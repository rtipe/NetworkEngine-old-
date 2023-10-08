cmake_minimum_required(VERSION 3.13)

target_sources(project PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/Clock.cpp"
)

target_include_directories(project PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}")