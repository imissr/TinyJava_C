
add_library(parser type.c  type.c)

target_link_libraries(parser scanner datastruktur tools)

target_include_directories(parser PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})