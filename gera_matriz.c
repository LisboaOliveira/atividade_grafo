#include<stdio.h>
#include<stdlib.h>

#define tamanho 2355

int main(){
int matriz[tamanho][tamanho], linha = 0, coluna =0;
char zoru;
FILE *arquivo;

arquivo = fopen("dados.txt", "r");

if(arquivo == NULL){
    printf("Deu ruim!");
    exit (1);
}

while((zoru = fgetc(arquivo)) != EOF){
    matriz[linha][coluna] = zoru - '0';
    coluna ++;
    if(coluna == tamanho){
        coluna = 0;
        linha ++;
    }
}

fclose(arquivo);

for(int i = 0; i < tamanho; i++){
    for(int j = 0; j < tamanho; j ++){
        printf("%i", matriz[i][j]);
    }
    printf("\n");
}

return 0;
}
