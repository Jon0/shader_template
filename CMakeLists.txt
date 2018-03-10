project (GLTemplate)

cmake_minimum_required (VERSION 2.8)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/CMake/")

find_package(LibEpoxy 1.2 REQUIRED)
find_package(PkgConfig REQUIRED)
pkg_search_module(GLFW REQUIRED glfw3)
pkg_search_module(GLM REQUIRED glm)

include_directories (
	${LIBEPOXY_INCLUDE_DIRS}
	${GLFW_INCLUDE_DIRS}
	${GLM_INCLUDE_DIRS}
)

file(GLOB SRC_FILES
    "src/*.cpp"
    "src/buffer/*.cpp"
    "src/components/*.cpp"
    "src/control/*.cpp"
    "src/io/*.cpp"
    "src/shader/*.cpp"
    "src/pipeline/*.cpp"
)

# copy shaders to binary folder
file( COPY "${PROJECT_SOURCE_DIR}/glsl/" DESTINATION "${PROJECT_BINARY_DIR}/glsl/")

add_definitions(-std=c++17)
add_executable (GLMain ${SRC_FILES})
target_link_libraries (
	GLMain 
	${LIBEPOXY_LIBRARIES} 
	${GLFW_LIBRARIES}
	${GLM_LIBRARIES}
)
