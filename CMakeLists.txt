cmake_minimum_required(VERSION 3.2)
project(pymm)
set(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -g -Wall -Wextra -fexceptions")
set(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall -Wextra -fexceptions")
IF (CMAKE_BUILD_TYPE STREQUAL Debug)
    ADD_DEFINITIONS(-DDEBUG)
ENDIF()

aux_source_directory(src SRCS)
add_executable(pymm ${SRCS})
target_include_directories(pymm
	PRIVATE
		${PROJECT_SOURCE_DIR}/include
)
target_compile_features(pymm PRIVATE cxx_auto_type)

