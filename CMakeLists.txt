cmake_minimum_required(VERSION 3.12 FATAL_ERROR)
set (CMAKE_CXX_STANDARD 11)
project(PlaygroundEngine)

# Code Coverage Configuration
add_library(coverage_config INTERFACE)

option(CODE_COVERAGE "Enable coverage reporting" OFF)
if(CODE_COVERAGE AND CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
  # Add required flags (GCC & LLVM/Clang)
  target_compile_options(coverage_config INTERFACE
    -O0        # no optimization
    -g         # generate debug info
    --coverage # sets all required flags
  )
  if(CMAKE_VERSION VERSION_GREATER_EQUAL 3.13)
    target_link_options(coverage_config INTERFACE --coverage)
  else()
    target_link_libraries(coverage_config INTERFACE --coverage)
  endif()
endif(CODE_COVERAGE)

# Build engine library
# Add files
file(GLOB
	SOURCE_FILES
	${CMAKE_SOURCE_DIR}/src/*.cpp)
file(GLOB_RECURSE
	HEADER_FILES
	${CMAKE_SOURCE_DIR}/include/*.h)

# Create library
add_library(
	${PROJECT_NAME}
	${HEADER_FILES}
	${SOURCE_FILES})

add_definitions(-DGLM_ENABLE_EXPERIMENTAL)

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
  # using Clang
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
  # using GCC
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Intel")
  # using Intel C++
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
  # using Visual Studio C++
	set_target_properties(${PROJECT_NAME}
	PROPERTIES
	LINK_FLAGS
	/SUBSYSTEM:CONSOLE)

	# Add project filters
	source_group(
		"Source"
		FILES
		${SOURCE_FILES})
	source_group(
		"Headers"
		FILES
		${HEADER_FILES})
	# source_group("Shaders" REGULAR_EXPRESSION "[vert,geom,frag,comp]$")

	set(GLEW_USE_STATIC_LIBS TRUE)
	ADD_DEFINITIONS(-DGLEW_STATIC )

	list(APPEND CMAKE_PREFIX_PATH "C:/thirdparty/glew")
endif()

# Find external libraries
set(CMAKE_MODULE_PATH
	${CMAKE_MODULE_PATH}
	"${CMAKE_SOURCE_DIR}/cmake/")

find_package(OpenGL REQUIRED OpenGL)

find_package(GLM REQUIRED)
message(STATUS
	"GLM included at ${GLM_INCLUDE_DIR}")

find_package(GLFW3 REQUIRED)
message(STATUS
	"GLFW3 included at ${GLFW3_INCLUDE_DIR}")

set(GLEW_VERBOSE TRUE)
find_package(GLEW REQUIRED)
message(STATUS
	"GLEW included at ${GLEW_INCLUDE_DIR}")

# Link libraries
set(LIBS
	OpenGL::GL
	${GLFW3_LIBRARY}
	GLEW::GLEW
  coverage_config)
target_link_libraries(
	${PROJECT_NAME}
	${LIBS})

# Define include directories
set(ADDITIONAL_INCLUDES
	${GLM_INCLUDE_DIR}
	${GLFW3_INCLUDE_DIR}
	${GLEW_INCLUDE_DIRS})
target_include_directories(
	${PROJECT_NAME}
	PUBLIC
	"${CMAKE_SOURCE_DIR}/src"
	"${CMAKE_SOURCE_DIR}/include"
	${ADDITIONAL_INCLUDES})
	
add_subdirectory(apps)

# Add testing
option (BUILD_TESTING "Build the testing tree." ON)
# Only build tests if we are the top-level project
# Allows this to be used by super projects with `add_subdirectory`
if (BUILD_TESTING AND (PROJECT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR))
  enable_testing()
  add_subdirectory(tests)
endif()
