#ifndef EMBEDDED_UI_WEB_PAGE_H
#define EMBEDDED_UI_WEB_PAGE_H


#include <Arduino.h>


static const char WEB_PAGE[] PROGMEM = R"HTML(
<!DOCTYPE html>
<html lang="pt-BR">

<head>

    <meta charset="UTF-8">

    <meta
        name="viewport"
        content="width=device-width, initial-scale=1.0"
    >

    <title>EmbeddedUI WebSocket</title>

    <style>

        :root
        {
            color-scheme: dark;
        }

        *
        {
            box-sizing: border-box;
        }

        body
        {
            margin: 0;
            min-height: 100vh;

            display: flex;
            align-items: center;
            justify-content: center;

            background:
                radial-gradient(
                    circle at top,
                    #18263b,
                    #080c12 60%
                );

            color: #eaf6ff;

            font-family:
                Arial,
                Helvetica,
                sans-serif;
        }

        .panel
        {
            width: min(
                92vw,
                520px
            );

            padding: 24px;

            border: 1px solid #28415f;
            border-radius: 18px;

            background:
                rgba(
                    7,
                    13,
                    22,
                    0.94
                );

            box-shadow:
                0 20px 60px
                rgba(
                    0,
                    0,
                    0,
                    0.55
                );
        }

        h1
        {
            margin:
                0
                0
                6px;

            font-size: 1.3rem;
        }

        .status
        {
            margin-bottom: 18px;

            color: #8fa9c4;

            font-size: 0.85rem;
        }

        .status.connected
        {
            color: #64e6a3;
        }

        .status.disconnected
        {
            color: #ff7c7c;
        }

        .display-shell
        {
            margin-bottom: 22px;
            padding: 14px;

            border-radius: 14px;

            background: #020407;

            box-shadow:
                inset 0 0 0 1px #25374c,
                inset 0 0 28px
                rgba(
                    0,
                    136,
                    255,
                    0.13
                );
        }

        #display
        {
            width: 100%;
            aspect-ratio: 1 / 1;

            padding: 12px;

            overflow: hidden;

            border: 2px solid #3a648a;
            border-radius: 5px;

            background:
                linear-gradient(
                    150deg,
                    #06101c,
                    #020508
                );

            color: #dff8ff;

            font-family:
                "Courier New",
                monospace;

            font-size:
                clamp(
                    13px,
                    3.4vw,
                    18px
                );

            line-height: 1.5;

            text-shadow:
                0 0 7px
                rgba(
                    98,
                    210,
                    255,
                    0.6
                );
        }

        .display-line
        {
            min-height: 1.5em;

            display: flex;
            align-items: center;
            justify-content: space-between;

            padding:
                1px
                5px;

            white-space: pre;
        }

        .display-line.selected
        {
            color: #00131e;
            background: #76ddff;

            text-shadow: none;
        }

        .display-line.editing
        {
            outline:
                1px dashed
                currentColor;

            outline-offset: -3px;
        }

        .display-line.disabled
        {
            opacity: 0.45;
        }

        .display-empty
        {
            color: #577187;
        }

        .controls
        {
            display: grid;

            grid-template-columns:
                repeat(
                    2,
                    minmax(
                        0,
                        1fr
                    )
                );

            gap: 12px;
        }

        button
        {
            min-height: 62px;

            border: 1px solid #386a91;
            border-radius: 12px;

            background:
                linear-gradient(
                    180deg,
                    #17324a,
                    #0b1b29
                );

            color: #effaff;

            font-size: 1rem;
            font-weight: 700;

            cursor: pointer;

            touch-action: manipulation;

            box-shadow:
                0 6px 14px
                rgba(
                    0,
                    0,
                    0,
                    0.3
                );
        }

        button:hover
        {
            background:
                linear-gradient(
                    180deg,
                    #215070,
                    #10283a
                );
        }

        button:active
        {
            transform:
                translateY(
                    2px
                );

            box-shadow:
                0 2px 7px
                rgba(
                    0,
                    0,
                    0,
                    0.4
                );
        }

        button:disabled
        {
            cursor: not-allowed;
            opacity: 0.45;
        }

        .command-log
        {
            margin-top: 16px;

            color: #6f8aa3;

            font-family:
                monospace;

            font-size: 0.8rem;
        }

    </style>

</head>

