# Zandgall's Quickwork

cmake_minimum_required(VERSION 3.22.1)
project(Quickwork VERSION 0.2 DESCRIPTION "A quick working OpenGL project framework")

# Grab all the files in /src/...
file(GLOB_RECURSE SOURCE_FILES ${CMAKE_SOURCE_DIR}/src/*.c ${CMAKE_SOURCE_DIR}/src/*.cpp)
file(GLOB_RECURSE HEADER_FILES ${CMAKE_SOURCE_DIR}/src/*.h ${CMAKE_SOURCE_DIR}/src/*.hpp)

find_package(OpenGL REQUIRED)
find_package(glm REQUIRED)
find_package(glfw3 3.3 REQUIRED)
find_package(Freetype REQUIRED)

# Mark down what libraries are to be included, along with glad's header file directory
set(LIBS glfw glm::glm z m freetype)
include_directories(
    ${CMAKE_SOURCE_DIR}/third-party/include
    ${FREETYPE_INCLUDE_DIRS}
)

# Link the executable with its files, including glad and included libraries
add_executable(${PROJECT_NAME} ${HEADER_FILES} ${SOURCE_FILES} ${CMAKE_SOURCE_DIR}/third-party/src/gl.c)
target_link_libraries(${PROJECT_NAME} ${LIBS})

# Confirm debug and release compile options
target_compile_options(${PROJECT_NAME} PUBLIC "$<$<CONFIG:Debug>:-DDEBUG;-g;-Wall>")
target_compile_options(${PROJECT_NAME} PUBLIC "$<$<CONFIG:Release>:-O3>")
