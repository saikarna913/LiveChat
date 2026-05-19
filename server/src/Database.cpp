#include "../include/Database.hpp"

#include <iostream>

Database::Database(
    const std::string& file
) {

    if (sqlite3_open(
        file.c_str(),
        &db
    )) {

        std::cerr
            << "Failed to open DB\n";
    }
}

Database::~Database() {

    sqlite3_close(db);
}

void Database::insertMessage(
    const PersistedMessage& msg
) {

    const char* sql =
        "INSERT INTO messages "
        "(room_id, username, message, timestamp)"
        "VALUES (?, ?, ?, ?);";

    sqlite3_stmt* stmt;

    sqlite3_prepare_v2(
        db,
        sql,
        -1,
        &stmt,
        nullptr
    );

    sqlite3_bind_text(
        stmt,
        1,
        msg.roomId.c_str(),
        -1,
        SQLITE_TRANSIENT
    );

    sqlite3_bind_text(
        stmt,
        2,
        msg.username.c_str(),
        -1,
        SQLITE_TRANSIENT
    );

    sqlite3_bind_text(
        stmt,
        3,
        msg.message.c_str(),
        -1,
        SQLITE_TRANSIENT
    );

    sqlite3_bind_int64(
        stmt,
        4,
        msg.timestamp
    );

    sqlite3_step(stmt);

    sqlite3_finalize(stmt);
}