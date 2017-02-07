add_subdirectory(pybind11)

find_package( Eigen3 )
include_directories(${CMAKE_INSTALL_PREFIX}/include/eigen3)

pybind11_add_module(expressions expressions.cpp)
