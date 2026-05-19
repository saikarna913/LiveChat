#pragma once

#include "Database.hpp"
#include "MessageQueue.hpp"

#include <thread>

class PersistenceWorker {
public:

    PersistenceWorker(
        Database& db,
        MessageQueue& queue
    );

    void start();

private:

    void run();

    Database& database;

    MessageQueue& queue;

    std::thread workerThread;
};