cmake_minimum_required (VERSION 2.6)

project (Test)
add_definitions(-std=c++11)



set (Test_VERSION_MAJOR 1)
set (Test_VERSION_MINOR 0)
configure_file (
  "${PROJECT_SOURCE_DIR}/src/config.h.in"
  "${PROJECT_BINARY_DIR}/config.h"
)

add_definitions(-DGLEW_STATIC)
set(GLEW_SOURCE ${PROJECT_SOURCE_DIR}/library/glew-1.10.0/src/*.c)

add_subdirectory (library/glfw-3.0.3)
add_subdirectory (library/glm)
include_directories ("${PROJECT_BINARY_DIR}")

include_directories ( ${GLEW_INCLUDE_DIR} )
include_directories ( ${GLFW_INCLUDE_DIR} )
include_directories ( ${GLM_INCLUDE_DIR} )

include_directories ("${PROJECT_SOURCE_DIR}/library")
include_directories ("${PROJECT_SOURCE_DIR}/library/glew-1.10.0/include")
include_directories ("${PROJECT_SOURCE_DIR}/library/glfw-3.0.3/include")

add_library( glew_static STATIC
	${GLEW_SOURCE}
)

file(GLOB SRC_FILES
    "src/*.h"
    "src/*.cpp"
    "src/shader/*.h"
    "src/shader/*.cpp"
)

add_executable (Test ${SRC_FILES})
target_link_libraries (Test glew_static glfw ${GLFW_LIBRARIES})
