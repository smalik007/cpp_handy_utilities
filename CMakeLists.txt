cmake_minimum_required(VERSION 3.0)

SET(CMAKE_CXX_COMPILER "g++")

PROJECT(RunProgram)

# set c++17 standard
if(CMAKE_VERSION VERSION_LESS "3.1")
  if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11")
  endif()
else()
  set(CMAKE_CXX_STANDARD 11)
endif()

# add CFLAGS
add_definitions("-O3 -Wall -g -lstdc++ -Wl,-rpath -fpermissive -Wno-unused-variable -Wno-unused-function -Wno-unused-but-set-variable -std=c++17")

# make a list of all source files for ButkerIPUServer
file(GLOB SOURCES "inc/*.hpp" "inc/*.h" "src/*.cpp")

# x86_64 settings
add_executable(RunProgram ${SOURCES})

target_link_libraries(RunProgram
  boost_filesystem
  boost_system
)