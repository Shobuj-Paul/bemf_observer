cmake_minimum_required(VERSION 3.15)
project(bemf_observer LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic -Werror")

include(CTest)
enable_testing()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

# Declare a C++ library
add_library(${PROJECT_NAME}
    src/controllers/pi_controller.cpp
    src/math/functions.cpp
    src/math/foc.cpp
    src/math/operators.cpp
    src/observers/tracker.cpp
    src/observers/dq_update.cpp
    src/observers/bemf_observer.cpp
)

## Add C++ tests here
add_executable(pi_test tests/pi_test.cpp)
target_link_libraries(pi_test ${PROJECT_NAME})
add_test(NAME pi_test COMMAND "${CMAKE_SOURCE_DIR}/bin/pi_test")

add_executable(bemf_observer_test tests/bemf_observer_test.cpp)
target_link_libraries(bemf_observer_test ${PROJECT_NAME})
add_test(NAME bemf_observer_test COMMAND "${CMAKE_SOURCE_DIR}/bin/bemf_observer_test")

# Include Header files
include_directories(
    include
)
