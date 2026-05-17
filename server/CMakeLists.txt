cmake_minimum_required(VERSION 3.16)

project(ChatServer)

set(CMAKE_CXX_STANDARD 17)

add_executable(chat_server
    src/main.cpp
    src/ChatServer.cpp
    src/RoomManager.cpp
)

target_include_directories(chat_server PRIVATE
    include
    uWebSockets/src
    uWebSockets/uSockets/src
)

# Link the compiled uSockets library
target_link_libraries(chat_server
    ${CMAKE_CURRENT_SOURCE_DIR}/uWebSockets/uSockets/uSockets.a
    ssl
    crypto
    z
    pthread
    dl
)
