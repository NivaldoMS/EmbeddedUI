#ifndef OLED_WEB_MENU_MONITOR_WEB_PAGE_H
#define OLED_WEB_MENU_MONITOR_WEB_PAGE_H


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

    <title>OLED Menu Monitor</title>

    <style>

        *
        {
            box-sizing: border-box;
        }

        body
        {
            margin: 0;
            min-height: 100vh;

            background:
                radial-gradient(
                    circle at top,
                    #18283a,
                    #090e14 65%
                );

            color: #edf6ff;

            font-family:
                Arial,
                Helvetica,
                sans-serif;
        }

        main
        {
            width: min(94%, 760px);

            margin: 0 auto;
            padding: 26px 0;
        }

        header
        {
            margin-bottom: 18px;
        }

        h1
        {
            margin: 0;

            font-size: 1.4rem;
        }

        .description
        {
            margin-top: 6px;

            color: #8ea5ba;
            font-size: 0.88rem;
        }

        #status
        {
            margin-top: 10px;

            color: #ff8585;
            font-size: 0.84rem;
        }

        #status.connected
        {
            color: #67e6a2;
        }

        .legend
        {
            display: flex;
            flex-wrap: wrap;

            gap: 9px;

            margin-bottom: 15px;
        }

        .legend-item
        {
            padding:
                5px
                9px;

            border: 1px solid #314a61;
            border-radius: 7px;

            background: #111c27;

            color: #a9bdcf;
            font-size: 0.78rem;
        }

        .legend-item.selected
        {
            color: #08131c;
            background: #77ddff;
        }

        .legend-item.editing
        {
            color: #ffe39a;
            border-color: #d5a62d;
        }

        .legend-item.executing
        {
            color: #84f0b7;
            border-color: #30aa69;
        }

        .monitor
        {
            min-height: 280px;

            padding: 18px;

            border: 1px solid #2d465d;
            border-radius: 14px;

            background:
                rgba(
                    14,
                    23,
                    32,
                    0.96
                );

            box-shadow:
                0 18px 50px
                rgba(
                    0,
                    0,
                    0,
                    0.3
                );
        }

        ul
        {
            margin: 0;
            padding: 0;

            list-style: none;
        }

        ul ul
        {
            margin-left: 16px;
            padding-left: 17px;

            border-left: 1px solid #34516a;
        }

        li
        {
            margin: 6px 0;
        }

        .root-item
        {
            margin-bottom: 10px;
        }

        .item
        {
            min-height: 40px;

            display: grid;

            grid-template-columns:
                26px
                minmax(0, 1fr)
                auto
                auto;

            align-items: center;

            gap: 9px;

            padding:
                7px
                10px;

            border: 1px solid transparent;
            border-radius: 8px;

            background: #172431;
        }

        .item.folder
        {
            background: #1b3042;
            font-weight: 700;
        }

        .root-header
        {
            cursor: pointer;
            user-select: none;

            transition:
                background 0.16s ease,
                border-color 0.16s ease;
        }

        .root-header:hover
        {
            background: #24435a;
            border-color: #41647f;
        }

        .root-header:focus-visible
        {
            outline: 2px solid #77ddff;
            outline-offset: 2px;
        }

        .item.action
        {
            color: #b3c6d6;
        }

        .item.disabled
        {
            opacity: 0.4;
        }

        .item.selected
        {
            color: #07141d;

            border-color: #77ddff;
            background: #77ddff;
        }

        .item.editing
        {
            border-color: #e1b541;

            box-shadow:
                inset 0 0 0 1px
                rgba(
                    225,
                    181,
                    65,
                    0.45
                );
        }

        .item.executing
        {
            border-color: #42d985;

            box-shadow:
                inset 0 0 0 1px
                rgba(
                    66,
                    217,
                    133,
                    0.5
                );
        }

        .marker
        {
            width: 22px;

            font-weight: bold;
            text-align: center;
        }

        .caption
        {
            min-width: 0;

            overflow: hidden;

            text-overflow: ellipsis;
            white-space: nowrap;
        }

        .root-caption
        {
            display: flex;
            align-items: center;
        }

        .collapse-marker
        {
            display: inline-block;

            width: 18px;
            margin-right: 5px;

            color: #91b8d1;

            font-size: 0.8rem;
            text-align: center;

            transition:
                transform 0.16s ease;
        }

        .root-header.collapsed
        .collapse-marker
        {
            transform: rotate(-90deg);
        }

        .root-header.selected
        .collapse-marker
        {
            color: #07141d;
        }

        .value
        {
            min-width: 74px;

            justify-self: end;

            padding:
                4px
                8px;

            border-radius: 6px;

            background: #07121b;
            color: #77dcff;

            font-family:
                "Courier New",
                monospace;

            text-align: right;
        }

        .selected .value
        {
            color: #07141d;

            background:
                rgba(
                    255,
                    255,
                    255,
                    0.38
                );
        }

        .state
        {
            min-width: 0;

            font-size: 0.72rem;
            font-weight: bold;

            text-align: right;
        }

        .state:empty
        {
            display: none;
        }

        .state.editing
        {
            color: #ffd86a;
        }

        .state.executing
        {
            color: #73eaaa;
        }

        .selected .state
        {
            color: #07141d;
        }

        .children-container
        {
            overflow: hidden;

            max-height: 2000px;
            opacity: 1;

            transition:
                max-height 0.22s ease,
                opacity 0.16s ease;
        }

        .children-container.collapsed
        {
            max-height: 0;
            opacity: 0;

            pointer-events: none;
        }

        .empty
        {
            color: #7890a5;
        }

    </style>

