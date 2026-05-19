#pragma once

#include "PersistedMessage.hpp"

#include <sqlite3.h>
#include <string>

class Database {
public:

    Database(const std::string& file);

    ~Database();

    void insertMessage(
        const PersistedMessage& msg
    );

private:

    sqlite3* db;
};