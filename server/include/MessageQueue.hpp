#pragma once
#include "PersistedMessage.hpp"
#include <queue>
#include <mutex>
#include <condition_variable>

class MessageQueue {
public:

    void push(
        const PersistedMessage& msg
    );

    PersistedMessage pop();

private:

    std::queue<PersistedMessage> queue;

    std::mutex mutex;

    std::condition_variable cv;
};