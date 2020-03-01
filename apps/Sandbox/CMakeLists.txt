add_executable(Sandbox Sandbox.cpp)

# Linking up all libraries (includes the coverage settings set by 'example' library)
target_link_libraries(Sandbox PRIVATE
  PlaygroundEngine)
