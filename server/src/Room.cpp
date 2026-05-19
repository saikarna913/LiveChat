#include "../include/Room.hpp"

Room::Room(const std::string& id)
    : roomId(id) {}

void Room::addClient(Room::WebSocket* ws) {
    clients.insert(ws);
}

void Room::removeClient(Room::WebSocket* ws) {
    clients.erase(ws);
}

void Room::broadcast(
    const std::string& msg
) {
    for (auto client : clients) {
        client->send(
            msg,
            uWS::OpCode::TEXT
        );
    }
}

bool Room::empty() const {
    return clients.empty();
}

size_t Room::size() const {
    return clients.size();
}

const std::string&
Room::getId() const {
    return roomId;
}