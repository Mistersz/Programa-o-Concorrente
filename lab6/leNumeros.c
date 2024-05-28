/* Programa que le um arquivo binario com dois valores inteiros (indicando as dimensoes de uma matriz) 
 * e uma sequencia com os valores da matriz (em float)
 * Entrada: nome do arquivo de entrada
 * Saida: valores da matriz escritos no formato texto (com 6 casas decimais) na saida padrao 
 * */

#include<stdio.h>
#include<stdlib.h>
#include <math.h>

int ehPrimo(long long int n) {
int i;
if (n<=1) return 0;
if (n==2) return 1;
if (n%2==0) return 0;
for (i=3; i<sqrt(n)+1; i+=2)
if(n%i==0) return 0;
  return 1;

}


int main(int argc, char*argv[]) {
   int *matriz; //matriz que será carregada do arquivo
   int numeros; //dimensoes da matriz
   FILE * descritorArquivo; //descritor do arquivo de entrada
   size_t ret; //retorno da funcao de leitura no arquivo de entrada
   
   //recebe os argumentos de entrada
   if(argc < 2) {
      fprintf(stderr, "Digite: %s <arquivo entrada>\n", argv[0]);
      return 1;
   }
   
   //abre o arquivo para leitura binaria
   descritorArquivo = fopen(argv[1], "rb");
   if(!descritorArquivo) {
      fprintf(stderr, "Erro de abertura do arquivo\n");
      return 2;
   }


  ret = fread(&numeros, sizeof(int), 1, descritorArquivo);
   if(!ret) {
      fprintf(stderr, "Erro de leitura dos numeros \n");
      return 3;
   }
 

   //aloca memoria para a matriz
   matriz = (int*) malloc(sizeof(int)*numeros);

   if(!matriz) {
      fprintf(stderr, "Erro de alocao da memoria da matriz\n");
      return 3;
   }
    //carrega a matriz de elementos do tipo float do arquivo
   ret = fread(matriz, sizeof(int), numeros, descritorArquivo);
   if(ret < numeros) {
      fprintf(stderr, "Erro de leitura dos elementos da matriz\n");
      return 4;
   }
  int primos = 0;
  int b;
  //imprime a matriz na saida padrao
 
    for(int i=0; i<numeros; i++) {

      b = ehPrimo(matriz[i]);

      if (b == 1){
      printf("Primo = ");
      primos++;

    }

      fprintf(stdout, "%d ", matriz[i]);
      fprintf(stdout, "\n");
   }

    printf("Foram encontrados %d numeros primos no arquivo\n",primos);
   //finaliza o uso das variaveis
   fclose(descritorArquivo);
   free(matriz);
   return 0;
}

