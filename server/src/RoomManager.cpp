#include "../include/RoomManager.hpp"

#include <iostream>

void RoomManager::joinRoom(
    const std::string& roomId,
    RoomManager::WebSocket* ws
) {

    if (!rooms.count(roomId)) {

        rooms[roomId] =
            std::make_unique<Room>(roomId);

        std::cout
            << "Created room: "
            << roomId
            << "\n";
    }

    rooms[roomId]->addClient(ws);

    std::cout
        << "User joined room "
        << roomId
        << " | users="
        << rooms[roomId]->size()
        << "\n";
}

void RoomManager::leaveRoom(
    const std::string& roomId,
    RoomManager::WebSocket* ws
) {

    if (!rooms.count(roomId))
        return;

    rooms[roomId]->removeClient(ws);

    std::cout
        << "User left room "
        << roomId
        << " | users="
        << rooms[roomId]->size()
        << "\n";

    if (rooms[roomId]->empty()) {

        rooms.erase(roomId);

        std::cout
            << "Deleted empty room: "
            << roomId
            << "\n";
    }
}

void RoomManager::broadcastToRoom(
    const std::string& roomId,
    const std::string& msg
) {

    if (!rooms.count(roomId))
        return;

    rooms[roomId]->broadcast(msg);
}