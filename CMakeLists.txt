project(stringwriter)
cmake_minimum_required(VERSION 2.8)

include(CheckCXXCompilerFlag)
check_cxx_compiler_flag(-std=c++11 HAS_STD_CPP11)
if (HAS_STD_CPP11)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
else()
    check_cxx_compiler_flag(-std=c++0x HAS_STD_CPP0X)
    if (HAS_STD_CPP0X)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
    else()
        message(WARNING
          "C++ Compiler does not support the -std=c++11 flag. If you get compile errors make"
          "sure you have a compiler that supports C++11.")
    endif()
endif()
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wall -Wconversion")

aux_source_directory(. SRC_LIST)
add_executable(${PROJECT_NAME} ${SRC_LIST})

