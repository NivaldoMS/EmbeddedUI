INTEGRAÇÃO DE TELAS INDEPENDENTES

1. Substitua os arquivos de core pelos arquivos desta pasta.
2. Substitua widgets/menu/MenuScreen.h e MenuScreen.cpp.
3. Adicione a pasta screens ao src da biblioteca.
4. Mantenha Render.h/.cpp em src/render: ele passa a ser exclusivo do menu.
5. Atualize EmbeddedUI.h.
6. Use MenuApplication.h/.cpp da pasta app no exemplo.

Fluxo final:
Engine -> ScreenManager -> Screen ativa -> DisplayDriver
MenuScreen -> Render (somente menu)
InformationScreen/ResetScreen -> DisplayDriver diretamente

ResetScreen mostra o primeiro quadro antes de executar a tarefa configurada.
