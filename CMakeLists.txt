cmake_minimum_required(VERSION 3.22)
project(NetworkEngine)

set(CMAKE_CXX_STANDARD 20)

find_package(jsoncpp CONFIG REQUIRED)

include_directories(src)

add_executable(NetworkEngine
        src/Uniti.cpp
        src/Uniti.hpp src/ProjectInfo.hpp
        src/ProjectInfo.cpp
        src/User/UserManager.hpp
        src/User/UserManager.cpp
        src/User/IUser.hpp
        src/Event/EventManager.hpp
        src/Event/EventManager.cpp
        src/Object/ObjectManager.hpp
        src/Object/ObjectManager.cpp
        src/Object/Object.hpp
        src/Object/Object.cpp
        src/Object/Transform/Transform.hpp
        src/Object/Transform/Transform.cpp
        src/Object/Transform/Position.hpp
        src/Object/Transform/Scale.hpp
        src/Object/Transform/Rotation.hpp
        src/Script/IScript.hpp
        src/Script/ScriptFactory.hpp
        src/Script/ScriptManager.hpp
        src/Object/Transform/Position.cpp
        src/Object/Transform/Rotation.cpp
        src/Object/Transform/Scale.cpp
        src/Script/ScriptFactory.cpp
        src/Script/ScriptManager.cpp
        src/Event/sendEventManager.hpp
        src/Event/sendEventManager.cpp
        src/User/AUser.hpp
        src/User/AUser.cpp test.cpp)

target_link_libraries(NetworkEngine PRIVATE JsonCpp::JsonCpp)
