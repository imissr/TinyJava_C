// parser_ll1.c

#include "parser_LL1.h"
#include "print_abstract_syntax_tree.h"
#include <stdio.h>

static void init_first_sets(ParserLL1 *parser) {
    bitset_set(parser->firstMembDecl, SYM_STATIC);
    bitset_set(parser->firstMembDecl, SYM_FINAL);
    bitset_set(parser->firstMembDecl, SYM_VOID);
    bitset_set(parser->firstMembDecl, SYM_INT);
    bitset_set(parser->firstMembDecl, SYM_ID);

    bitset_set(parser->firstStmt, SYM_IF);
    bitset_set(parser->firstStmt, SYM_WHILE);
    bitset_set(parser->firstStmt, SYM_RETURN);
    bitset_set(parser->firstStmt, SYM_STATIC);
    bitset_set(parser->firstStmt, SYM_INT);
    bitset_set(parser->firstStmt, SYM_ID);

    bitset_set(parser->firstCondFact, SYM_EQUAL);
    bitset_set(parser->firstCondFact, SYM_LESS);
    bitset_set(parser->firstCondFact, SYM_GREATER);
    bitset_set(parser->firstCondFact, SYM_LESS_EQUAL);
    bitset_set(parser->firstCondFact, SYM_GREATER_EQUAL);
    bitset_set(parser->firstCondFact, SYM_UNEQUAL);
}

ParserLL1 *parser_create(Scanner *in, bool debug, bool vcg) {
    ParserLL1 *parser = malloc(sizeof(ParserLL1));
    parser->in = in;
    parser->out = in->output;

    parser->firstMembDecl = bitset_create();
    parser->firstStmt = bitset_create();
    parser->firstCondFact = bitset_create();

    parser->unresolvedMethods = linkedlist_create();

    parser->token = NULL;
    parser->lastToken = NULL;

    parser->symbolTable = NULL;
    parser->classObject = NULL;
    parser->curObject = NULL;
    parser->abstractSyntaxTree = NULL;

    parser->debug = debug;
    parser->vcg = vcg;

    init_first_sets(parser);

    // start parsing
    parser->token = scan_symbol(parser->in);
    // call ClassDecl(); — implement this function next
    // parser->abstractSyntaxTree = ClassDecl(parser); // Example call

    if (parser->token->symbol != EOF_TOKEN) {
        output_add_syntactical_error(parser->out, parser->token->line, parser->token->column, "compiler doesn't reach end of file");
    }

    if (debug) {
        output_printLexicalErrorReport(parser->out);
        output_printSyntacticalErrorReport(parser->out);
        output_printSemanticErrorReport(parser->out);
    }

    if (vcg && !output_errorFound(parser->out)) {
        char astFilename[128];
        snprintf(astFilename, sizeof(astFilename), "parse_ast_%s.vcg", parser->classObject ? parser->classObject->objectName : "unknown");
        print_abstract_syntax_tree(parser->abstractSyntaxTree, astFilename);

        if (debug)
            printf("parser: %s successfully created\n", astFilename);
    }

    return parser;
}

Token *get_next_token(ParserLL1 *parser) {
    parser->lastToken = parser->token;
    parser->token = scan_symbol(parser->in);
    return parser->token;
}

bool check_token(ParserLL1 *parser, int expected) {
    if (peek_token(parser, expected)) {
        return true;
    } else {
        char msg[128];
        snprintf(msg, sizeof(msg), "symbol \"%s\" expected", symbols[expected]);
        output_add_syntactical_error(parser->out, parser->token->line, parser->token->column, msg);
        return false;
    }
}

bool peek_token(ParserLL1 *parser, int expected) {
    if (parser->token->symbol == expected) {
        get_next_token(parser);
        return true;
    }
    return false;
}

