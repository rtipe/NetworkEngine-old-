cmake_minimum_required(VERSION 3.22)
project(project)

set(CMAKE_CXX_STANDARD 20)

find_package(Threads REQUIRED)
find_package(jsoncpp CONFIG REQUIRED)

add_executable(project)

target_link_libraries(project PRIVATE JsonCpp::JsonCpp Threads::Threads)

add_subdirectory(NetworkEngine)
add_subdirectory(src)
add_subdirectory(Scripts)
