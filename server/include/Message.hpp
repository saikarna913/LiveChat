 #pragma once

#include <string>
#include <cstdint>

struct Message {
    std::string username;
    std::string text;
    uint64_t timestamp;
};
