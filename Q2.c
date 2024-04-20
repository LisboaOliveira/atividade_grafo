#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define tamanho 2355

int main(){
int linha = 0, coluna =0;
char zoru;
FILE *arquivo;

int **matriz = (int **)malloc(tamanho * sizeof(int *));
int i, j;
for (i = 0; i < tamanho; i++)
matriz[i] = (int *)malloc(tamanho * sizeof(int));

arquivo = fopen("dados.txt", "r");

if(arquivo == NULL){
    printf("Deu ruim!");
    exit (1);
}

while((zoru = fgetc(arquivo)) != EOF){
    if(zoru == '0' || zoru == '1'){
    matriz[linha][coluna] = zoru - '0';
    coluna ++;
    }
    if(coluna == tamanho){
        coluna = 0;
        linha ++;
    }
}

fclose(arquivo);

int cont = 0;

arquivo = fopen("dados_grafos_graus.txt", "w");

for (i = 0; i < tamanho; i++){
    for (j = 0; j < tamanho; j++){
        if (matriz[i][j] == 1){
            cont++;
        }
    }
    fprintf(arquivo, "vertice %i tem %i graus\n", i + 1, cont);

    cont = 0;
}

fclose(arquivo);

return 0;}