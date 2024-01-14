cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 20)

project(client)

find_path(LibNL_INCLUDE_DIR netlink/netlink.h
    /usr/include
    /usr/include/libnl3
    /usr/local/include
    /usr/local/include/libnl3
)

find_library(LibNL_LIBRARY NAMES nl nl-3)
find_library(LibNL_GENL_LIBRARY NAMES nl-genl nl-genl-3)

add_executable(nl_client send/send.cpp)
add_executable(nl_server recv.cpp)

target_include_directories(nl_client PRIVATE ${LibNL_INCLUDE_DIR})
target_include_directories(nl_server PRIVATE ${LibNL_INCLUDE_DIR})

message(STATUS "LibNL_INCLUDE_DIR: ${LibNL_INCLUDE_DIR}")

target_link_libraries(nl_client PRIVATE ${LibNL_LIBRARY} ${LibNL_GENL_LIBRARY})
target_link_libraries(nl_server PRIVATE ${LibNL_LIBRARY} ${LibNL_GENL_LIBRARY})