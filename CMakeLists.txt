cmake_minimum_required(VERSION 3.0 FATAL_ERROR)
set (CMAKE_CXX_STANDARD 11)
project(OpenGLPlayground)

# Add files
file(GLOB
	SOURCE_FILES
	${CMAKE_SOURCE_DIR}/src/*.cpp)
file(GLOB_RECURSE
	HEADER_FILES
	${CMAKE_SOURCE_DIR}/include/*.h)
# file(GLOB_RECURSE
	# SHADER_FILES
	# ${CMAKE_SOURCE_DIR}/shaders/*)
	# message(${SHADER_FILES})

# Create executable
add_executable(
	${PROJECT_NAME}
	${HEADER_FILES}
	${SOURCE_FILES})

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

	set(GLEW_USE_STATIC_LIBS TRUE)

	list(APPEND CMAKE_PREFIX_PATH "C:/thirdparty/glew")
	list(APPEND CMAKE_PREFIX_PATH "C:/thirdparty/glew/lib/Release/Win32")
	list(APPEND CMAKE_PREFIX_PATH "C:/thirdparty/glew/bin/Release/Win32")
endif()

# Add project filters
source_group(
	"Source"
	FILES
	${SOURCE_FILES})
source_group(
	"Headers"
	FILES
	${HEADER_FILES})
# source_group(
	# "Shaders"
	# FILES
	# ${SHADER_FILES})

# Find external libraries
# find_file(
	# GLEW_DLL
	# "glew32.dll")

# add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
		   # COMMAND ${CMAKE_COMMAND} -E copy_if_different
		   # ${GLEW_DLL}
			# $<TARGET_FILE_DIR:${PROJECT_NAME}>)

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
	GLEW::GLEW)
target_link_libraries(
	${PROJECT_NAME}
	${LIBS})

# Define include directories
set(ADDITIONAL_INCLUDES
	${GLM_INCLUDE_DIR}
	${GLFW3_INCLUDE_DIR}
	${GLEW_INCLUDE_DIR})
target_include_directories(
	${PROJECT_NAME}
	PUBLIC
	"${CMAKE_SOURCE_DIR}/src"
	"${CMAKE_SOURCE_DIR}/include"
	${ADDITIONAL_INCLUDES})
