cmake_minimum_required(VERSION 3.16)

project(ChatServer)

set(CMAKE_CXX_STANDARD 17)

add_executable(chat_server

    src/main.cpp
    src/ChatServer.cpp
    src/Room.cpp
    src/RoomManager.cpp
    src/Database.cpp
    src/MessageQueue.cpp
    src/PersistenceWorker.cpp
)

target_include_directories(chat_server PRIVATE

    include

    uWebSockets/src

    uWebSockets/uSockets/src
)

target_link_libraries(chat_server

    sqlite3

    ssl
    crypto
    z

    pthread
)