#pragma once

#include <unordered_set>
#include <string>
#include "App.h"
#include "PerSocketData.hpp"

class Room {
public:

    using WebSocket =
        uWS::WebSocket<false, true, PerSocketData>;

    explicit Room(const std::string& id);

    void addClient(WebSocket* ws);

    void removeClient(WebSocket* ws);

    void broadcast(const std::string& msg);

    bool empty() const;

    size_t size() const;

    const std::string& getId() const;

private:

    std::string roomId;

    std::unordered_set<WebSocket*> clients;
};