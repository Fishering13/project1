find_package(GTest QUIET)
if(NOT GTest_FOUND)
  include(FetchContent)
  FetchContent_Declare(googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG release-1.12.1 GIT_SHALLOW TRUE)
  set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
  FetchContent_MakeAvailable(googletest)
endif()
add_executable(matrix_tests test_matrix.cpp)
target_link_libraries(matrix_tests PRIVATE matrix GTest::gtest_main)
include(GoogleTest)
gtest_discover_tests(matrix_tests)
