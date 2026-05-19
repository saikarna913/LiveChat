CREATE TABLE messages (

    id INTEGER PRIMARY KEY AUTOINCREMENT,

    room_id TEXT NOT NULL,

    username TEXT NOT NULL,

    message TEXT NOT NULL,

    timestamp INTEGER NOT NULL
);