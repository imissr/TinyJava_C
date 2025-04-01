add_library(scanner scanner.c token.c)

# Scanner benötigt Datastruktur, daher Link hinzufügen
target_link_libraries(scanner datastruktur tools)

# Inkludiere das aktuelle Verzeichnis für Header-Dateien
target_include_directories(scanner PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
