#include "../include/PersistenceWorker.hpp"

PersistenceWorker::PersistenceWorker(
    Database& db,
    MessageQueue& q
)
    : database(db),
      queue(q) {}

void PersistenceWorker::start() {

    workerThread =
        std::thread(
            &PersistenceWorker::run,
            this
        );

    workerThread.detach();
}

void PersistenceWorker::run() {

    while (true) {

        auto msg = queue.pop();

        database.insertMessage(msg);
    }
}