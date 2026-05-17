#pragma once
#include <unordered_map>
#include <unordered_set>
#include <string>
#include "App.h"

// Forward declare PerSocketData (defined in ChatServer.cpp)
struct PerSocketData;

class RoomManager {
public:
    using WebSocket = uWS::WebSocket<false, true, PerSocketData>;

    void joinRoom(const std::string& roomId, WebSocket* ws);

    void leaveRoom(const std::string& roomId, WebSocket* ws);

    void broadcast(const std::string& roomId, const std::string& message);

private:
    std::unordered_map<
        std::string,
        std::unordered_set<WebSocket*>>
    rooms;
};
