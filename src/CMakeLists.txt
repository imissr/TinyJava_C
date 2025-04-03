# Füge Unterverzeichnisse für Scanner und Datastruktur hinzu
add_subdirectory(scanner)
add_subdirectory(datastruktur)
add_subdirectory(tools)
add_subdirectory(parser)

# Erstelle das Hauptprogramm
add_executable(compiler main.c)

# Verknüpfe das Hauptprogramm mit den Bibliotheken
target_link_libraries(compiler scanner datastruktur tools parser)

# Füge den Include-Pfad für datastruktur hinzu
target_include_directories(compiler PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/datastruktur)
