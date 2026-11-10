#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdbool.h>

const int LARGURA_TELA = 140;
const int ALTURA_TELA = 480;

int main(int argc, char* argv[]) {
    // 1. Inicializa o subsistema de vídeo da SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("Erro ao inicializar SDL: %s\n", SDL_GetError());
        return -1;
    }

    // 2. Cria a janela do aplicativo
    SDL_Window* janela = SDL_CreateWindow(
        "Minha Tela SDL",          // Título da janela
        SDL_WINDOWPOS_CENTERED,    // Posição X inicial (centralizada)
        SDL_WINDOWPOS_CENTERED,    // Posição Y inicial (centralizada)
        LARGURA_TELA,              // Largura em pixels
        ALTURA_TELA,               // Altura em pixels
        SDL_WINDOW_SHOWN           // Opções (exibir a janela imediatamente)
    );

    if (janela == NULL) {
        printf("Erro ao criar janela: %s\n", SDL_GetError());
        SDL_Quit();
        return -1;
    }

    // 3. Cria o renderizador para desenhar na janela
    SDL_Renderer* renderizador = SDL_CreateRenderer(
        janela,
        -1,
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
    );

    if (renderizador == NULL) {
        printf("Erro ao criar renderizador: %s\n", SDL_GetError());
        SDL_DestroyWindow(janela);
        SDL_Quit();
        return -1;
    }

    // 4. Laço principal (Game Loop) e gerenciamento de eventos
    bool rodando = true;
    SDL_Event evento;

    while (rodando) {
        // Verifica se o usuário interagiu com a janela (fechar, teclado, etc.)
        while (SDL_PollEvent(&evento) != 0) {
            if (evento.type == SDL_QUIT) {
                rodando = false; // Sai do laço se clicar no 'X' para fechar
            }
        }

        // Define a cor de fundo (RGBA: 0, 100, 200, 255 -> Azul)
        SDL_SetRenderDrawColor(renderizador, 0, 100, 200, 255);

        // Limpa a tela com a cor selecionada
        SDL_RenderClear(renderizador);

        // Aqui você pode adicionar funções para desenhar imagens, textos ou formas geométricas

        // Atualiza a tela com o que foi renderizado
        SDL_RenderPresent(renderizador);
    }

    // 5. Limpeza de memória antes de fechar o programa
    SDL_DestroyRenderer(renderizador);
    SDL_DestroyWindow(janela);
    SDL_Quit();

    return 0;
}
