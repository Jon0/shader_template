cmake_minimum_required (VERSION 2.6)

project (Test)
set (Test_VERSION_MAJOR 2)
set (Test_VERSION_MINOR 0)

configure_file (
  "${PROJECT_SOURCE_DIR}/src/config.h.in"
  "${PROJECT_BINARY_DIR}/config.h"
)

add_subdirectory (library/glfw-3.0.3)
add_subdirectory (library/glm)
include_directories ("${PROJECT_BINARY_DIR}")
include_directories ( ${GLM_INCLUDE_DIRS} )
include_directories ( ${GLFW_INCLUDE_DIRS} )
include_directories ("${PROJECT_SOURCE_DIR}/library")
include_directories ("${PROJECT_SOURCE_DIR}/library/glfw-3.0.3/include")

add_executable (Test src/test.cpp src/shader/program.cpp src/shader/Shader.cpp)
target_link_libraries (Test glfw ${GLFW_LIBRARIES})