</head>

<body>

    <main>

        <header>

            <h1>
                OLED + Monitor Web
            </h1>

            <div class="description">
                Estado em tempo real do menu exibido no OLED.
            </div>

            <div id="status">
                WebSocket desconectado
            </div>

        </header>

        <section class="legend">

            <span class="legend-item selected">
                ▶ Selecionado
            </span>

            <span class="legend-item editing">
                ● Editando
            </span>

            <span class="legend-item executing">
                ◆ Executando
            </span>

        </section>

        <section class="monitor">

            <div id="menu">
                Aguardando dados...
            </div>

        </section>

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


        const collapsedItems =
            new Map();


        let socket =
            null;


        let reconnectTimer =
            null;


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
                            "menuHierarchyMonitor"
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
                            "Mensagem inválida:",
                            event.data,
                            error
                        );

                    }

                }
            );

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

                const empty =
                    document.createElement(
                        "div"
                    );


                empty.className =
                    "empty";


                empty.textContent =
                    "Menu vazio";


                menuElement.appendChild(
                    empty
                );


                return;

            }


            menuElement.appendChild(
                createList(
                    items,
                    0,
                    ""
                )
            );

        }


        function createList(
            items,
            level,
            parentPath
        )
        {

            const list =
                document.createElement(
                    "ul"
                );


            items.forEach(
                (
                    item,
                    index
                ) =>
                {

                    const itemPath =
                        parentPath +
                        "/" +
                        index +
                        ":" +
                        (
                            item.caption ||
                            ""
                        );


                    const listItem =
                        document.createElement(
                            "li"
                        );


                    if(level === 0)
                    {

                        listItem.classList.add(
                            "root-item"
                        );

                    }


                    const row =
                        createItemRow(
                            item,
                            level
                        );


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

                        const childrenContainer =
                            document.createElement(
                                "div"
                            );


                        childrenContainer.className =
                            "children-container";


                        childrenContainer.appendChild(
                            createList(
                                item.children,
                                level + 1,
                                itemPath
                            )
                        );


                        if(level === 0)
                        {

                            const collapsed =
                                collapsedItems.get(
                                    itemPath
                                ) === true;


                            applyCollapsedState(
                                row,
                                childrenContainer,
                                collapsed
                            );


                            row.addEventListener(
                                "click",
                                () =>
                                {

                                    const nextCollapsed =
                                        !childrenContainer
                                            .classList
                                            .contains(
                                                "collapsed"
                                            );


                                    collapsedItems.set(
                                        itemPath,
                                        nextCollapsed
                                    );


                                    applyCollapsedState(
                                        row,
                                        childrenContainer,
                                        nextCollapsed
                                    );

                                }
                            );


                            row.addEventListener(
                                "keydown",
                                event =>
                                {

                                    if(
                                        event.key !== "Enter" &&
                                        event.key !== " "
                                    )
                                    {
                                        return;
                                    }


                                    event.preventDefault();


                                    row.click();

                                }
                            );

                        }


                        listItem.appendChild(
                            childrenContainer
                        );

                    }


                    list.appendChild(
                        listItem
                    );

                }
            );


            return list;

        }


        function createItemRow(
            item,
            level
        )
        {

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


            if(level === 0)
            {

                row.classList.add(
                    "root-header"
                );


                row.setAttribute(
                    "role",
                    "button"
                );


                row.setAttribute(
                    "tabindex",
                    "0"
                );

            }


            if(
                item.enabled === false
            )
            {

                row.classList.add(
                    "disabled"
                );

            }


            if(item.selected)
            {

                row.classList.add(
                    "selected"
                );

            }


            if(item.editing)
            {

                row.classList.add(
                    "editing"
                );

            }


            if(item.executing)
            {

                row.classList.add(
                    "executing"
                );

            }


            const marker =
                document.createElement(
                    "span"
                );


            marker.className =
                "marker";


            if(item.executing)
            {

                marker.textContent =
                    "◆";

            }
            else if(item.editing)
            {

                marker.textContent =
                    "●";

            }
            else if(item.selected)
            {

                marker.textContent =
                    "▶";

            }
            else
            {

                marker.textContent =
                    "";

            }


            const caption =
                document.createElement(
                    "span"
                );


            caption.className =
                "caption";


            if(level === 0)
            {

                caption.classList.add(
                    "root-caption"
                );


                const collapseMarker =
                    document.createElement(
                        "span"
                    );


                collapseMarker.className =
                    "collapse-marker";


                collapseMarker.textContent =
                    "▼";


                caption.appendChild(
                    collapseMarker
                );


                const captionText =
                    document.createElement(
                        "span"
                    );


                captionText.textContent =
                    item.caption || "";


                caption.appendChild(
                    captionText
                );

            }
            else
            {

                caption.textContent =
                    item.caption || "";

            }


            const value =
                document.createElement(
                    "span"
                );


            value.className =
                "value";


            value.textContent =
                item.value
                ?
                item.value.text
                :
                "";


            const state =
                document.createElement(
                    "span"
                );


            state.className =
                "state";


            if(item.executing)
            {

                state.classList.add(
                    "executing"
                );


                state.textContent =
                    "EXECUTANDO";

            }
            else if(item.editing)
            {

                state.classList.add(
                    "editing"
                );


                state.textContent =
                    "EDITANDO";

            }
            else
            {

                state.textContent =
                    "";

            }


            row.appendChild(
                marker
            );


            row.appendChild(
                caption
            );


            row.appendChild(
                value
            );


            row.appendChild(
                state
            );


            return row;

        }


        function applyCollapsedState(
            row,
            childrenContainer,
            collapsed
        )
        {

            row.classList.toggle(
                "collapsed",
                collapsed
            );


            childrenContainer.classList.toggle(
                "collapsed",
                collapsed
            );


            row.setAttribute(
                "aria-expanded",
                collapsed
                ?
                "false"
                :
                "true"
            );

        }


        setConnected(
            false
        );


        connect();

    </script>

</body>

</html>
)HTML";


#endif