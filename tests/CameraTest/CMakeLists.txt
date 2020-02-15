# This is just a placeholder for CTests.
# Need to add real tests for each object in OpenGLPlayground.

add_executable(CameraTest CameraTest.cpp)

# For the following to work, OpenGLPlayground must be converted to a library.
# Linking up all libraries (includes the coverage settings set by 'example' library)
target_link_libraries(CameraTest PRIVATE
  PlaygroundEngine)

add_test(NAME CameraTest COMMAND CameraTest)
