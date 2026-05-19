#pragma once

#include "RoomManager.hpp"
#include "Database.hpp"
#include "MessageQueue.hpp"
#include "PersistenceWorker.hpp"

class ChatServer {
public:

    void run(int port);

private:

    RoomManager roomManager;

    Database database{"chat.db"};

    MessageQueue messageQueue;

    PersistenceWorker persistenceWorker{
        database,
        messageQueue
    };
};