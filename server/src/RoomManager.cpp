#include "RoomManager.hpp"
#include <iostream>

void RoomManager::joinRoom(const std::string& roomId, WebSocket* ws) {
    rooms[roomId].insert(ws);
    std::cout << "WebSocket joined room: " << roomId << std::endl;
}

void RoomManager::leaveRoom(const std::string& roomId, WebSocket* ws) {
    auto it = rooms.find(roomId);
    if (it != rooms.end()) {
        it->second.erase(ws);
        if (it->second.empty()) {
            rooms.erase(it);
        }
    }
    std::cout << "WebSocket left room: " << roomId << std::endl;
}

void RoomManager::broadcast(const std::string& roomId, const std::string& message) {
    auto it = rooms.find(roomId);
    if (it != rooms.end()) {
        for (auto* ws : it->second) {
            ws->send(message, uWS::OpCode::TEXT);
        }
    }
}
