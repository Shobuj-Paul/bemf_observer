cmake_minimum_required(VERSION 3.15)

project(bemf_observer)
set(CMAKE_CXX_STANDARD 20) # C++20 Standard

## Add C++ executables here
  add_executable(pi_test test/pi_test.cpp)
  target_link_libraries(pi_test ${PROJECT_NAME})

# Declare a C++ library
add_library(${PROJECT_NAME}
    src/controllers.cpp
)

# Include Header files
include_directories(
    include
)