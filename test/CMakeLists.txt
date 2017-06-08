file(GLOB TEST_FILES "*.cpp")

# We need thread support
find_package(Threads REQUIRED)

# Enable ExternalProject CMake module
INCLUDE(ExternalProject)

# Set default ExternalProject root directory
SET_DIRECTORY_PROPERTIES(PROPERTIES EP_PREFIX ${CMAKE_BINARY_DIR}/third_party)

#Add Gtest project
ExternalProject_Add(
        gtest
        URL https://github.com/google/googletest/archive/release-1.7.0.zip
        # Disable install step
        INSTALL_COMMAND ""
        CMAKE_ARGS -DCMAKE_BUILD_TYPE=Release
)

ExternalProject_Get_Property(gtest binary_dir)
ExternalProject_Get_Property(gtest source_dir)
set(gtest_main_library ${binary_dir}/libgtest_main.a)
set(gtest_library ${binary_dir}/libgtest.a)
set(gtest_include_dir "${source_dir}/include")
include_directories(SYSTEM "${gtest_include_dir}")

# Files
file(GLOB TEST_FILES "*.cpp")
add_executable(runAllTests ${TEST_FILES})

add_dependencies(runAllTests gtest)

target_link_libraries(runAllTests ${gtest_library})
target_link_libraries(runAllTests ${gtest_main_library})
target_link_libraries (runAllTests ${CMAKE_THREAD_LIBS_INIT})
target_link_libraries (runAllTests graphtoolShared)
