# This is just a placeholder for CTests.
# Need to add real tests for each object in OpenGLPlayground.

add_executable(Empty EmptyTest.cpp)

# For the following to work, OpenGLPlayground must be converted to a library.
# Linking up all libraries (includes the coverage settings set by 'example' library)
target_link_libraries(Empty PRIVATE
  coverage_config
  PlaygroundEngine)

add_test(NAME empty_test COMMAND Empty)
