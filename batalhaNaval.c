#include <stdio.h>

#define TAMANHO_TABULEIRO 10
#define TAMANHO_NAVIO 3
#define AGUA 0
#define NAVIO 3

// Função para inicializar o tabuleiro com 0 (água)
void inicializarTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            tabuleiro[i][j] = AGUA;
        }
    }
}

// Verifica se o navio pode ser posicionado no local especificado
int podePosicionarNavio(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int linha, int coluna, char orientacao) {
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        int x = linha + (orientacao == 'V' ? i : 0);
        int y = coluna + (orientacao == 'H' ? i : 0);

        if (x >= TAMANHO_TABULEIRO || y >= TAMANHO_TABULEIRO)
            return 0;

        if (tabuleiro[x][y] == NAVIO)
            return 0;
    }
    return 1;
}

// Posiciona o navio no tabuleiro
void posicionarNavio(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int linha, int coluna, char orientacao) {
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        int x = linha + (orientacao == 'V' ? i : 0);
        int y = coluna + (orientacao == 'H' ? i : 0);
        tabuleiro[x][y] = NAVIO;
    }
}

// Exibe o tabuleiro
void exibirTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    printf("\n=== Tabuleiro ===\n");
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            printf("%d ", tabuleiro[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO];
    inicializarTabuleiro(tabuleiro);

    // Coordenadas iniciais dos navios
    int linha1 = 2, coluna1 = 4; // Navio horizontal
    int linha2 = 5, coluna2 = 7; // Navio vertical

    // Posicionamento e exibição das coordenadas do navio horizontal
    if (podePosicionarNavio(tabuleiro, linha1, coluna1, 'H')) {
        posicionarNavio(tabuleiro, linha1, coluna1, 'H');
        printf("Coordenadas do navio horizontal:\n");
        for (int i = 0; i < TAMANHO_NAVIO; i++) {
            printf("(%d, %d)\n", linha1, coluna1 + i);
        }
    } else {
        printf("Erro: Não foi possível posicionar o navio horizontal.\n");
    }

    // Posicionamento e exibição das coordenadas do navio vertical
    if (podePosicionarNavio(tabuleiro, linha2, coluna2, 'V')) {
        posicionarNavio(tabuleiro, linha2, coluna2, 'V');
        printf("Coordenadas do navio vertical:\n");
        for (int i = 0; i < TAMANHO_NAVIO; i++) {
            printf("(%d, %d)\n", linha2 + i, coluna2);
        }
    } else {
        printf("Erro: Não foi possível posicionar o navio vertical.\n");
    }

    // Exibe o tabuleiro final
    exibirTabuleiro(tabuleiro);

    return 0;
}
