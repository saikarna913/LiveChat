#pragma once

#include <string>

struct ClientSession {
    uint64_t userId;
    std::string username;
    std::string roomId;
};
