# -*- mode: cmake; eval: (hl-line-mode 0);-*-
#integrator functions and program
set(progname Integrator)

find_package(MPI REQUIRED)
include_directories(${MPI_CXX_INCLUDE_PATH})

# If URANDOM_ONLY is set to 1 only get random numbers from the system random number generator; else use a pseudorandom number generator seeded with system random numbers
# If AUTO_RESEED is different from 0, seed the pseudorandom number genarator based on the random returned number (once every AUTO_RESEED calls in mean). Ignored if URANDOM_ONLY is 1
add_definitions(-DURANDOM_ONLY=0 -DAUTO_RESEED=0)

set(sources equation.cpp randomnumbers.cpp equation_except.cpp)
add_library(${progname} SHARED ${sources})

target_link_libraries(${progname} ${MPI_CXX_LIBRARIES})
set_property(GLOBAL PROPERTY CXX_STANDARD 14)
set_property(GLOBAL PROPERTY CXX_STANDARD_REQUIRED)

if(MPI_COMPILE_FLAGS)
  set_target_properties(${progname} PROPERTIES COMPILE_FLAGS "${MPI_CXX_COMPILE_FLAGS}")
endif()
if(MPI_LINK_FLAGS)
  set_target_properties(${progname} PROPERTIES LINK_FLAGS "${MPI_CXX_LINK_FLAGS}")
endif()
