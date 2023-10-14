cmake_minimum_required(VERSION 3.13)

target_sources(project PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/BasicEnemy.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/EnemiesHandler.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/Kamikaze.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/Sniper.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/Boss.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/Tank.cpp"
)

target_include_directories(project PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}")