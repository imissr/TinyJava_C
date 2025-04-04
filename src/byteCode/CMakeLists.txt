
add_library(byteCode constantPoolItem.c)

target_link_libraries(byteCode scanner datastruktur tools parser)

target_include_directories(byteCode PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})