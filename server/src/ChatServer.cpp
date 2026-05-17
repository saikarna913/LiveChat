#include "../include/ChatServer.hpp"
#include <string_view>
#include <string>
#include <iostream>
#include <cstdlib>

struct PerSocketData {
    std::string username;
    std::string roomId;
};

void ChatServer::run(int port) {

    uWS::App().ws<PerSocketData>("/*", {

        .open = [this](auto* ws) {
            std::cout << "Client connected\n";
        },

        .message =
        [this](auto* ws,
               std::string_view message,
               uWS::OpCode opCode) {

            auto* data = ws->getUserData();

            std::string msg(message);

            // First message = room join
            if (data->roomId.empty()) {

                data->roomId = "main";
                data->username =
                    "user_" +
                    std::to_string(rand() % 10000);

                roomManager.joinRoom(
                    data->roomId,
                    ws
                );

                return;
            }

            std::string formatted =
                data->username + ": " + msg;

            roomManager.broadcast(
                data->roomId,
                formatted
            );
        },

        .close =
        [this](auto* ws,
               int code,
               std::string_view msg) {

            auto* data = ws->getUserData();

            roomManager.leaveRoom(
                data->roomId,
                ws
            );

            std::cout << "Client disconnected\n";
        }

    }).listen(port,
        [port](auto* token) {

        if (token) {
            std::cout
                << "Server listening on port "
                << port
                << "\n";
        }
    }).run();
}
