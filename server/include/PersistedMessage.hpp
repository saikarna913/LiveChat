#pragma once

#include <string>
#include <cstdint>

struct PersistedMessage {

    std::string roomId;

    std::string username;

    std::string message;

    uint64_t timestamp;
};