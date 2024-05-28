
/* Programa que cria arquivo com uma matriz de valores do tipo float, gerados aleatoriamente 
 * Entrada: dimensoes da matriz (linhas e colunas) e nome do arquivo de saida
 * Saida: arquivo binario com as dimensoes (valores inteiros) da matriz (linhas e colunas), 
 * seguido dos valores (float) de todas as celulas da matriz gerados aleatoriamente
 * */



#include<stdio.h>
#include<stdlib.h>
#include<time.h>

//#define TEXTO 

int main(int argc, char*argv[]) {
   int  *matriz; //matriz que será gerada
   FILE * descritorArquivo; //descritor do arquivo de saida
   size_t ret; //retorno da funcao de escrita no arquivo de saida
   
   //recebe os argumentos de entrada
   if(argc < 2) {
      fprintf(stderr, "Digite: %s <numeros> <arquivo saida>\n", argv[0]);
      return 1;
   }

  srand(time(NULL));
   int numeros;
   numeros = atoi(argv[1]); 

   //aloca memoria para a matriz
   matriz = (int*) malloc(sizeof(int) * numeros);

  // Lida com erro de alocação
   if(!matriz) {
      fprintf(stderr, "Erro de alocao da memoria da matriz\n");
      return 2;
   }

  // Escreve os numeros na matriz
   for(int i=1; i<numeros+1; i++) {

    *(matriz+(i-1)) = i;
   
  }


   //escreve a matriz no arquivo
   //abre o arquivo para escrita binaria
 
   descritorArquivo = fopen(argv[2], "wb");
   if(!descritorArquivo) {
      fprintf(stderr, "Erro de abertura do arquivo\n");
      return 3;
   }

   //escreve o tamanhao antes e depois os elementos da matriz
  
   ret = fwrite(&numeros, sizeof(int), 1, descritorArquivo);
   printf("%d",numeros);

   ret = fwrite(matriz, sizeof(int), numeros, descritorArquivo);
   if(ret < numeros) {
      fprintf(stderr, "Erro de escrita no  arquivo\n");
      return 4;
   }

   //finaliza o uso das variaveis
   fclose(descritorArquivo);
   free(matriz);
   return 0;
}

