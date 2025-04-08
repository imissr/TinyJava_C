
#include "print_abstract_syntax_tree.h"

static int node_counter = 0;
static FILE *vcg_file = NULL;

static void open_vcg_graph(const char *filename) {
    vcg_file = fopen(filename, "w");
    if (!vcg_file) {
        perror("Cannot open VCG output file");
        exit(EXIT_FAILURE);
    }

    fprintf(vcg_file,
        "graph: {\n"
        "title: \"visual abstract syntax tree\"\n"
        "layoutalgorithm: tree\n"
        "x: 30\n"
        "y: 30\n"
        "width: 1000\n"
        "height: 1000\n"
        "color: white\n"
        "stretch: 8\n"
        "shrink: 10\n"
        "layout_upfactor: 10\n"
        "display_edge_labels: yes\n"
    );
}

static void close_vcg_graph() {
    if (vcg_file) {
        fprintf(vcg_file, "}\n");
        fclose(vcg_file);
        vcg_file = NULL;
    }
}

static void make_node(const char *color, const char *textcolor, int no, const char *label) {
    fprintf(vcg_file,
        "node: { color: %s textcolor: %s title: \"%d\" label: \"%s\" }\n",
        color, textcolor, no, label);
}

static void make_edge(const char *kind, int from, int to, const char *color, int thickness, const char *label) {
    fprintf(vcg_file,
        "%s: { sourcename: \"%d\" targetname: \"%d\" color: %s thickness: %d label: \"%s\" }\n",
        kind, from, to, color, thickness, label);
}

static void print_nodes(Node *node) {
    if (!node) return;

    node->no = node_counter++;

    const char *color = "white";
    if (node->nodeClass == CLASS_CLASS) color = "yellow";
    else if (node->nodeClass == CLASS_ENTER) color = "green";

    char label[256];
    nodeToString(node, label, sizeof(label));
    make_node(color, "black", node->no, label);

    print_nodes(node->left);
    print_nodes(node->right);
    print_nodes(node->next);
}

static void print_edges(Node *node) {
    if (!node) return;

    if (node->left) {
        make_edge("edge", node->no, node->left->no, "blue", 3, "left");
        print_edges(node->left);
    }
    if (node->right) {
        make_edge("edge", node->no, node->right->no, "blue", 3, "right");
        print_edges(node->right);
    }
    if (node->next) {
        make_edge("nearedge", node->no, node->next->no, "red", 3, "next");
        print_edges(node->next);
    }
}

void print_abstract_syntax_tree(Node *root, const char *filename) {
    node_counter = 0;
    open_vcg_graph(filename);
    print_nodes(root);
    print_edges(root);
    close_vcg_graph();
}
