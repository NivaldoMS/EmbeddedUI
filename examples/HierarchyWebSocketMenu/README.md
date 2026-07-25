# Painel de árvore

A página exibirá todos os itens e valores, respeitando a hierarquia, enquanto os quatro botões continuam controlando o menu.

### Estrutura do código

Este exemplo não simula o display gráfico. A página apresenta o menu inteiro em forma de árvore:


```text
Audio
├── Volume: 50
├── Bass: 0
└── Enabled: Ligado

Display
└── Brightness: 128

System
├── Information
└── Reset

```

### Os quatro botões continuam enviando:
```text
CW
CCW
ENTER
BACK
```
A árvore é reenviada apenas quando algum valor muda.

## Estrutura

```text
HierarchyWebSocketMenu/
├── HierarchyWebSocketMenu.ino
├── AppConfig.h
├── WebPage.h
├── WebSocketInput.h
├── WebSocketInput.cpp
├── NullDisplay.h
├── MenuApplication.h
├── MenuApplication.cpp
├── MenuHierarchyPublisher.h
├── MenuHierarchyPublisher.cpp
├── CommandLed.h
└── CommandLed.cpp
```
`WebSocketInput` e `CommandLed` podem ser reutilizados do exemplo anterior sem alterações.

## Resultado na página

A página não recebe coordenadas ou instruções gráficas. O WebSocket transmite somente uma estrutura semelhante a:

```json
{
  "type": "menuHierarchy",
  "items": [
    {
      "caption": "Audio",
      "nodeType": "folder",
      "enabled": true,
      "children": [
        {
          "caption": "Volume",
          "nodeType": "value",
          "enabled": true,
          "value": {
            "type": "integer",
            "raw": 50,
            "text": "50"
          }
        }
      ]
    }
  ]
}
```

`ENTER` confirma a edição. `BACK` cancela e o `MenuHierarchyPublisher` reenviará o valor original restaurado.