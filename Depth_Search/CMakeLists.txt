cmake_minimum_required(VERSION 3.8 FATAL_ERROR)

project(Depth_Search VERSION 1.0.0)

add_executable(Depth_Search Depth_Search.c)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)


