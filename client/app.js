const ws =
    new WebSocket("ws://localhost:9001");

const messages =
    document.getElementById("messages");

ws.onmessage = (event) => {

    const div = document.createElement("div");

    div.innerText = event.data;

    messages.appendChild(div);
};

function sendMessage() {

    const input =
        document.getElementById("input");

    ws.send(input.value);

    input.value = "";
}
