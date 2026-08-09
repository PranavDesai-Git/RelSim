cmake_minimum_required(VERSION 3.14)

project(RelSym VERSION 0.1)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Fetch Raylib
include(FetchContent)
FetchContent_Declare(
    raylib
    GIT_REPOSITORY https://github.com/raysan5/raylib.git
    GIT_TAG        master
)
set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)
set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(raylib)

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

# Create the executable
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
    target_link_libraries(${PROJECT_NAME} PRIVATE ${LIB_FILES} raylib)
else()
    target_link_libraries(${PROJECT_NAME} PRIVATE raylib)
endif()
