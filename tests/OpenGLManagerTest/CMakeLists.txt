add_executable(OpenGLManagerTest OpenGLManagerTest.cpp)

# Linking up all libraries (includes the coverage settings set by 'example' library)
target_link_libraries(OpenGLManagerTest PRIVATE
  PlaygroundEngine)

add_test(NAME OpenGLManagerTest COMMAND OpenGLManagerTest)
