add_library(coverage_config INTERFACE)

option(CODE_COVERAGE "Enable coverage reporting" OFF)
set(
  USE_CODE_COVERAGE
  $<AND:$<BOOL:${CODE_COVERAGE}>, $<IN_LIST:CMAKE_CXX_COMPILER_ID,"GNU;Clang">>)

if(USE_CODE_COVERAGE)
  message("Using CodeCov.")
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
  endif(CMAKE_VERSION VERSION_GREATER_EQUAL 3.13)
endif(USE_CODE_COVERAGE)