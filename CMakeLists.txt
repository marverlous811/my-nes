cmake_minimum_required(VERSION 3.19)
project(nes_cloud)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_VERBOSE_MAKEFILE  ON)

if(APPLE)
    if(DEFINED ENV{VCPKG_ROOT})
        set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake"
                CACHE STRING "")
        message("INFO VCPKG CMAKE_TOOLCHAIN_FILE = ${CMAKE_TOOLCHAIN_FILE}")
        set(CMAKE_PREFIX_PATH "$ENV{VCPKG_ROOT}/installed/x64-osx")
    else()
        message("INFO default tool chain")
    endif()
endif()

file(GLOB_RECURSE SOURCE_FILE "src/*.cpp")
file(GLOB_RECURSE HEADER_FILE "include/*.h")
file(GLOB_RECURSE TEST_FILE "test/*.cpp")

find_package(GTest CONFIG REQUIRED)
enable_testing()

add_executable(nes_cloud ${SOURCE_FILE})
target_include_directories(nes_cloud PUBLIC
    ${PROJECT_SOURCE_DIR}/include
)
target_link_libraries(nes_cloud
    pthread
)

add_library(nes-lib ${SOURCE_FILE})
target_include_directories(nes-lib PUBLIC
    ${PROJECT_SOURCE_DIR}/include
)

add_executable(nes-test ${TEST_FILE})
add_dependencies( nes-test nes-lib )
target_include_directories(nes-test PUBLIC
    ${PROJECT_SOURCE_DIR}/include
)
target_link_libraries(nes-test PRIVATE
    GTest::gmock
    GTest::gtest
    GTest::gmock_main
    GTest::gtest_main
    nes-lib
)