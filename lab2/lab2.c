#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <math.h>


typedef struct {
   int thread;
   int relacao;
   float *soma;
} t_Args;


float *vetor;
int numeros_por_threads;
int resto;
int numero_threads;
int auxiliar;


//Funcao executada pelas threads
void *soma_threads (void *arg) {
  
    t_Args *args = (t_Args *) arg;
    int i;
    int index_local = args->thread * args->relacao;

    args->soma = malloc(sizeof(float));
    *(args->soma) = 0;


    printf("\nA thread %d comecou\n",args->thread);

      
    if (resto != 0) {

        printf("Passou do limite, sou a thread: %d!\n",args->thread);

        for(i = 0;i<args->relacao;i++)  {

          printf("A thread %d está executando a soma do número %.1f\n", args->thread, vetor[index_local]);
          *(args->soma) += vetor[index_local];
          index_local += 1;

        }
      
        printf("A thread %d está  adicionando a soma o número %.2f\n", args->thread, vetor[index_local]);
        *(args->soma) += vetor[args->relacao * numero_threads + auxiliar];
        auxiliar += 1;
        resto -= 1;
      }

  
    else {

    for(i = 0;i<args->relacao;i++){

        // printf("Index loctotalal = %d\n",index_local);
        printf("A thread %d está adicionando a soma o número %.1f\n", args->thread, vetor[index_local]);
        *(args->soma) += vetor[index_local];
        index_local += 1;
  
    }

    }
  printf("\n");
  pthread_exit((void*) args);

}



int main(int argc, char *argv[]) {

    int i;
    float soma_vetor;
    int M;
    int tamanho;
    t_Args *retorno;
    float numero;
    auxiliar = 0;

    scanf("%d",&tamanho);
    vetor = malloc( tamanho * sizeof(float));

    // Lendo o vetor dos arquivos
    for (i=0; i<tamanho; i++) {

      scanf("%f",&numero);
      vetor[i] = numero;      
      printf("%.1f ",vetor[i]);

    }


    soma_vetor = 0;
    numero_threads = atoi(argv[1]);
    retorno = malloc(tamanho * sizeof(float));

    printf("O Numero de threads criadas é %d\n",numero_threads);
    M = numero_threads;

    // Printa o vetor
    printf("\nVetor: ");
      for (i=0; i<tamanho; i++){
          printf("%.0f ",vetor[i]);
      }
  
    printf("\n");

    // Identificadores para as threads.
    pthread_t tid_sistema[M];

    // Cria o vetor de struct. Isso serve para podermos passar mais de um número para as threads trabalharem
    t_Args *args;
    numeros_por_threads = tamanho/M;
    resto = tamanho % M;
 
  for (i=0; i<M; i++){

        args = malloc(sizeof(t_Args));
        printf("Thread %d criada\n",i);
        args->thread = i;
        args->relacao = numeros_por_threads;

        if (pthread_create(&tid_sistema[i], NULL, soma_threads, (void*)args)) {
            printf("--ERRO: pthread_create()\n"); exit(-1);
        }

  }
 

  // Espera as threads terminarem e recebe o retorno das threads
  for (int i=0; i<M; i++) {
    
    if(pthread_join(tid_sistema[i], (void**) &retorno)) {
         printf("--ERRO: pthread_join() \n"); exit(-1);
    }

    soma_vetor += *(retorno->soma);

  }

  printf("O resultado da soma foi: %.2f",soma_vetor);

  printf("\n--Thread principal terminou\n");
  pthread_exit(NULL);



    return 0;
}
