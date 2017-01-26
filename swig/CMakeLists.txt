cmake_minimum_required(VERSION 2.8.0)

if(APPLE)
  cmake_policy(SET CMP0042 NEW)
endif()

find_package( Eigen3 )
if (EIGEN3_FOUND)
  include_directories( ${EIGEN3_INCLUDE_DIR} )
else()
    message("Eigen3 not found, so I'm installing it from source. ")
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
  include_directories(${CMAKE_INSTALL_PREFIX}/include/eigen3)
endif()

find_package(SWIG REQUIRED)
include(UseSWIG)

if(NOT PYTHON_LIBRARY AND NOT PYTHON_INCLUDE_DIR)
  execute_process(
    COMMAND "${PYTHON_EXECUTABLE}" -c "import sys; print(sys.exec_prefix)"
    RESULT_VARIABLE PYTHON_EXEC_PREFIX_RESULT
    OUTPUT_VARIABLE PYTHON_EXEC_PREFIX
    OUTPUT_STRIP_TRAILING_WHITESPACE)

  if(PYTHON_EXEC_PREFIX_RESULT EQUAL 0)
    list(APPEND CMAKE_PREFIX_PATH ${PYTHON_EXEC_PREFIX})
  else()
    message(WARNING "Could NOT determine Python sys.exec_prefix")
  endif()
endif()

find_package(PythonLibs 3.5 REQUIRED)
include_directories(${PYTHON_INCLUDE_DIRS})

set_property(SOURCE expressions.i PROPERTY CPLUSPLUS ON)
swig_add_module(expressions python expressions.i)
set_property(TARGET ${SWIG_MODULE_expressions_REAL_NAME} PROPERTY CXX_STANDARD 11)
target_link_libraries(${SWIG_MODULE_expressions_REAL_NAME} ${PYTHON_LIBRARIES})

