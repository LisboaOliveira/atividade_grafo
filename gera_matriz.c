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

/*for(int i = 0; i < tamanho; i++){
    for(int j = 0; j < tamanho; j ++){
        printf("%i", matriz[i][j]);
    }
    printf("\n");
}*/

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

/*for(i = 0; i < tamanho; i++){
    for(j = 0; j < tamanho; j++){
        if(matriz[i][j] == 1){
           cont++;
        }
    }
    if(cont == maior){
        p+=1;
        int *outro = realloc(VmaiorG, (p + 1) * sizeof(int));
        VmaiorG = outro;
        VmaiorG[p] = i;
        
    }
    cont = 0;
}o vértice 743 é o maior de todos*/

//2. Apresente em um arquivo chamado dados_grafos_graus.txt o número do vértices seguido pelo seu respectivo grau
arquivo = fopen("dados_grafos_graus.txt", "w");
fprintf(arquivo, "%i = %i\n", VmaiorG[0], maior);
fclose(arquivo);

//3. Se existir, quais são os vértices isolados?
for (i = 0; i < tamanho; i++){
    for (j = 0; j < tamanho; j++){
        if (matriz[i][j] == 1){
            cont++;
        }
    }
    if (cont == 0){
        arquivo = fopen("isolados.txt", "w");
        fprintf(arquivo, "%i\n", i);
        fclose(arquivo);
    }
    cont = 0;
}
//não tem vértices isolados

//4. Existe um vértice sumidouro?
 arquivo = fopen("sumidouro.txt", "w");
for (i = 0; i < tamanho; i++){
    for (j = 0; j < tamanho; j++){
        if (matriz[i][j] == 1){
            cont++;
        }
    }
    if (cont == (tamanho - 1)){
        fprintf(arquivo, "%i\n", i);
    }
    cont = 0;
}
fclose(arquivo);
//como o vértice com maior grau so tem 1262 graus e o sumidouro teria que ter 2354 não existe sumidouro nesta matriz.
//mais fica ai o confere de toda forma...

//5. Existe um vértice fonte?
arquivo = fopen("direçãoacima.txt", "w");
for (i = 0; i < tamanho; i++){
    for (j = 0; j < tamanho; j++){
        if (matriz[i][j] == 1){
            cont++;
        }
        if (cont == 0 && i == j){
            fprintf(arquivo, "%i\n", i);
            i++;
            j = 0;
            cont = 0;
        }   
    }
    
    cont = 0;
}//confere se os valores abaixo da diagonal principal são todos 0
fclose(arquivo);
arquivo = fopen("direçãoabaixo.txt", "w");
for (i = 0; i < tamanho; i++){
    for (j = (tamanho-1); j >= 0; j--){
        if (matriz[i][j] == 1){
            cont++;
        }
        if (cont == 0 && i == j){
            fprintf(arquivo, "%i\n", i);
            i++;
            j = (tamanho - 1);
            cont = 0;
        }   
    }
    cont = 0;
}//confere se os valores acima da diagonal principal são todos 0
fclose(arquivo);
//o grafo não é direcional. Logo não se aplica nem a questão 4 nem a 5, mesmo assim fica os confere ai...

//6. Determine o grau de Emissão e Recepção de cada vértice e os coloque em arquivos chamados de "dados_grafos_emissao.txt" e "dados_grafos_recepcao.txt"
//também não se aplica

//7. Apresente um arquivo com o grafo complementar da questão;
arquivo = fopen("complementar.txt", "w");
for (i = 0; i < tamanho; i++){
    for (j = 0; j < tamanho; j++){
        if (matriz[i][j] == 1){
            fprintf(arquivo, "%i ", 0);
        }else{
            fprintf(arquivo, "%i ", 1);
        }
    }
    fprintf(arquivo, "\n");
}
fclose(arquivo);

//8. Inverta a direção de todas as arestas do grafo da questão e apresente-os em um novo arquivo com o nome de "dados_grafos_invertido.txt".
//não se aplica

//9. Apresente o grafo complementar e os represente em um arquivo com o nome "dados_grafo_complementar.txt".
//não entendi essa, to achando que é para repeitir oq fiz na questão 7 com o arquivo recebendo outro nome...

//10. Apresente um novo arquivo chamado "dados_grafo_gerador.txt" com os vértices múltiplos de 5.
arquivo = fopen("dados_grafo_gerador.txt", "w");
for (i = 0; i < tamanho; i++){
    for (j = 0; j < tamanho; j++){
        if (matriz[i][j] == 1){
            cont++;
        }
    }
    if (cont % 5 == 0){ 
        fprintf(arquivo, "%i com %i vertices\n", i, cont);
    }   
    cont = 0;
}
 fclose(arquivo);

 //11. Encontre o maior clique do grafo da questão.
 

 //12. Verifique se o primeiro e último vértice estão conectados
 if(matriz[0][tamanho - 1] == 1){
    printf("o primeiro e ultimo vertice estao conectados\n");
 }else{
    printf("o primeiro e ultimo vertice nao estao conectados\n");
 }// tambem da pra comfeirir com comando gdb print matriz[0][2354] ou matraiz[2354][0], se for igual a 1 entoa estao conectados

return 0;
}