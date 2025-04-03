add_library(parser parser.c type.c)
target_include_directories(parser PUBLIC ${CMAKE_SOURCE_DIR}/include)

target_include_directories(parser PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})