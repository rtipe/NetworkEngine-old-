cmake_minimum_required(VERSION 3.13)

target_sources(project PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/EventManager.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/sendEventManager.cpp"
)

target_include_directories(project PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}")