#pragma once

#include "RoomManager.hpp"

class ChatServer {
public:
    void run(int port);

private:
    RoomManager roomManager;
};
