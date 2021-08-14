cmake_minimum_required(VERSION 3.20)
project(nes_cloud)

set(CMAKE_CXX_STANDARD 17)

file(GLOB_RECURSE SOURCE_FILE "src/*.cpp")
file(GLOB_RECURSE HEADER_FILE "include/*.h")

add_executable(nes_cloud ${SOURCE_FILE})
target_include_directories(nes_cloud PRIVATE
    ${PROJECT_SOURCE_DIR}/include
)
target_link_libraries(nes_cloud
    pthread
)