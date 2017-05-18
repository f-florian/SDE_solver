# -*- mode: cmake; eval: (hl-line-mode 0);-*-
cmake_minimum_required(VERSION 3.0.0)
cmake_policy(SET CMP0048 NEW)
project(SDE_solve VERSION 1.0 LANGUAGES CXX)

set(progname ${PROJECT_NAME})
add_definitions(-Dcmake_MAJOR=${PROJECT_VERSION_MAJOR} -Dcmake_MINOR=${PROJECT_VERSION_MINOR} -Dcmake_NAME="${progname}" -D___debug="1")

set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_CXX_FLAGS "-pipe -O2 -Wall -g")

find_package(Qt5Core)
find_package(Qt5Widgets)

get_target_property(QtCore_location Qt5::Core LOCATION)
get_target_property(QtWidgets_location Qt5::Widgets LOCATION)

add_subdirectory(integrator ${CMAKE_CURRENT_BINARY_DIR}/integrator)
