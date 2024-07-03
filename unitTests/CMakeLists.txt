#
# Lines inspired by https://google.github.io/googletest/quickstart-cmake.html
#

# Note: include(GoogleTest)and enable_testing() already done in top CMakeLists.txt

add_executable(unitTests unitTests.cpp)
target_link_libraries(unitTests GTest::gtest_main src pugixml sfml-graphics)
if (UNIX)
  target_link_options(unitTests PUBLIC -pthread)
endif()

# The next line enables CMake’s test runner to discover the tests included in the binary,
# using the GoogleTest CMake module (which was included in root CMakeLists.txt).


add_custom_target(copy-resources-test ALL
        COMMAND ${CMAKE_COMMAND} -E copy_directory_if_different ${CMAKE_SOURCE_DIR}/resources ${CMAKE_SOURCE_DIR}/out/build/x64-Debug/unitTests/resources)
add_dependencies(unitTests copy-resources-test)

add_custom_target(copy-resources-test ALL
        COMMAND ${CMAKE_COMMAND} -E copy_directory_if_different ${CMAKE_SOURCE_DIR}/resources C:/Users/romai/Bureau/Cours/JIN/CAASI/out/build/x64-Debug/unitTests/resources)
add_dependencies(unitTests copy-resources-test)



