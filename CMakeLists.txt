cmake_minimum_required(VERSION 3.0 FATAL_ERROR)
project(OpenGLPlayground)

# Add files
file(GLOB_RECURSE
	SOURCE_FILES
	${CMAKE_SOURCE_DIRS}/src/*.cpp)	
file(GLOB_RECURSE
	HEADER_FILES
	${CMAKE_SOURCE_DIRS}/include/*.h)

# Create executable	
add_executable(
	${PROJECT_NAME}
	${HEADER_FILES}
	${SOURCE_FILES})

# Add project filters	
source_group(
	"Source"
	FILES
	${SOURCE_FILES})
source_group(
	"Headers"
	FILES
	${HEADER_FILES})
	
# Find external libraries
set(CMAKE_MODULE_PATH
	${CMAKE_MODULE_PATH}
	"${CMAKE_SOURCE_DIR}/cmake/")
find_package(OpenGL REQUIRED)
find_package(GLM REQUIRED)
message(STATUS
	"GLM included at ${GLM_INCLUDE_DIR}")
find_package(GLFW3 REQUIRED)
message(STATUS
	"GLFW3 included at ${GLFW3_INCLUDE_DIR}")
find_package(GLEW REQUIRED)
message(STATUS	
	"GLEW included at ${GLEW_INCLUDE_DIR}")
	
# Link libraries
set(LIBS
	opengl32
	glm
	glfw3
	glew)
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
	"${CMAKE_SOURCE_DIRS}/src/"
	"${CMAKE_SOURCE_DIRS}/include/"
	${ADDITIONAL_INCLUDES})