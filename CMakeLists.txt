cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 20)

project(client)

find_path(LibNL_INCLUDE_DIR netlink/netlink.h
    /usr/include
    /usr/include/libnl3
    /usr/local/include
    /usr/local/include/libnl3
)

include_directories(${CMAKE_SOURCE_DIR}/include)

find_library(LibNL_LIBRARY NAMES nl nl-3)

add_executable(nl_client send/send.cpp)
add_executable(nl_server recv/recv.cpp)

target_include_directories(nl_client PRIVATE ${LibNL_INCLUDE_DIR})
target_include_directories(nl_server PRIVATE ${LibNL_INCLUDE_DIR})

message(STATUS "LibNL_INCLUDE_DIR: ${LibNL_INCLUDE_DIR}")

target_link_libraries(nl_client PRIVATE ${LibNL_LIBRARY})
target_link_libraries(nl_server PRIVATE ${LibNL_LIBRARY})


# Tests
enable_testing()

add_executable(ConnectionTest tests/ConnectionTest.cpp)
target_include_directories(ConnectionTest PRIVATE ${LibNL_INCLUDE_DIR})
target_link_libraries(ConnectionTest PRIVATE ${LibNL_LIBRARY})
add_test(NAME ConnectionTest COMMAND ConnectionTest)

add_executable(MessageTest tests/MessageTest.cpp)
target_include_directories(MessageTest PRIVATE ${LibNL_INCLUDE_DIR})
target_link_libraries(MessageTest PRIVATE ${LibNL_LIBRARY})
add_test(NAME MessageTest COMMAND MessageTest)