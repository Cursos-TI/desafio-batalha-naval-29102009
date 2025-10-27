#include <stdio.h>

#define TAM 10        // Tamanho fixo do tabuleiro 10x10
#define TAM_NAVIO 3   // Cada navio ocupa 3 posições
#define AGUA 0
#define NAVIO 3


// Função: inicializa o tabuleiro com água (0)

void inicializarTabuleiro(int tabuleiro[TAM][TAM]) {
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            tabuleiro[i][j] = AGUA;
        }
    }
}


// Verifica se um navio cabe no tabuleiro (sem sair)

int navioCabe(int linha, int coluna, int orientacao) {
    switch (orientacao) {
        case 0: // horizontal
            return (coluna + TAM_NAVIO <= TAM);
        case 1: // vertical
            return (linha + TAM_NAVIO <= TAM);
        case 2: // diagonal principal (↘)
            return (linha + TAM_NAVIO <= TAM && coluna + TAM_NAVIO <= TAM);
        case 3: // diagonal secundária (↙)
            return (linha + TAM_NAVIO <= TAM && coluna - TAM_NAVIO + 1 >= 0);
        default:
            return 0;
    }
}


// Verifica se o navio sobrepõe outro

int sobrepoe(int tabuleiro[TAM][TAM], int linha, int coluna, int orientacao) {
    for (int k = 0; k < TAM_NAVIO; k++) {
        int l = linha;
        int c = coluna;
        switch (orientacao) {
            case 0: c += k; break;       // horizontal
            case 1: l += k; break;       // vertical
            case 2: l += k; c += k; break; // diagonal principal
            case 3: l += k; c -= k; break; // diagonal secundária
        }
        if (tabuleiro[l][c] == NAVIO)
            return 1; // há sobreposição
    }
    return 0;
}


//  Posiciona um navio no tabuleiro (seguro)

void posicionarNavio(int tabuleiro[TAM][TAM], int linha, int coluna, int orientacao) {
    if (!navioCabe(linha, coluna, orientacao)) {
        printf("Erro: navio fora dos limites do tabuleiro!\n");
        return;
    }
    if (sobrepoe(tabuleiro, linha, coluna, orientacao)) {
        printf("Erro: sobreposição de navios detectada!\n");
        return;
    }

    for (int k = 0; k < TAM_NAVIO; k++) {
        switch (orientacao) {
            case 0: tabuleiro[linha][coluna + k] = NAVIO; break;        // horizontal
            case 1: tabuleiro[linha + k][coluna] = NAVIO; break;        // vertical
            case 2: tabuleiro[linha + k][coluna + k] = NAVIO; break;    // diagonal principal ↘
            case 3: tabuleiro[linha + k][coluna - k] = NAVIO; break;    // diagonal secundária ↙
        }
    }
}


// Exibe o tabuleiro de forma organizada

void exibirTabuleiro(int tabuleiro[TAM][TAM]) {
    printf("\n   ");
    for (int j = 0; j < TAM; j++)
        printf("%2d ", j);
    printf("\n---------------------------------------------\n");

    for (int i = 0; i < TAM; i++) {
        printf("%2d| ", i);
        for (int j = 0; j < TAM; j++) {
            if (tabuleiro[i][j] == AGUA)
                printf("~ ");
            else if (tabuleiro[i][j] == NAVIO)
                printf("N ");
            else
                printf("? ");
        }
        printf("\n");
    }
    printf("\n");
}


// Função principal

int main() {
    int tabuleiro[TAM][TAM];
    inicializarTabuleiro(tabuleiro);

    // -----------------------------
    // Coordenadas e orientações:
    // 0 = horizontal, 1 = vertical
    // 2 = diagonal principal ↘, 3 = diagonal secundária ↙
    // -----------------------------

    // Navios retos
    posicionarNavio(tabuleiro, 2, 2, 0); // horizontal
    posicionarNavio(tabuleiro, 5, 7, 1); // vertical

    // Navios diagonais
    posicionarNavio(tabuleiro, 0, 0, 2); // diagonal principal ↘
    posicionarNavio(tabuleiro, 0, 9, 3); // diagonal secundária ↙

    printf("=== TABULEIRO COMPLETO COM NAVIOS DIAGONAIS ===\n");
    exibirTabuleiro(tabuleiro);

    return 0;
}
