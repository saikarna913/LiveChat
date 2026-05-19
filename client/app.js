const status = document.getElementById("status");
const messages = document.getElementById("messages");

const ws = new WebSocket("ws://localhost:9001");

ws.onopen = () => {
    status.innerText = "Connected to server on ws://localhost:9001";
};

ws.onerror = () => {
    status.innerText = "WebSocket error: could not connect to server";
    status.style.color = "red";
};

ws.onclose = () => {
    status.innerText = "WebSocket connection closed";
    status.style.color = "red";
};

ws.onmessage = (event) => {
    const div = document.createElement("div");
    div.className = "message";
    div.innerText = event.data;
    messages.appendChild(div);
};

function joinRoom() {

    const room =
        document.getElementById("room");

    ws.send("JOIN:" + room.value);
}

function sendMessage() {

    const input =
        document.getElementById("input");

    ws.send("MSG:" + input.value);

    input.value = "";
}