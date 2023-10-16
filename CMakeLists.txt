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

target_link_libraries(project PRIVATE jsoncpp_static jsoncpp_object jsoncpp_lib)


add_subdirectory(NetworkEngine)
add_subdirectory(src)
add_subdirectory(Scripts)

file(COPY ${CMAKE_SOURCE_DIR}/json DESTINATION .)

install(TARGETS project
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

install(DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/json" DESTINATION ${CMAKE_INSTALL_BINDIR})

include(InstallRequiredSystemLibraries)

set(CPACK_PACKAGE_NAME "rtype-server")
set(CPACK_PACKAGE_VERSION "1.0.0")
set(CPACK_PACKAGE_DESCRIPTION "Description de MonProjet")
set(CPACK_PACKAGE_INSTALL_DIRECTORY "RTYPE-SERVER")
set(CPACK_PACKAGE_CONTACT "younes1.bahri@epitech.eu")
set(CPACK_DEBIAN_PACKAGE_MAINTAINER "${CPACK_PACKAGE_CONTACT}")

if(WIN32)
    set(CPACK_GENERATOR "NSIS")
elseif(APPLE)
    set(CPACK_GENERATOR "DragNDrop")
else()
    set(CPACK_GENERATOR "DEB;RPM")
endif()

include(CPack)
