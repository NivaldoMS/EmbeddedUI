# NodeMCU ESP8266 ESP-12E com OLED 0,96″

Exemplo completo para NodeMCU ESP8266 ESP-12E com OLED 0,96″ 128×64 SSD1306 I²C, usando buffer paginado para economizar RAM.

## Ligações do display

```text
OLED      NodeMCU
VCC   →   3V3
GND   →   GND
SCL   →   D1 / GPIO5
SDA   →   D2 / GPIO4
```
## Botões

```text
CW      → D5 / GPIO14
CCW     → D6 / GPIO12
ENTER   → D7 / GPIO13
BACK    → D3 / GPIO0
```

Cada botão deve ser ligado entre o pino e o GND.
Não mantenha o botão conectado ao D3 pressionado durante a inicialização, pois o GPIO0 participa do modo de boot do ESP8266.