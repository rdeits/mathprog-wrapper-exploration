cmake_minimum_required(VERSION 2.8.12)
project(expressions)
include(ExternalProject)

ExternalProject_Add(eigen-pod
  GIT_REPOSITORY https://github.com/RobotLocomotion/eigen-pod.git
  GIT_TAG ceba39500b89a77a8649b3e8b421b10a3d74d42b
  BUILD_IN_SOURCE 1
  CONFIGURE_COMMAND ""
  BUILD_COMMAND make BUILD_PREFIX=${CMAKE_INSTALL_PREFIX} BUILD_TYPE=${CMAKE_BUILD_TYPE}
  UPDATE_COMMAND ""
  INSTALL_COMMAND ""
  )

ExternalProject_Add(pybind-demo
    SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src
    DEPENDS eigen-pod
    CMAKE_ARGS 
      -DCMAKE_INSTALL_PREFIX=${CMAKE_INSTALL_PREFIX} 
      -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    INSTALL_COMMAND ""
  )

ExternalProject_Add_Step(pybind-demo forceconfigure
  COMMAND ${CMAKE_COMMAND} -E echo "Force configure of pybind-demo"
  DEPENDEES update
  DEPENDERS configure
  ALWAYS 1)