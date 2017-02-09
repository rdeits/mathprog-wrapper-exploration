cmake_minimum_required(VERSION 2.8.12)

add_subdirectory(pybind11)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/pybind11/tools")
find_package(Eigen3 REQUIRED)
include_directories(${EIGEN3_INCLUDE_DIR})
find_package(NumPy REQUIRED)
include_directories(${NUMPY_INCLUDE_DIRS})

pybind11_add_module(expressions expressions.cpp)
