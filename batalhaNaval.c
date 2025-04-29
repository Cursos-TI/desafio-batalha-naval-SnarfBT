#include <stdio.h>

#define TAMANHO 10
#define TAMANHO_NAVIO 3
#define NAVIO 3
#define AGUA 0
#define HABILIDADE 5
#define TAM_HAB 5  // Tamanho fixo da matriz de habilidade (5x5)

// Inicializa o tabuleiro com água
void inicializarTabuleiro(int tabuleiro[TAMANHO][TAMANHO]) {
    for (int i = 0; i < TAMANHO; i++)
        for (int j = 0; j < TAMANHO; j++)
            tabuleiro[i][j] = AGUA;
}

// Posiciona navios
void posicionarNavio(int tabuleiro[TAMANHO][TAMANHO], int linha, int coluna, char orientacao) {
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        int x = linha, y = coluna;
        if (orientacao == 'H') y += i;
        else if (orientacao == 'V') x += i;
        else if (orientacao == 'D') { x += i; y += i; }
        else if (orientacao == 'A') { x += i; y -= i; }
        tabuleiro[x][y] = NAVIO;
    }
}

// Valida se pode posicionar navio em certa orientação
int podePosicionarNavio(int tabuleiro[TAMANHO][TAMANHO], int linha, int coluna, char orientacao) {
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        int x = linha, y = coluna;
        if (orientacao == 'H') y += i;
        else if (orientacao == 'V') x += i;
        else if (orientacao == 'D') { x += i; y += i; }
        else if (orientacao == 'A') { x += i; y -= i; }

        if (x < 0 || x >= TAMANHO || y < 0 || y >= TAMANHO || tabuleiro[x][y] == NAVIO)
            return 0;
    }
    return 1;
}

// Cria matriz em forma de cone
void criarMatrizCone(int matriz[TAM_HAB][TAM_HAB]) {
    for (int i = 0; i < TAM_HAB; i++) {
        for (int j = 0; j < TAM_HAB; j++) {
            if (j >= TAM_HAB / 2 - i && j <= TAM_HAB / 2 + i)
                matriz[i][j] = 1;
            else
                matriz[i][j] = 0;
        }
    }
}

// Cria matriz em forma de cruz
void criarMatrizCruz(int matriz[TAM_HAB][TAM_HAB]) {
    for (int i = 0; i < TAM_HAB; i++) {
        for (int j = 0; j < TAM_HAB; j++) {
            if (i == TAM_HAB / 2 || j == TAM_HAB / 2)
                matriz[i][j] = 1;
            else
                matriz[i][j] = 0;
        }
    }
}

// Cria matriz em forma de octaedro (losango)
void criarMatrizOctaedro(int matriz[TAM_HAB][TAM_HAB]) {
    for (int i = 0; i < TAM_HAB; i++) {
        for (int j = 0; j < TAM_HAB; j++) {
            if (abs(i - TAM_HAB / 2) + abs(j - TAM_HAB / 2) <= TAM_HAB / 2)
                matriz[i][j] = 1;
            else
                matriz[i][j] = 0;
        }
    }
}

// Sobrepõe matriz de habilidade no tabuleiro na posição (linha, coluna)
void aplicarHabilidade(int tabuleiro[TAMANHO][TAMANHO], int matriz[TAM_HAB][TAM_HAB], int linha, int coluna) {
    for (int i = 0; i < TAM_HAB; i++) {
        for (int j = 0; j < TAM_HAB; j++) {
            int x = linha - TAM_HAB / 2 + i;
            int y = coluna - TAM_HAB / 2 + j;

            if (x >= 0 && x < TAMANHO && y >= 0 && y < TAMANHO) {
                if (matriz[i][j] == 1 && tabuleiro[x][y] == AGUA)
                    tabuleiro[x][y] = HABILIDADE;
            }
        }
    }
}

// Exibe o tabuleiro
void exibirTabuleiro(int tabuleiro[TAMANHO][TAMANHO]) {
    for (int i = 0; i < TAMANHO; i++) {
        for (int j = 0; j < TAMANHO; j++) {
            printf("%d ", tabuleiro[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int tabuleiro[TAMANHO][TAMANHO];
    inicializarTabuleiro(tabuleiro);

    // Posicionar 4 navios
    if (podePosicionarNavio(tabuleiro, 2, 2, 'H')) posicionarNavio(tabuleiro, 2, 2, 'H');
    if (podePosicionarNavio(tabuleiro, 0, 0, 'V')) posicionarNavio(tabuleiro, 0, 0, 'V');
    if (podePosicionarNavio(tabuleiro, 5, 1, 'D')) posicionarNavio(tabuleiro, 5, 1, 'D');
    if (podePosicionarNavio(tabuleiro, 3, 7, 'A')) posicionarNavio(tabuleiro, 3, 7, 'A');

    // Matrizes de habilidade
    int cone[TAM_HAB][TAM_HAB], cruz[TAM_HAB][TAM_HAB], octaedro[TAM_HAB][TAM_HAB];
    criarMatrizCone(cone);
    criarMatrizCruz(cruz);
    criarMatrizOctaedro(octaedro);

    // Aplicar habilidades no tabuleiro
    aplicarHabilidade(tabuleiro, cone, 1, 5);       // Cone no topo centro
    aplicarHabilidade(tabuleiro, cruz, 5, 5);       // Cruz no centro
    aplicarHabilidade(tabuleiro, octaedro, 8, 8);   // Octaedro no canto inferior direito

    // Exibir o tabuleiro com navios e áreas afetadas
    printf("\nTabuleiro com navios e habilidades aplicadas:\n");
    exibirTabuleiro(tabuleiro);

    return 0;
}
