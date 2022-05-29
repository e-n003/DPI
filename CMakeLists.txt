cmake_minimum_required(VERSION 3.0)
project("TIDS")
set(CMAKE_CXX_STANDARD 14)
include_directories(./include)
file(GLOB SRC_LIST "./dpi_protol/*.c" "./linkList/*.c")
add_executable(TIDS ./main.c ./dpi_main.c ${SRC_LIST})
add_executable(testlist ./test/test.c ./linkList/dpi_list.c)


SET(CMAKE_BUILD_TYPE "Debug")  # 定义编译类型
SET(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g2 -ggdb") # 定义Debug编译参数
SET(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall") # 定义Release编译参数

target_link_libraries(TIDS pcap)
