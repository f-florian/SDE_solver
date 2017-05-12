# -*- mode: cmake; eval: (hl-line-mode 0);-*-
#Visulizer program

set(progname Visualizer)

# Use c++14
enable_language(CXX)

set(sources main.cpp view.cpp view.ui)                                                              
add_executable(${progname} ${sources})
set_property(TARGET ${progname} PROPERTY CXX_STANDARD 14)
target_link_libraries(${progname} Qt5::Core Qt5::Widgets)                   
