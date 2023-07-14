cmake_minimum_required(VERSION 3.0)

SET(CMAKE_CXX_COMPILER "g++")

PROJECT(RunProgram)

# set c++17 standard
if(CMAKE_VERSION VERSION_LESS "3.1")
  if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++17")
  endif()
else()
  set(CMAKE_CXX_STANDARD 17)
endif()

find_package(jsoncpp CONFIG REQUIRED)

# add CFLAGS
add_definitions("-O3 -lstdc++ -Wl,-rpath -fpermissive -std=c++17")
# add_definitions("-g") # debugging symbol

# Manage warnings
add_definitions("-Wall") # enable all warnings
# supress individual warning if needed
# add_definitions("-Wno-unused-variable")
# add_definitions("-Wno-unused-function -Wno-unused-but-set-variable")
add_definitions("-Wp,-w")

file(GLOB SOURCES "src/*.hpp" "src/*.cpp")

# x86_64 settings
add_executable(RunProgram ${SOURCES})

target_link_libraries(RunProgram
  PRIVATE JsonCpp::JsonCpp
  boost_filesystem
  boost_system
)

add_test(
  NAME RunProgram
  COMMAND RunProgram
)