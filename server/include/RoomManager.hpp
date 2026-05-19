#pragma once

#include "Room.hpp"
#include "PerSocketData.hpp"

#include <unordered_map>
#include <memory>
#include <string>

class RoomManager {
public:

    using WebSocket =
        uWS::WebSocket<false, true, PerSocketData>;

    void joinRoom(
        const std::string& roomId,
        WebSocket* ws
    );

    void leaveRoom(
        const std::string& roomId,
        WebSocket* ws
    );

    void broadcastToRoom(
        const std::string& roomId,
        const std::string& msg
    );

private:

    std::unordered_map<
        std::string,
        std::unique_ptr<Room>
    > rooms;
};