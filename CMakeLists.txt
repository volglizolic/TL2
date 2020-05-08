cmake_minimum_required(VERSION 3.15)
project(TL2)

set(CMAKE_C_STANDARD 11)
set(GCC_COVERAGE_COMPILE_FLAGS "-pthread -g -O3")
set(TL2_COMPILE_FLAGS "")
set(TL2_COMPILE_FLAGS "-DTL2_EAGER")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${TL2_COMPILE_FLAGS}")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}" )


add_library(TL2 STATIC
        common.h
        platform.h
        stm.h
        tl2.c
        tl2.h
        tmalloc.c
        tmalloc.h
        util.h)