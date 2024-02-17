cmake_minimum_required(VERSION 3.15)
project(bemf_observer LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic -Werror -Wold-style-cast")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS} -g")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS} -O3")

include(CTest)
enable_testing()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

# Declare a C++ library
add_library(${PROJECT_NAME}
    src/controllers/pi_controller.cpp
    src/math/functions.cpp
    src/math/foc.cpp
    src/math/operators.cpp
    src/math/cordic.cpp
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

add_executable(dq_update_test tests/dq_update_test.cpp)
target_link_libraries(dq_update_test ${PROJECT_NAME})
add_test(NAME dq_update_test COMMAND "${CMAKE_SOURCE_DIR}/bin/dq_update_test")

add_executable(tracker_test tests/tracker_test.cpp)
target_link_libraries(tracker_test ${PROJECT_NAME})
add_test(NAME tracker_test COMMAND "${CMAKE_SOURCE_DIR}/bin/tracker_test")

add_executable(cordic_algo_test tests/cordic_algo_test.cpp)
target_link_libraries(cordic_algo_test ${PROJECT_NAME})
add_test(NAME cordic_algo_test COMMAND "${CMAKE_SOURCE_DIR}/bin/cordic_algo_test" 45)

# Include Header files
include_directories(
    include
)
