#ifndef HIERARCHY_WEB_SOCKET_MENU_WEB_PAGE_H
#define HIERARCHY_WEB_SOCKET_MENU_WEB_PAGE_H


#include <Arduino.h>


static const char WEB_PAGE[] PROGMEM = R"HTML(
<!DOCTYPE html>
<html lang="pt-BR">

<head>

    <meta charset="UTF-8">

    <meta
        name="viewport"
        content="width=device-width, initial-scale=1"
    >

    <title>EmbeddedUI</title>

    <style>

        *
        {
            box-sizing: border-box;
        }

        body
        {
            margin: 0;
            min-height: 100vh;

            background: #0b1118;
            color: #edf5ff;

            font-family:
                Arial,
                sans-serif;
        }

        main
        {
            width: min(94%, 720px);

            margin: auto;
            padding: 24px 0;
        }

        h1
        {
            margin: 0;
            font-size: 1.35rem;
        }

        #status
        {
            margin: 6px 0 20px;

            color: #ff8181;
            font-size: 0.85rem;
        }

        #status.connected
        {
            color: #68e5a3;
        }

        .menu-panel
        {
            min-height: 240px;

            padding: 16px;

            border: 1px solid #294158;
            border-radius: 14px;

            background: #111b25;
        }

        ul
        {
            margin: 0;
            padding: 0;

            list-style: none;
        }

        ul ul
        {
            margin-left: 15px;
            padding-left: 15px;

            border-left: 1px solid #35516b;
        }

        li
        {
            margin: 6px 0;
        }

        .item
        {
            min-height: 38px;

            display: flex;
            align-items: center;
            justify-content: space-between;

            gap: 12px;

            padding: 8px 10px;

            border-radius: 8px;

            background: #172431;
        }

        .item.folder
        {
            background: #1c3042;
            font-weight: bold;
        }

        .item.action
        {
            color: #a8bfd2;
        }

        .item.disabled
        {
            opacity: 0.45;
        }

        .value
        {
            min-width: 78px;

            padding: 4px 8px;

            border-radius: 5px;

            background: #07121c;
            color: #76dcff;

            font-family:
                "Courier New",
                monospace;

            text-align: right;
        }

        .controls
        {
            display: grid;

            grid-template-columns:
                repeat(2, 1fr);

            gap: 12px;

            margin-top: 18px;
        }

        button
        {
            min-height: 58px;

            border: 1px solid #3d6687;
            border-radius: 10px;

            background: #17344b;
            color: white;

            font-size: 1rem;
            font-weight: bold;

            cursor: pointer;
            touch-action: manipulation;
        }

        button:active
        {
            transform: translateY(2px);
        }

        button:disabled
        {
            cursor: not-allowed;
            opacity: 0.4;
        }

        #command
        {
            margin-top: 14px;

            color: #71899f;
            font-family: monospace;
            font-size: 0.82rem;
        }

    </style>

</head>

<body>

    <main>

        <h1>EmbeddedUI — Hierarquia do menu</h1>

        <div id="status">
            WebSocket desconectado
        </div>

        <section class="menu-panel">

            <div id="menu">
                Aguardando dados...
            </div>

        </section>

        <section class="controls">

            <button data-command="CCW">
                ◀ CCW
            </button>

            <button data-command="CW">
                CW ▶
            </button>

            <button data-command="ENTER">
                ENTER
            </button>

            <button data-command="BACK">
                BACK
            </button>

        </section>

        <div id="command">
            Nenhum comando enviado.
        </div>

    </main>

    <script>

        const statusElement =
            document.getElementById(
                "status"
            );

        const menuElement =
            document.getElementById(
                "menu"
            );

        const commandElement =
            document.getElementById(
                "command"
            );

        const buttons =
            document.querySelectorAll(
                "button[data-command]"
            );


        let socket;

        let reconnectTimer;


        function setConnected(
            connected
        )
        {

            statusElement.textContent =
                connected
                ?
                "WebSocket conectado"
                :
                "WebSocket desconectado";


            statusElement.classList.toggle(
                "connected",
                connected
            );


            buttons.forEach(
                button =>
                {

                    button.disabled =
                        !connected;

                }
            );

        }


        function connect()
        {

            clearTimeout(
                reconnectTimer
            );


            socket =
                new WebSocket(
                    "ws://" +
                    window.location.hostname +
                    ":81/"
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
                            connect,
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

                        const message =
                            JSON.parse(
                                event.data
                            );


                        if(
                            message.type ===
                            "menuHierarchy"
                        )
                        {

                            renderMenu(
                                message.items || []
                            );

                        }

                    }
                    catch(error)
                    {

                        console.error(
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


            commandElement.textContent =
                "Comando enviado: " +
                command;

        }


        function renderMenu(
            items
        )
        {

            menuElement.replaceChildren();


            if(
                !Array.isArray(items) ||
                items.length === 0
            )
            {

                menuElement.textContent =
                    "Menu vazio";


                return;

            }


            menuElement.appendChild(
                createList(
                    items
                )
            );

        }


        function createList(
            items
        )
        {

            const list =
                document.createElement(
                    "ul"
                );


            items.forEach(
                item =>
                {

                    const listItem =
                        document.createElement(
                            "li"
                        );


                    const row =
                        document.createElement(
                            "div"
                        );


                    row.className =
                        "item " +
                        (
                            item.nodeType ||
                            ""
                        );


                    if(
                        item.enabled === false
                    )
                    {

                        row.classList.add(
                            "disabled"
                        );

                    }


                    const caption =
                        document.createElement(
                            "span"
                        );


                    caption.textContent =
                        item.caption || "";


                    row.appendChild(
                        caption
                    );


                    if(item.value)
                    {

                        const value =
                            document.createElement(
                                "span"
                            );


                        value.className =
                            "value";


                        value.textContent =
                            item.value.text;


                        row.appendChild(
                            value
                        );

                    }


                    listItem.appendChild(
                        row
                    );


                    if(
                        Array.isArray(
                            item.children
                        ) &&
                        item.children.length > 0
                    )
                    {

                        listItem.appendChild(
                            createList(
                                item.children
                            )
                        );

                    }


                    list.appendChild(
                        listItem
                    );

                }
            );


            return list;

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

                const commands =
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
                    commands[event.key];


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


        connect();

    </script>

</body>

</html>
)HTML";


#endif