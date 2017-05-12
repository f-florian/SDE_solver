# -*- mode: cmake; eval: (hl-line-mode 0);-*-
#This is the tama suite
cmake_minimum_required(VERSION 3.0.0)
cmake_policy(SET CMP0048 NEW)
project(Parallel_replica_test VERSION 1.0)

set(progname ${PROJECT_NAME})
add_definitions(-Dcmake_MAJOR=${PROJECT_VERSION_MAJOR} -Dcmake_MINOR=${PROJECT_VERSION_MINOR} -Dcmake_NAME="${progname}" -D___debug="1")

# Use c++14
enable_language(CXX)
set_property(GLOBAL PROPERTY CXX_STANDARD 14)
set_property(GLOBAL PROPERTY CXX_STANDARD_REQUIRED)


set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_CXX_FLAGS "-pipe -O2 -Wall -g")

find_package(Qt5Core)
find_package(Qt5Widgets)

get_target_property(QtCore_location Qt5::Core LOCATION)
get_target_property(QtWidgets_location Qt5::Widgets LOCATION)

#add_subdirectory(visualizer ${CMAKE_CURRENT_BINARY_DIR}/visualizer)
add_subdirectory(integrator ${CMAKE_CURRENT_BINARY_DIR}/integrator)
