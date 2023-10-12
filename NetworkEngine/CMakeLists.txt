cmake_minimum_required(VERSION 3.13)

target_sources(project PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/ProjectInfo.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/Uniti.cpp"
)

target_include_directories(project PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}")

add_subdirectory(Event)
add_subdirectory(Object)
add_subdirectory(Script)
add_subdirectory(User)
add_subdirectory(Time)