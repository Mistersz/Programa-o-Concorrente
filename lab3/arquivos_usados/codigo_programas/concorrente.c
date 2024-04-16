#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>

// Define a struct que sera usada para passar argumentos para as threads.
typedef struct {
   int thread;
   int relacao;
   int *colunas2;
   int *colunas;
   float *matriz;
   float *matriz2;
   float *matriz3;
} t_Args;


int linhas, colunas; //dimensoes da matriz
int linhas2, colunas2; //dimensoes da matriz2

int M;

float *matriz; // Matriz que será carregada do arquivo
float *matriz2; // Matriz 2 que será carregada do arquivo
float *matriz3; // Matriz 3 que será gerada neste arquivo

int auxiliar_resto;

void *multiplica_matriz (void *arg) {
  
  t_Args *args = (t_Args *) arg;
  float soma;
  soma = 0;
 
   int i;
   int j;
   int k;

   int id;
   int proporcao;

   id = args->thread;
   proporcao = args->relacao;

if (args->thread < auxiliar_resto) {

    // printf("A thread %d está executando a linha %d da matriz final\n - Execução extra\n",args->thread, *(args->colunas) -1-args->thread);
   
   for(j = 0; j < *(args->colunas2);j++)
         {
                  for(int k = 0; k < *(args->colunas); k++){
                     soma += args->matriz[(*(args->colunas)-1-args->thread) * (*(args->colunas)) + k] * args->matriz2[k*(*(args->colunas2))+ j];
                  }
                  args->matriz3[(*(args->colunas)-1-args->thread) * (*(args->colunas2))+ j] = soma;

                  soma = 0;
         }  

}

   for(i = id*proporcao; i<id*proporcao+proporcao; i++){
             

        //printf("A thread %d está executando a linha %d da matriz final\n",args->thread,i);
            for(j = 0; j< *(args->colunas2);j++){

                for(int k = 0; k < *(args->colunas); k++){
                    soma += args->matriz[i* (*(args->colunas)) + k] * args->matriz2[k*(*(args->colunas2))+ j];
                }
                args->matriz3[i*(*(args->colunas2))+ j] = soma;
                soma = 0;
            }
        }
   
    //printf("A thread %d acabou\n",args->thread);   
    //printf("\n");           

   pthread_exit(NULL);
   }
  


int main(int argc, char*argv[]) {


   float *matriz; // Matriz que será carregada do arquivo
   float *matriz2; // Matriz  que será carregada do arquivo
   float *matriz3; // Matriz  que será gerada neste arquivo

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

   auxiliar_resto = 0;

   // Começa a contar o tempo de preparação
   struct timespec start, end, start_processo, end_processo, start_finalizacao, end_finalizacao;
   double elapsedTime;
   clock_gettime(CLOCK_MONOTONIC, &start);


   //recebe os argumentos de entrada
   if(argc < 5) {
      fprintf(stderr, "Digite: %s <arquivo entrada> <arquivo de entrada> <arquivo de saida> <numero de threads>\n", argv[0]);
      return 1;
   }
   
    M = atoi(argv[4]);

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


    if(colunas < M){
        M = colunas;
    }

   tam = linhas * colunas; //calcula a qtde de elementos da matriz
   tam2 = linhas2 * colunas2; //calcula a qtde de elementos da matriz


   //Aloca memoria para as matrizes
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

   auxiliar_resto = linhas % M;

    int tam3;
    tam3 = linhas * colunas2;
    matriz3 = malloc(sizeof(float)*tam3);
 
    t_Args *args;
    pthread_t tid_sistema[M];
    

   // Termina o tempo de preparação
   clock_gettime(CLOCK_MONOTONIC, &end);
   elapsedTime = (end.tv_sec - start.tv_sec) +(end.tv_nsec - start.tv_nsec) / 1.0e9; 
   printf("Tempo de preparação: %f segundos\n", elapsedTime); 


   clock_gettime(CLOCK_MONOTONIC, &start_processo);


    // Cria as threads
    for (i=0; i<M; i++) {

            args = malloc(sizeof(t_Args));
            //printf("Thread %d criada\n",i);

            args->thread = i;
            args->relacao = (linhas / M);

            args->colunas2 = &colunas2;
            args->colunas = &colunas;

            args->matriz = matriz;
            args->matriz2 = matriz2;
            args->matriz3 = matriz3;


            if (pthread_create(&tid_sistema[i], NULL, multiplica_matriz, (void*)args)) {
                printf("--ERRO: pthread_create()\n"); exit(-1);
            }

    }



    // Espera as threads terminarem e recebe seus retornos
    for (int i=0; i<M; i++) {
        
        if(pthread_join(tid_sistema[i],NULL)) {

            printf("--ERRO: pthread_join() \n"); exit(-1);
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

   //Finaliza o uso das variaveis

   fclose(descritorArquivo);
   free(matriz);
   free(matriz2);
   free(matriz3);

   clock_gettime(CLOCK_MONOTONIC, &end_finalizacao);
   elapsedTime = (end_finalizacao.tv_sec - start_finalizacao.tv_sec) + (end_finalizacao.tv_nsec - start_finalizacao.tv_nsec) / 1.0e9; 
   printf("Tempo de finalizacao: %f segundos\n", elapsedTime); 

   printf("\n--Thread principal terminou\n");
   pthread_exit(NULL);

   return 0;
}
