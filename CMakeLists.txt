cmake_minimum_required(VERSION 3.10)
cmake_policy(SET CMP0015 NEW)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

project(emtest)

file(GLOB_RECURSE CORE_HDR src/*.h)
file(GLOB_RECURSE CORE_SRC src/*.cpp)

add_executable(client ${CORE_SRC} ${CORE_HDR})

set(CMAKE_VERBOSE_MAKEFILE on)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/build.emscripten)

#
# Trying usual cmake project compiler execution
#

add_definitions("-std=c++11")

# To switch from Emscript build to regular cpp binary build
set(EMSCRIPT ON)

if(EMSCRIPT)
	message(STATUS "EMSCRIPT BUILD ON")	
	add_definitions(-DUSE_EMSCRIPT)
endif()

### INTERPROCEDURAL_OPTIMIZATION ###
cmake_policy(SET CMP0069 NEW)
include(CheckIPOSupported)
check_ipo_supported(RESULT result OUTPUT error)
if (result)
    message(STATUS "IPO / LTO enabled")
    set_target_properties(client PROPERTIES INTERPROCEDURAL_OPTIMIZATION True)
else ()
    message(STATUS "IPO / LTO not supported: <${error}>")
endif ()
### END INTERPROCEDURAL_OPTIMIZATION ###

if(EMSCRIPT)
	set_target_properties(client PROPERTIES LINK_FLAGS "-s DEMANGLE_SUPPORT=1 -s ALLOW_MEMORY_GROWTH=1 --preload-file assets -lembind")
else()
	set_target_properties(client PROPERTIES LINK_FLAGS " -O3")
endif()

