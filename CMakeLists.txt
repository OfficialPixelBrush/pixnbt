cmake_minimum_required(VERSION 3.16.0)
cmake_policy(SET CMP0072 NEW)

project(pixnbt VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include_directories(
    "${PROJECT_SOURCE_DIR}/nbt"
    "${PROJECT_SOURCE_DIR}/"
)

add_executable(
    pixnbt
    
    tags/tag.cpp
    nbt.cpp
    example.cpp
)

# this is only defined to expose jthreads
target_compile_definitions(pixnbt PRIVATE -D_LIBCPP_ENABLE_EXPERIMENTAL=1)

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_options(pixnbt PRIVATE -ggdb)
endif ()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address -g")
set(CMAKE_LINKER_FLAGS "${CMAKE_LINKER_FLAGS} -fsanitize=address")

target_link_libraries(
    pixnbt
    deflate
)
