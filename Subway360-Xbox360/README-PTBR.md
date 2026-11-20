# Subway360 — pacote de preparação para Xbox 360

Este pacote contém duas partes:

1. `UnityOriginal/SubwaySurfers-main/`: cópia do ZIP enviado, mantida como projeto-fonte original.
2. `Subway360-Xbox360/`: início de um projeto nativo para Xbox 360 usando o xsdk público.

## Estado real desta etapa

O código em `src/main.c` é um **bootstrap de teste**: inicializa o xsdk, abre a saída 720p, limpa a tela e permite sair pelo botão Back. Ele serve para validar a cadeia de compilação e a inicialização de um XEX.

**Ainda NÃO é o Subway Surfers jogável.** O projeto enviado é Unity 6 / C#. O xsdk compila títulos nativos C/C++; ele não converte automaticamente cenas Unity, scripts C#, FBX, animações, materiais ou Shader Graph para Xbox 360. A jogabilidade, renderização 3D, colisões, personagens, trens, moedas, áudio e interface ainda precisam ser portados e testados separadamente.

## Como usar pelo GitHub no celular

1. Crie um repositório no GitHub, por exemplo `Subway360`.
2. Envie o conteúdo desta pasta ZIP para a raiz do repositório (extraia o ZIP antes de enviar).
3. Abra a aba **Actions**.
4. Se necessário, habilite Actions para o repositório.
5. Execute **Build Subway360 XEX** em **Run workflow**.
6. Aguarde o workflow terminar. O primeiro build do compilador pode demorar e consumir bastante espaço.
7. Abra a execução concluída, baixe o artefato **Subway360-XEX** e confira se contém `Subway360.xex`.

Se o workflow falhar por limite de espaço/tempo do runner ou por alteração no xsdk, abra os logs e corrija a primeira falha real. Não considere um build concluído se não houver artefato.

## Como testar

O XEX gerado é destinado a Xbox 360 RGH/JTAG compatível com homebrew, não a um Xbox 360 retail bloqueado. O teste final deve ser feito no console: transfira o XEX usando o método de arquivos da sua dashboard e execute-o. Nesta etapa, o resultado esperado é apenas uma tela escura/azulada e saída pelo botão Back. Consulte o log `Subway360.log` se ele for criado pelo xsdk.

## Próximas etapas de portabilidade

- Inventariar as cenas e scripts C# do projeto Unity.
- Escolher uma cena mínima e reconstruir a lógica em C/C++.
- Converter/importar modelos e texturas para formatos suportados pelo renderer nativo.
- Implementar shaders compatíveis com a GPU Xenos.
- Implementar input do controle, física, colisões, áudio e interface.
- Testar cada sistema no Xenia como verificação preliminar e no console RGH/JTAG como teste final.

## Dependências

O workflow baixa o xsdk de https://github.com/xenosworks/xsdk durante a execução. A documentação oficial do xsdk explica dependências, toolchain, CMake e o formato XEX:
https://github.com/xenosworks/xsdk/blob/main/docs/GETTING_STARTED.md

Use apenas código e assets que você tenha direito de modificar e distribuir. O nome e os assets oficiais de Subway Surfers podem ter direitos de terceiros.
