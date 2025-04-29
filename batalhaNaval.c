#include <stdio.h>

#define TAM 10
#define NAVIO 3
#define AGUA 0
#define HABILIDADE 5
#define TAM_HAB 5

void inicializarTabuleiro(int tabuleiro[TAM][TAM]) {
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            tabuleiro[i][j] = AGUA;
        }
    }
}

int verificarPosicao(int tabuleiro[TAM][TAM], int linha, int coluna, int tamanho, int direcao, int diagonal) {
    for (int i = 0; i < tamanho; i++) {
        int l = linha + (direcao == 1 ? i : (diagonal == 1 ? i : 0));
        int c = coluna + (direcao == 0 ? i : (diagonal == 2 ? -i : 0));

        if (l < 0 || l >= TAM || c < 0 || c >= TAM) return 0;
        if (tabuleiro[l][c] != AGUA) return 0;
    }
    return 1;
}

void posicionarNavio(int tabuleiro[TAM][TAM], int linha, int coluna, int tamanho, int direcao, int diagonal) {
    for (int i = 0; i < tamanho; i++) {
        int l = linha + (direcao == 1 ? i : (diagonal == 1 ? i : 0));
        int c = coluna + (direcao == 0 ? i : (diagonal == 2 ? -i : 0));

        tabuleiro[l][c] = NAVIO;
    }
}

void exibirTabuleiro(int tabuleiro[TAM][TAM]) {
    printf("\nTabuleiro:\n\n");
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            printf("%d ", tabuleiro[i][j]);
        }
        printf("\n");
    }
}

// Cria uma matriz 5x5 em forma de cone
void criarMatrizCone(int matriz[TAM_HAB][TAM_HAB]) {
    for (int i = 0; i < TAM_HAB; i++) {
        for (int j = 0; j < TAM_HAB; j++) {
            matriz[i][j] = 0;
        }
    }
    for (int i = 0; i < TAM_HAB; i++) {
        for (int j = TAM_HAB / 2 - i; j <= TAM_HAB / 2 + i; j++) {
            if (j >= 0 && j < TAM_HAB) {
                matriz[i][j] = 1;
            }
        }
    }
}

// Cria uma matriz 5x5 em forma de cruz
void criarMatrizCruz(int matriz[TAM_HAB][TAM_HAB]) {
    for (int i = 0; i < TAM_HAB; i++) {
        for (int j = 0; j < TAM_HAB; j++) {
            matriz[i][j] = (i == TAM_HAB / 2 || j == TAM_HAB / 2) ? 1 : 0;
        }
    }
}

// Cria uma matriz 5x5 em forma de octaedro (losango)
void criarMatrizOctaedro(int matriz[TAM_HAB][TAM_HAB]) {
    for (int i = 0; i < TAM_HAB; i++) {
        for (int j = 0; j < TAM_HAB; j++) {
            matriz[i][j] = 0;
        }
    }
    for (int i = 0; i < TAM_HAB; i++) {
        for (int j = abs(TAM_HAB / 2 - i); j < TAM_HAB - abs(TAM_HAB / 2 - i); j++) {
            matriz[i][j] = 1;
        }
    }
}

// Aplica a matriz de habilidade no tabuleiro, marcando com o valor 5
void aplicarHabilidade(int tabuleiro[TAM][TAM], int origemLinha, int origemColuna, int matrizHabilidade[TAM_HAB][TAM_HAB]) {
    int centro = TAM_HAB / 2;

    for (int i = 0; i < TAM_HAB; i++) {
        for (int j = 0; j < TAM_HAB; j++) {
            int linhaTab = origemLinha + i - centro;
            int colunaTab = origemColuna + j - centro;

            if (linhaTab >= 0 && linhaTab < TAM && colunaTab >= 0 && colunaTab < TAM) {
                if (matrizHabilidade[i][j] == 1 && tabuleiro[linhaTab][colunaTab] == AGUA) {
                    tabuleiro[linhaTab][colunaTab] = HABILIDADE;
                }
            }
        }
    }
}

int main() {
    int tabuleiro[TAM][TAM];
    inicializarTabuleiro(tabuleiro);

    // Posicionar dois navios ortogonais
    if (verificarPosicao(tabuleiro, 1, 1, 3, 0, 0)) posicionarNavio(tabuleiro, 1, 1, 3, 0, 0); // Horizontal
    if (verificarPosicao(tabuleiro, 4, 2, 3, 1, 0)) posicionarNavio(tabuleiro, 4, 2, 3, 1, 0); // Vertical

    // Posicionar dois navios diagonais
    if (verificarPosicao(tabuleiro, 6, 0, 3, 0, 1)) posicionarNavio(tabuleiro, 6, 0, 3, 0, 1); // Diagonal ↘
    if (verificarPosicao(tabuleiro, 2, 7, 3, 0, 2)) posicionarNavio(tabuleiro, 2, 7, 3, 0, 2); // Diagonal ↙

    // Criar matrizes de habilidades
    int cone[TAM_HAB][TAM_HAB];
    int cruz[TAM_HAB][TAM_HAB];
    int octaedro[TAM_HAB][TAM_HAB];

    criarMatrizCone(cone);
    criarMatrizCruz(cruz);
    criarMatrizOctaedro(octaedro);

    // Aplicar habilidades no tabuleiro
    aplicarHabilidade(tabuleiro, 2, 2, cone);
    aplicarHabilidade(tabuleiro, 5, 5, cruz);
    aplicarHabilidade(tabuleiro, 7, 7, octaedro);

    // Exibir resultado
    exibirTabuleiro(tabuleiro);

    return 0;
}
