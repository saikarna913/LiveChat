#include "../include/MessageQueue.hpp"

void MessageQueue::push(
    const PersistedMessage& msg
) {

    {
        std::lock_guard lock(mutex);

        queue.push(msg);
    }

    cv.notify_one();
}

PersistedMessage MessageQueue::pop() {

    std::unique_lock lock(mutex);

    cv.wait(lock, [this] {

        return !queue.empty();
    });

    auto msg = queue.front();

    queue.pop();

    return msg;
}