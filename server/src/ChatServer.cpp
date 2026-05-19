#include "../include/ChatServer.hpp"

#include <iostream>
#include <ctime>

struct PerSocketData {

    std::string username;

    std::string roomId;
};

void ChatServer::run(int port) {

    persistenceWorker.start();

    uWS::App().ws<PerSocketData>("/*", {

        .open = [this](auto* ws) {

            std::cout
                << "Client connected\n";
        },

        .message =
        [this](auto* ws,
               std::string_view message,
               uWS::OpCode opCode) {

            auto* data =
                ws->getUserData();

            std::string msg(message);

            // JOIN ROOM
            if (msg.rfind("JOIN:", 0) == 0) {

                std::string roomId =
                    msg.substr(5);

                data->roomId = roomId;

                data->username =
                    "user_" +
                    std::to_string(
                        rand() % 10000
                    );

                roomManager.joinRoom(
                    roomId,
                    ws
                );

                ws->send(
                    "Joined room: " +
                    roomId,
                    uWS::OpCode::TEXT
                );

                return;
            }

            // SEND MESSAGE
            if (msg.rfind("MSG:", 0) == 0) {

                if (data->roomId.empty()) {

                    ws->send(
                        "Join room first",
                        uWS::OpCode::TEXT
                    );

                    return;
                }

                std::string text =
                    msg.substr(4);

                std::string formatted =
                    "[" +
                    data->roomId +
                    "] " +
                    data->username +
                    ": " +
                    text;

                roomManager.broadcastToRoom(
                    data->roomId,
                    formatted
                );

                // ASYNC PERSISTENCE
                PersistedMessage dbMsg {

                    .roomId =
                        data->roomId,

                    .username =
                        data->username,

                    .message =
                        text,

                    .timestamp =
                        static_cast<uint64_t>(
                            time(nullptr)
                        )
                };

                messageQueue.push(dbMsg);
            }
        },

        .close =
        [this](auto* ws,
               int code,
               std::string_view msg) {

            auto* data =
                ws->getUserData();

            roomManager.leaveRoom(
                data->roomId,
                ws
            );

            std::cout
                << "Client disconnected\n";
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