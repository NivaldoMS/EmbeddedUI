# OledWebMenuMonitor
#### display OLED e monitoramento web.

### Duas saídas simultâneas

```text
Botões físicos
      │
      ▼
 EmbeddedUI
      │
      ├── OLED SSD1306 128×64
      └── MenuHierarchyMonitor → WebSocket → navegador
```

## Estrutura

```text
examples/
└── OledWebMenuMonitor/
    ├── OledWebMenuMonitor.ino
    ├── AppConfig.h
    ├── MenuApplication.h
    ├── MenuApplication.cpp
    └── WebPage.h
```

Ele reutiliza estes componentes já existentes na biblioteca:

```text
src/drivers/display/U8g2Display.h

src/extensions/websocket/
├── MenuHierarchyMonitor.h
└── MenuHierarchyMonitor.cpp

src/utilities/
├── CommandLed.h
└── CommandLed.cpp
```

## Ligações

### OLED SSD1306 I²C

```text
OLED        NodeMCU ESP8266

VCC    →    3V3
GND    →    GND
SCL    →    D1 / GPIO5
SDA    →    D2 / GPIO4
```

### Botões

Cada botão deve ser ligado entre o pino e `GND`.

```text
CW       → D5 / GPIO14
CCW      → D6 / GPIO12
ENTER    → D7 / GPIO13
BACK     → D3 / GPIO0
```
O botão em `D3` não deve permanecer pressionado durante a inicialização do ESP8266.

## Pré-requisito em MenuScreen

O exemplo utiliza:
```C++
_menuScreen.cursor();
_menuScreen.interactionState();
```
`MenuScreen` deve expor esses objetos.