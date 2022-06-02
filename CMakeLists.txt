cmake_minimum_required(VERSION 3.10)
project(MinHash)

#设置编译 c++ 标准	
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -g -W -Wall -Wextra -O3 ")

#设置头文件、源文件路径
set(SOURCES_DIRECTORY ${PROJECT_SOURCE_DIR}/src)
set(INCLUDES_DIRECTORY ${PROJECT_SOURCE_DIR}/include)

#设置输出路径
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

# -I 包含头文件路径
include_directories(${INCLUDES_DIRECTORY})
# -I 包含头文件路径
include_directories(${INCLUDES_DIRECTORY} "/usr/include/python3.6")


#源文件搜索
FILE(GLOB_RECURSE SourceFiles "${SOURCES_DIRECTORY}/*.cpp")
add_executable(MinHash ${SourceFiles})

target_link_libraries(MinHash "/usr/lib/python3.6/libpython3.6.so")

