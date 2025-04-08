# Bibliothek 'tools' mit input.c und output.c erstellen
add_library(tools input.c output.c print_abstract_syntax_tree.c)

# Sicherstellen, dass 'tools' Zugriff auf die Header von 'datastruktur' hat
target_link_libraries(tools datastruktur parser)

# Inklusionsverzeichnisse für 'tools' setzen (inkl. 'datastruktur')
target_include_directories(tools PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})