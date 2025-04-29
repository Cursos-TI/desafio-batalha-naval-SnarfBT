#include <stdio.h>

#define TAMANHO 10
#define TAMANHO_NAVIO 3
#define NAVIO 3
#define AGUA 0

void inicializarTabuleiro(int tabuleiro[TAMANHO][TAMANHO]) {
    for (int i = 0; i < TAMANHO; i++) {
        for (int j = 0; j < TAMANHO; j++) {
            tabuleiro[i][j] = AGUA;
        }
    }
}

void posicionarNavioHorizontal(int tabuleiro[TAMANHO][TAMANHO], int linha, int coluna) {
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        tabuleiro[linha][coluna + i] = NAVIO;
        printf("Navio horizontal posicionado em: [%d][%d]\n", linha, coluna + i);
    }
}

void posicionarNavioVertical(int tabuleiro[TAMANHO][TAMANHO], int linha, int coluna) {
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        tabuleiro[linha + i][coluna] = NAVIO;
        printf("Navio vertical posicionado em: [%d][%d]\n", linha + i, coluna);
    }
}

void exibirTabuleiro(int tabuleiro[TAMANHO][TAMANHO]) {
    for (int i = 0; i < TAMANHO; i++) {
        for (int j = 0; j < TAMANHO; j++) {
            printf("%d ", tabuleiro[i][j]);
        }
        printf("\n");
    }
}

int podePosicionarNavio(int tabuleiro[TAMANHO][TAMANHO], int linha, int coluna, char orientacao) {
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        int x = linha;
        int y = coluna;

        if (orientacao == 'H') y += i;
        else if (orientacao == 'V') x += i;
        else if (orientacao == 'D') { x += i; y += i; }
        else if (orientacao == 'A') { x += i; y -= i; }

        if (x < 0 || x >= TAMANHO || y < 0 || y >= TAMANHO)
            return 0;
        if (tabuleiro[x][y] == NAVIO)
            return 0;
    }
    return 1;
}

void posicionarNavio(int tabuleiro[TAMANHO][TAMANHO], int linha, int coluna, char orientacao) {
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        int x = linha;
        int y = coluna;

        if (orientacao == 'H') y += i;
        else if (orientacao == 'V') x += i;
        else if (orientacao == 'D') { x += i; y += i; }
        else if (orientacao == 'A') { x += i; y -= i; }

        tabuleiro[x][y] = NAVIO;
    }
}

int main() {
    int tabuleiro1[TAMANHO][TAMANHO];
    inicializarTabuleiro(tabuleiro1);
    int linhaH = 2, colunaH = 3;
    int linhaV = 5, colunaV = 7;

    if (colunaH + TAMANHO_NAVIO <= TAMANHO)
        posicionarNavioHorizontal(tabuleiro1, linhaH, colunaH);
    if (linhaV + TAMANHO_NAVIO <= TAMANHO)
        posicionarNavioVertical(tabuleiro1, linhaV, colunaV);

    printf("\nTabuleiro com 2 navios ortogonais:\n");
    exibirTabuleiro(tabuleiro1);

    int tabuleiro2[TAMANHO][TAMANHO];
    inicializarTabuleiro(tabuleiro2);

    if (podePosicionarNavio(tabuleiro2, 2, 2, 'H'))
        posicionarNavio(tabuleiro2, 2, 2, 'H');
    if (podePosicionarNavio(tabuleiro2, 0, 0, 'V'))
        posicionarNavio(tabuleiro2, 0, 0, 'V');
    if (podePosicionarNavio(tabuleiro2, 5, 1, 'D'))
        posicionarNavio(tabuleiro2, 5, 1, 'D');
    if (podePosicionarNavio(tabuleiro2, 3, 7, 'A'))
        posicionarNavio(tabuleiro2, 3, 7, 'A');

    printf("\nTabuleiro com 4 navios (incluindo diagonais):\n");
    exibirTabuleiro(tabuleiro2);

    return 0;
}
