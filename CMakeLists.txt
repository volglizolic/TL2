cmake_minimum_required(VERSION 3.15)
project(STMx86)

set(CMAKE_CXX_STANDARD 17)
set(GCC_COVERAGE_COMPILE_FLAGS "-fgnu-tm -pthread -g")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}" )

add_executable(STMx86 common.h platform.h stm.h tl2.c tl2.h tmalloc.c tmalloc.h util.h)