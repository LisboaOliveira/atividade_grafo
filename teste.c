#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define tamanho 2355

// Função para encontrar cliques maximais
void bron_kerbosch(int *R, int *P, int *X, int **matriz, int vertice) {
    if (P[0] == -1 && X[0] == -1) {
        // R contém um clique maximal, faça o que for necessário com ele
        // Exemplo: imprimir os vértices do clique
        printf("Clique maximal encontrado: ");
        for (int i = 0; R[i] != -1; i++) {
            printf("%d ", R[i]);
        }
        printf("\n");
        exit(0); // Encerra o programa
    }
    int u, k;
    for (int i = 0; P[i] != -1; i++) {
        u = P[i];
        int *new_R = (int *)malloc(vertice * sizeof(int));
        int *new_P = (int *)malloc(vertice * sizeof(int));
        int *new_X = (int *)malloc(vertice * sizeof(int));
        // Adiciona u a R
        int j;
        for (j = 0; R[j] != -1; j++) {
            new_R[j] = R[j];
        }
        new_R[j] = u;
        new_R[j + 1] = -1;
        // Interseção de P e vizinhos de u
        int *intersect_P = (int *)malloc(vertice * sizeof(int));
        int *intersect_X = (int *)malloc(vertice * sizeof(int));
        j = 0;
        for (k = 0; P[k] != -1; k++) {
            if (matriz[u][P[k]] == 1)
                intersect_P[j++] = P[k];
        }
        intersect_P[j] = -1;
        j = 0;
        for (int k = 0; X[k] != -1; k++) {
            if (matriz[u][X[k]] == 1)
                intersect_X[j++] = X[k];
        }
        intersect_X[j] = -1;
        // Chama recursivamente com os novos conjuntos R, P e X
        bron_kerbosch(new_R, intersect_P, intersect_X, matriz, vertice);
        // Remove u de P e o coloca em X
        int *temp_P = (int *)malloc(vertice * sizeof(int));
        int *temp_X = (int *)malloc(vertice * sizeof(int));
        memcpy(temp_P, P, vertice * sizeof(int));
        memcpy(temp_X, X, vertice * sizeof(int));
        for (j = 0; temp_P[j] != -1; j++) {
            if (temp_P[j] == u) {
                for (int l = j; temp_P[l] != -1; l++)
                    temp_P[l] = temp_P[l + 1];
                break;
            }
        }
        for (j = 0; temp_X[j] != -1; j++) {
            if (temp_X[j] == -1) {
                temp_X[j] = u;
                temp_X[j + 1] = -1;
                break;
            }
        }
        bron_kerbosch(new_R, temp_P, temp_X, matriz, vertice);
        free(new_R);
        free(new_P);
        free(new_X);
        free(intersect_P);
        free(intersect_X);
        free(temp_P);
        free(temp_X);
    }
}

int main() {
    int linha = 0, coluna = 0, vertice = 2355;
    char zoru;
    FILE *arquivo;

    int **matriz = (int **)malloc(tamanho * sizeof(int *));
    for (int i = 0; i < tamanho; i++)
        matriz[i] = (int *)malloc(tamanho * sizeof(int));

    arquivo = fopen("dados.txt", "r");

    if (arquivo == NULL) {
        printf("Não foi possível abrir o arquivo!\n");
        exit(1);
    }

    while ((zoru = fgetc(arquivo)) != EOF) {
        if (zoru == '0' || zoru == '1') {
            matriz[linha][coluna] = zoru - '0';
            coluna++;
        }
        if (coluna == tamanho) {
            coluna = 0;
            linha++;
        }
    }

    fclose(arquivo);

    // Chamar a função para encontrar cliques maximais
    int *R = (int *)malloc(tamanho * sizeof(int)); // conjunto R inicialmente vazio
    R[0] = -1;
    int *P = (int *)malloc(tamanho * sizeof(int)); // conjunto P contendo todos os vértices
    int *X = (int *)malloc(tamanho * sizeof(int)); // conjunto X inicialmente vazio
    X[0] = -1;
    for (int i = 0; i < tamanho; i++) {
        P[i] = i;
        X[i] = -1;
        R[i] = -1;
    }
    P[tamanho - 1] = -1;
    bron_kerbosch(R, P, X, matriz, vertice);
    free(R);
    free(P);
    free(X);

    // Liberar memória alocada para a matriz
    for (int i = 0; i < tamanho; i++)
        free(matriz[i]);
    free(matriz);

    return 0;
}
