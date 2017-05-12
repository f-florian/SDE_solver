# -*- mode: cmake; eval: (hl-line-mode 0);-*-
#integrator functions and program

set(progname Integrator)

# Use c++14
enable_language(CXX)

find_package(MPI REQUIRED)

MESSAGE("${MPI_CXX_LIBRARIES}")

include_directories(${MPI_CXX_INCLUDE_PATH})

set(sources main.cpp equation.cpp aux.cpp gauss_gen.cpp equation_except.cpp)
add_executable(${progname} ${sources})
target_link_libraries(${progname} ${MPI_CXX_LIBRARIES})

if(MPI_COMPILE_FLAGS)
  set_target_properties(${progname} PROPERTIES COMPILE_FLAGS "${MPI_CXX_COMPILE_FLAGS}")
endif()
if(MPI_LINK_FLAGS)
  set_target_properties(${progname} PROPERTIES LINK_FLAGS "${MPI_CXX_LINK_FLAGS}")
endif()

set_property(TARGET ${progname} PROPERTY CXX_STANDARD 14)

