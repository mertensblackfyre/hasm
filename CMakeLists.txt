cmake_minimum_required(VERSION 3.16)
project(hasm LANGUAGES C CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include header directory
include_directories(${CMAKE_SOURCE_DIR}/includes)

# Source files
set(SOURCES
    main.cc
    src/constant.cc
    src/helper.cc
)

# Create executable
add_executable(hasm ${SOURCES})

