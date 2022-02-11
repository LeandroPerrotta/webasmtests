cmake_minimum_required(VERSION 2.8)
cmake_policy(SET CMP0015 NEW)

project(emtest)

set(CMAKE_VERBOSE_MAKEFILE on)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/build.emscripten)

file(GLOB_RECURSE CORE_HDR src/*.h)
file(GLOB_RECURSE CORE_SRC src/*.cpp)

#
# Trying usual cmake project compiler execution
#

add_definitions("-std=c++11")

# To switch from Emscript build to regular cpp binary build
set(EMSCRIPT OFF)

if(EMSCRIPT)
	message(STATUS "EMSCRIPT BUILD ON")	
	add_definitions(-DUSE_EMSCRIPT)
endif()

add_executable(client ${CORE_SRC} ${CORE_HDR})

if(EMSCRIPT)
	set_target_properties(client PROPERTIES LINK_FLAGS "-s DEMANGLE_SUPPORT=1 -s ALLOW_MEMORY_GROWTH=1 --preload-file assets -lembind -O3 -ffast-math")
else()
	set_target_properties(client PROPERTIES LINK_FLAGS " -O3 -ffast-math")
endif()