void syntax_error(ParserLL1 *parser, int *expected, int count) {
    if (count == 0) return;
    char msg[256] = "";
    for (int i = 0; i < count; i++) {
        strcat(msg, "symbol \"");
        strcat(msg, symbols[expected[i]]);
        strcat(msg, "\"");
        if (i < count - 1) strcat(msg, " or ");
    }
    strcat(msg, " expected");
    output_add_syntactical_error(parser->out, parser->token->line, parser->token->column, msg);
}

void semantic_error(ParserLL1 *parser, const char *message) {
    output_add_semantic_error(parser->out, parser->token->line, parser->token->column, message);
}


Node *parse_ClassDecl(ParserLL1 *parser) {
    parser->symbolTable = createSymbolTable(NULL);
    parser->classObject = createItem();

    check_token(parser, SYM_CLASS);

    if (check_token(parser, SYM_ID)) {
        parser->classObject = createItemFull(
            parser->lastToken->identifier,
            KIND_CLASS,
            NOSUBKIND,
            initType(TYPE_CLASS),
            0, 0, NULL
        );
        strcpy(parser->classObject->objectType->classType, parser->classObject->objectName);
        insertItem(parser->symbolTable, parser->classObject);
        parser->abstractSyntaxTree = createNodeFull(CLASS_CLASS, NOSUBCLASS, parser->classObject, NULL, NULL, NULL, NULL);
    }

    parser->classObject->fields = createSymbolTable(parser->symbolTable);
    parser->classObject->fields->parent = parser->classObject;
    parser->symbolTable = parser->classObject->fields;

    check_token(parser, SYM_LEFT_CURVED_PARENT);
    Node *members = parse_MembDecls(parser);
    if (members) members->parent = parser->abstractSyntaxTree;
    parser->abstractSyntaxTree->left = members;
    check_token(parser, SYM_RIGHT_CURVED_PARENT);

    resolve_unresolved_methods(parser, parser->classObject->fields);
    parser->symbolTable = parser->symbolTable->enclose;

    return parser->abstractSyntaxTree;
}

// Dummy resolver
void resolve_unresolved_methods(ParserLL1 *parser, SymbolTable *table) {
    // to be implemented
}

// --- MembDecls ---
Node *parse_MembDecls(ParserLL1 *parser) {
    Node *decls = createNode();
    while (bitset_test(parser->firstMembDecl, parser->token->symbol)) {
        parser->curObject = createItem();
        Node *decl = parse_MembDecl(parser);
        attachNode(decls, decl);
    }
    return decls->next;
}

// --- MembDecl ---
Node *parse_MembDecl(ParserLL1 *parser) {
    if (peek_token(parser, SYM_STATIC)) {
        parser->curObject->staticModifier = 1;
        return parse_StaticMembDecl(parser);
    } else if (peek_token(parser, SYM_FINAL)) {
        return parse_ConstDecl(parser);
    } else if (peek_token(parser, SYM_VOID)) {
        parser->curObject->itemKind = KIND_METHOD;
        parser->curObject->objectType = initType(TYPE_VOID);
        return parse_MethDecl(parser);
    } else if (peek_token(parser, SYM_INT)) {
        parser->curObject->objectType = initType(TYPE_INT);
        return parse_MethOrVarDecl(parser);
    } else if (peek_token(parser, SYM_ID)) {
        parser->curObject->objectName = strdup(parser->lastToken->identifier);
        return parse_VarOrConstructorDecl(parser);
    } else {
        int expected[] = {SYM_STATIC, SYM_FINAL, SYM_VOID, SYM_INT, SYM_ID};
        syntax_error(parser, expected, 5);
    }
    return NULL;
}


void parser_free(ParserLL1 *parser) {
    if (!parser) return;
    if (parser->firstMembDecl) bitset_destroy(parser->firstMembDecl);
    if (parser->firstStmt) bitset_destroy(parser->firstStmt);
    if (parser->firstCondFact) bitset_destroy(parser->firstCondFact);
    if (parser->unresolvedMethods) linkedlist_free(parser->unresolvedMethods, NULL);
    free(parser);
}
