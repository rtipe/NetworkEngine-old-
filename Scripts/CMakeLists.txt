cmake_minimum_required(VERSION 3.13)

target_sources(project PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/Missile.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/Entity.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/VesselAlly.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/UserController.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/VesselHeal.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/VesselWeapon.cpp"
)

target_include_directories(project PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}")

add_subdirectory(Enemies)