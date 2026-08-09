cmake_minimum_required(VERSION 3.10)

project(RelSym VERSION 0.1)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Set CMake policy to prefer the new GLVND libraries over legacy OpenGL
if(POLICY CMP0072)
    cmake_policy(SET CMP0072 NEW)
endif()

# Find OpenGL, GLFW, and GLEW
find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)
find_package(GLEW REQUIRED)


# Output everything into "out"
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/out")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/out")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/out")

# Include everything in "include"
include_directories("${CMAKE_SOURCE_DIR}/include")

# Collect everything from "src" to compile
file(GLOB_RECURSE SRC_FILES
    "${CMAKE_SOURCE_DIR}/src/*.cpp"
    "${CMAKE_SOURCE_DIR}/src/*.c"
    "${CMAKE_SOURCE_DIR}/src/*.cc"
    "${CMAKE_SOURCE_DIR}/src/*.cxx"
)

# Create the executable (it requires at least one source file in src/)
add_executable(${PROJECT_NAME} ${SRC_FILES})

# Link directories and collect all libraries in "lib"
link_directories("${CMAKE_SOURCE_DIR}/lib")
file(GLOB_RECURSE LIB_FILES
    "${CMAKE_SOURCE_DIR}/lib/*.a"
    "${CMAKE_SOURCE_DIR}/lib/*.so"
    "${CMAKE_SOURCE_DIR}/lib/*.dylib"
    "${CMAKE_SOURCE_DIR}/lib/*.lib"
)

if(LIB_FILES)
    target_link_libraries(${PROJECT_NAME} PRIVATE ${LIB_FILES} OpenGL::GL glfw GLEW::GLEW)
else()
    target_link_libraries(${PROJECT_NAME} PRIVATE OpenGL::GL glfw GLEW::GLEW)
endif()
