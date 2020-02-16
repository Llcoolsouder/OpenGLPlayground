add_executable(MeshTest MeshTest.cpp)

# Linking up all libraries (includes the coverage settings set by 'example' library)
target_link_libraries(MeshTest PRIVATE
  PlaygroundEngine)

add_test(NAME MeshTest COMMAND MeshTest)
