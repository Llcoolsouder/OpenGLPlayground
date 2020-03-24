add_executable(WindowTest WindowTest.cpp)

# Linking up all libraries (includes the coverage settings set by 'example' library)
target_link_libraries(WindowTest PRIVATE
  PlaygroundEngine)

add_test(NAME WindowTest COMMAND WindowTest)
