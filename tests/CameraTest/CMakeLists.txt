add_executable(CameraTest CameraTest.cpp)

# Linking up all libraries (includes the coverage settings set by 'example' library)
target_link_libraries(CameraTest PRIVATE
  PlaygroundEngine)

add_test(NAME CameraTest COMMAND CameraTest)
