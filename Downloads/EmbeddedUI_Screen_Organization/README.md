# Organização de telas

## Biblioteca

`library/screens` contém somente telas genéricas e reutilizáveis.

Incluído nesta etapa:

- `SplashScreen`: tela genérica de inicialização com título, mensagem, borda opcional, duração e transição automática para outra tela.

`EmbeddedUI.h` exporta apenas `SplashScreen`. As telas específicas do exemplo não fazem mais parte da API pública.

## Exemplo Application

`example/Application/screens` contém telas dependentes do exemplo:

- `InformationScreen`
- `ResetScreen`

`MenuApplication.h` inclui essas telas diretamente:

```cpp
#include "screens/InformationScreen.h"
#include "screens/ResetScreen.h"
```

As classes foram colocadas no namespace `ApplicationScreens` para não poluir o namespace da biblioteca.

## Correção da ResetScreen

A tela agora:

1. renderiza `Reinicializando...`;
2. marca `_renderedOnce = true`;
3. executa a tarefa no próximo `update()`;
4. inicia a contagem após a tarefa;
5. mostra `Finalizado` ao terminar;
6. aceita `BACK` para retornar ao menu.

## Estrutura

```text
library/
├── EmbeddedUI.h
├── core/
├── render/
├── widgets/menu/
└── screens/
    ├── SplashScreen.h
    └── SplashScreen.cpp

example/Application/
├── MenuApplication.h
├── MenuApplication.cpp
└── screens/
    ├── InformationScreen.h
    ├── InformationScreen.cpp
    ├── ResetScreen.h
    └── ResetScreen.cpp
```

## Uso opcional da SplashScreen

```cpp
SplashScreen splash(
    engine.screens(),
    menuScreen,
    2000
);

splash.setTitle("EmbeddedUI");
splash.setMessage("Inicializando...");

engine.screens().show(
    splash
);
```
