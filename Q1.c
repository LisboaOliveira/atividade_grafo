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

int *VmaiorG  = (int *)malloc(1 * sizeof(int *));
int maior = 0, cont = 0, p = 0;

//1. Qual(is) o vértice(s) com maior(es) grau?
for (i = 0; i < tamanho; i++){
    for (j = 0; j < tamanho; j++){
        if (matriz[i][j] == 1){
            cont++;
        }
    }
    if (cont > maior){
        maior = cont;
        VmaiorG[p] = i;
    }
    cont = 0;
}//o vértice com maior grau é o 743 com 1262 graus 

return 0;}