<body>

    <main class="panel">

        <h1>EmbeddedUI</h1>

        <div
            id="status"
            class="status disconnected"
        >
            WebSocket desconectado
        </div>

        <div class="display-shell">

            <div id="display">

                <div class="display-empty">
                    Aguardando o display...
                </div>

            </div>

        </div>

        <div class="controls">

            <button
                type="button"
                data-command="CCW"
            >
                ◀ CCW
            </button>

            <button
                type="button"
                data-command="CW"
            >
                CW ▶
            </button>

            <button
                type="button"
                data-command="ENTER"
            >
                ENTER
            </button>

            <button
                type="button"
                data-command="BACK"
            >
                BACK
            </button>

        </div>

        <div
            id="commandLog"
            class="command-log"
        >
            Nenhum comando enviado.
        </div>

    </main>

    <script>

        const display =
            document.getElementById(
                "display"
            );

        const status =
            document.getElementById(
                "status"
            );

        const commandLog =
            document.getElementById(
                "commandLog"
            );

        const buttons =
            document.querySelectorAll(
                "button[data-command]"
            );


        let socket = null;

        let reconnectTimer = null;


        function setConnected(
            connected
        )
        {

            status.textContent =
                connected
                    ? "WebSocket conectado"
                    : "WebSocket desconectado";


            status.classList.toggle(
                "connected",
                connected
            );


            status.classList.toggle(
                "disconnected",
                !connected
            );


            buttons.forEach(
                button =>
                {
                    button.disabled =
                        !connected;
                }
            );

        }


        function connectWebSocket()
        {

            clearTimeout(
                reconnectTimer
            );


            const url =
                "ws://" +
                window.location.hostname +
                ":81/";


            socket =
                new WebSocket(
                    url
                );


            socket.addEventListener(
                "open",
                () =>
                {

                    setConnected(
                        true
                    );


                    socket.send(
                        "STATE"
                    );

                }
            );


            socket.addEventListener(
                "close",
                () =>
                {

                    setConnected(
                        false
                    );


                    reconnectTimer =
                        setTimeout(
                            connectWebSocket,
                            1500
                        );

                }
            );


            socket.addEventListener(
                "error",
                () =>
                {

                    socket.close();

                }
            );


            socket.addEventListener(
                "message",
                event =>
                {

                    try
                    {

                        const data =
                            JSON.parse(
                                event.data
                            );


                        if(
                            data.type ===
                            "display"
                        )
                        {

                            renderDisplay(
                                data
                            );

                        }

                    }
                    catch(error)
                    {

                        console.error(
                            "Mensagem inválida:",
                            event.data,
                            error
                        );

                    }

                }
            );

        }


        function sendCommand(
            command
        )
        {

            if(
                !socket ||
                socket.readyState !==
                    WebSocket.OPEN
            )
            {
                return;
            }


            socket.send(
                command
            );


            commandLog.textContent =
                "Comando enviado: " +
                command;

        }


        function renderDisplay(
            data
        )
        {

            display.replaceChildren();


            if(
                !Array.isArray(
                    data.lines
                ) ||
                data.lines.length === 0
            )
            {

                const empty =
                    document.createElement(
                        "div"
                    );


                empty.className =
                    "display-empty";


                empty.textContent =
                    "Tela vazia";


                display.appendChild(
                    empty
                );


                return;

            }


            data.lines.forEach(
                item =>
                {

                    const line =
                        document.createElement(
                            "div"
                        );


                    line.className =
                        "display-line";


                    if(item.selected)
                    {

                        line.classList.add(
                            "selected"
                        );

                    }


                    if(item.editing)
                    {

                        line.classList.add(
                            "editing"
                        );

                    }


                    if(item.enabled === false)
                    {

                        line.classList.add(
                            "disabled"
                        );

                    }


                    line.textContent =
                        item.text || "";


                    display.appendChild(
                        line
                    );

                }
            );

        }


        buttons.forEach(
            button =>
            {

                button.addEventListener(
                    "click",
                    () =>
                    {

                        sendCommand(
                            button.dataset.command
                        );

                    }
                );

            }
        );


        document.addEventListener(
            "keydown",
            event =>
            {

                const commandMap =
                {
                    ArrowRight: "CW",
                    ArrowDown: "CW",

                    ArrowLeft: "CCW",
                    ArrowUp: "CCW",

                    Enter: "ENTER",
                    Escape: "BACK",
                    Backspace: "BACK"
                };


                const command =
                    commandMap[
                        event.key
                    ];


                if(!command)
                    return;


                event.preventDefault();


                sendCommand(
                    command
                );

            }
        );


        setConnected(
            false
        );


        connectWebSocket();

    </script>

</body>

</html>
)HTML";


#endif