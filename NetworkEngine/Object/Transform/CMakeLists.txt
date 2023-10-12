cmake_minimum_required(VERSION 3.13)

target_sources(project PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/Position.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/Rotation.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/Scale.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/Transform.cpp"
)

target_include_directories(project PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}")