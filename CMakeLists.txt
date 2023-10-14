cmake_minimum_required(VERSION 3.22)
project(project)

set(CMAKE_CXX_STANDARD 20)

include(FetchContent)

message(STATUS "Fetching JSONCPP")

FetchContent_Declare(JSONCpp
        GIT_REPOSITORY https://github.com/open-source-parsers/jsoncpp.git
        GIT_TAG 1.9.5)
FetchContent_MakeAvailable(JSONCpp)

FetchContent_Declare(
        Boost
        URL "https://github.com/boostorg/boost/releases/download/boost-1.83.0/boost-1.83.0.tar.xz"
        DOWNLOAD_EXTRACT_TIMESTAMP ON
)

set(BOOST_RUNTIME_LINK static)
set(BOOST_INCLUDE_LIBRARIES
        asio
        assert
        align
        array

        bind

        coroutine
        config
        context
        core
        chrono

        date_time

        exception

        function

        move

        system
        smart_ptr

        throw_exception
        type_traits
        lockfree
        utility
)
FetchContent_MakeAvailable(Boost)

find_package(Threads REQUIRED)

add_executable(project)

foreach(lib ${BOOST_INCLUDE_LIBRARIES})
    target_link_libraries(
            project
            PRIVATE
            Boost::${lib}
    )
endforeach()


target_link_libraries(project PRIVATE Threads::Threads)

target_link_libraries(project PRIVATE jsoncpp_lib)


add_subdirectory(NetworkEngine)
add_subdirectory(src)
add_subdirectory(Scripts)
