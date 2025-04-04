
add_library(parser type.c  type.c node.c item.c dummyMethod.c )

target_link_libraries(parser scanner datastruktur tools byteCode)

target_include_directories(parser PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})