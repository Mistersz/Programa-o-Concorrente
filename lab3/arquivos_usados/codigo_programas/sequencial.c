
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char*argv[]) {
  
   float *matriz; //matriz que será carregada do arquivo
   float *matriz2;
   float *matriz3;
   int linhas, colunas; //dimensoes da matriz
   int linhas2, colunas2; //dimensoes da matriz2

   long long int tam; //qtde de elementos na matriz
   long long int tam2; // qtde de elementos na matriz2

   FILE * descritorArquivo; //descritor do arquivo de entrada
   FILE * descritorArquivo2; //descritor do arquivo de entrada
   FILE * descritorArquivo3; //descritor do arquivo de entrada
   size_t ret; //retorno da funcao de leitura no arquivo de entrada
   
   int i,j;

   float soma;
   soma = 0;

   double elapsedTime;

   // Começa a contar o tempo de preparação (leitura das dimensões das matrizes + alocação de memória para elas + )
   struct timespec start, end, start_processo, end_processo, start_finalizacao, end_finalizacao;
   clock_gettime(CLOCK_MONOTONIC, &start);

   //recebe os argumentos de entrada
   if(argc < 4) {
      fprintf(stderr, "Digite: %s <arquivo entrada> <arquivo de entrada> <arquivo de saida> \n", argv[0]);
      return 1;
   }
   
   //abre o arquivo para leitura binaria
   descritorArquivo = fopen(argv[1], "rb");
   descritorArquivo2 = fopen(argv[2], "rb");



   if(!descritorArquivo) {
      fprintf(stderr, "Erro de abertura do arquivo\n");
      return 2;
   }

   if(!descritorArquivo2) {
      fprintf(stderr, "Erro de abertura do arquivo\n");
      return 2;
   }



   //le as dimensoes da matriz1
   ret = fread(&linhas, sizeof(int), 1, descritorArquivo);
   if(!ret) {
      fprintf(stderr, "Erro de leitura das dimensoes da matriz arquivo \n");
      return 3;
   }

   ret = fread(&colunas, sizeof(int), 1, descritorArquivo);
   if(!ret) {
      fprintf(stderr, "Erro de leitura das dimensoes da matriz arquivo \n");
      return 3;
   }

    // le as dimensoes da matriz2
   ret = fread(&linhas2, sizeof(int), 1, descritorArquivo2);
   if(!ret) {
      fprintf(stderr, "Erro de leitura das dimensoes da matriz arquivo \n");
      return 3;
   }

   ret = fread(&colunas2, sizeof(int), 1, descritorArquivo2);
   if(!ret) {
      fprintf(stderr, "Erro de leitura das dimensoes da matriz arquivo \n");
      return 3;
   }

    if(colunas != linhas2){
        printf("O número de colunas da primeira matriz precisa ser igual ao número de linhas da segunda");
        return 3;
    }


   tam = linhas * colunas; //calcula a qtde de elementos da matriz
   tam2 = linhas2 * colunas2; //calcula a qtde de elementos da matriz

  
   //aloca memoria para a matriz
   matriz = (float*) malloc(sizeof(float) * tam);
   if(!matriz) {
      fprintf(stderr, "Erro de alocao da memoria da matriz\n");
      return 3;
   }
   matriz2 = (float*) malloc(sizeof(float) * tam2);
   if(!matriz2) {
      fprintf(stderr, "Erro de alocao da memoria da matriz\n");
      return 3;
   }


   //carrega a matriz de elementos do tipo float do arquivo
   ret = fread(matriz, sizeof(float), tam, descritorArquivo);
   if(ret < tam) {
      fprintf(stderr, "Erro de leitura dos elementos da matriz\n");
      return 4;
   }

  ret = fread(matriz2, sizeof(float), tam2, descritorArquivo2);
   if(ret < tam2) {
      fprintf(stderr, "Erro de leitura dos elementos da matriz\n");
      return 4;
      }

    int tam3;
    tam3 = linhas * colunas2;
    matriz3 = malloc(sizeof(float)*tam3);

  
   clock_gettime(CLOCK_MONOTONIC, &end);
   elapsedTime = (end.tv_sec - start.tv_sec) +(end.tv_nsec - start.tv_nsec) / 1.0e9; 
   printf("Tempo de preparação: %f segundos\n", elapsedTime); 


   clock_gettime(CLOCK_MONOTONIC, &start_processo);

    // Realiza a multiplicação de matrizes
    for(i = 0;i<linhas;i++){
        for(j = 0; j<colunas2; j++){

            for(int k = 0; k < colunas; k++){
                soma += matriz[i*colunas + k] * matriz2[k*colunas2 + j];
            }
            matriz3[i*colunas2 + j] = soma;
            soma = 0;
        }
    }

  
   clock_gettime(CLOCK_MONOTONIC, &end_processo);
   elapsedTime = (end_processo.tv_sec - start_processo.tv_sec) + (end_processo.tv_nsec - start_processo.tv_nsec) / 1.0e9; 
   printf("Tempo de processamento: %f segundos\n", elapsedTime); 


   clock_gettime(CLOCK_MONOTONIC, &start_finalizacao);

   descritorArquivo3 = fopen(argv[3], "wb");
   ret = fwrite(&linhas, sizeof(int), 1, descritorArquivo3);
   ret = fwrite(&colunas2, sizeof(int), 1, descritorArquivo3);
   ret = fwrite(matriz3, sizeof(float), tam3, descritorArquivo3);
  
   if(ret < tam3) {
      fprintf(stderr, "Erro de escrita no  arquivo\n");
      return 4;
   }

   //finaliza o uso das variaveis

   fclose(descritorArquivo);
   fclose(descritorArquivo2);
 
   fclose(descritorArquivo3);
   free(matriz);
   free(matriz2);
   free(matriz3);

   clock_gettime(CLOCK_MONOTONIC, &end_finalizacao);
   elapsedTime = (end_finalizacao.tv_sec - start_finalizacao.tv_sec) + (end_finalizacao.tv_nsec - start_finalizacao.tv_nsec) / 1.0e9; 
   printf("Tempo de finalizacao: %f segundos\n", elapsedTime); 


   return 0;
}

