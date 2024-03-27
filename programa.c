#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <math.h>



typedef struct {
   int thread;
   int relacao;
} t_Args;


float *vetor;
int numeros_por_threads;
int resto;
int numero_threads;

//Funcao executada pelas threads
void *numeros_quadrados (void *arg) {
   
    t_Args *args = (t_Args *) arg;
    int i;
    int index_local = args->thread * args->relacao;

    printf("A thread %d comecou\n",args->thread);
   
    if (args->thread == numero_threads  - 1 && resto != 0) {
        printf("EU SOU A THREAD %d!\n",args->thread);

        for(i = 0;i<args->relacao+resto;i++){
       
        printf("Index local = %d\n",index_local);
        printf("A theard %d está elevando ao quadrado numero %0.f\n", args->thread, vetor[index_local]);
        vetor[index_local] *= vetor[index_local];
        printf("Número elevado ao quadrado\n");
        index_local += 1;
   
    }

    }
   
    else {
       
    for(i = 0;i<args->relacao;i++){
       
        // printf("Index local = %d\n",index_local);
        printf("A theard %d está elevando ao quadrado o seguinte numero %0.f\n", args->thread, vetor[index_local]);
        vetor[index_local] *= vetor[index_local];
        index_local += 1;
   
    }

    

 
    }
  pthread_exit(NULL);
}




int main() {

    int i;
    int M;
    int N;

    printf("Insira o numero de threads\n");
    scanf("%d",&M);
    printf("Insira o tamanho do vetor\n" );
    scanf("%d",&N);
    vetor = malloc( N * sizeof(int));
    numero_threads = M;
    srand(time(NULL));
    int intervalo;
   


    printf("Insira aqui um intervalo para gerarmos numeros aleatorios de 0 a este numero ");
    scanf("%d",&intervalo);
   
    for (i=0; i<N; i++){
      int r = rand() % intervalo+1;
        vetor[i] = r;
    }
    printf("\nVetor: ");
    for (i=0; i<N; i++){
        printf("%.0f ",vetor[i]);
    }
 
    printf("\n");

    // Identificadores para as threads.
    pthread_t tid_sistema[M];

    // Cria o vetor de struct. Isso serve para podermos passar mais de um número para as threads trabalharem
    t_Args *args;
    numeros_por_threads = N/M;
    resto = N % M;
 
  for (i=0; i<M; i++){

        args = malloc(sizeof(t_Args));

       

        args->thread = i;
        args->relacao = numeros_por_threads;

        if (pthread_create(&tid_sistema[i], NULL, numeros_quadrados, (void*)args)) {
            printf("--ERRO: pthread_create()\n"); exit(-1);
        }
       

  }
 

// Espera as threads terminarem
  for (int i=0; i<M; i++) {
    if(pthread_join(tid_sistema[i], NULL)) {
         printf("--ERRO: pthread_join() \n"); exit(-1);
    }
  }





  printf("\n------------------------------------------\n");
  printf("\nVetor antigo: ");
    for (i=0; i<N; i++){

      printf("%.0f ",pow(vetor[i],0.5));

      }
     
  printf("\nVetor novo: ");  
    for (i=0; i<N; i++){
        printf("%.0f ",vetor[i]);
    }

  // Tira a prova real com cada elemento do vetor

  printf("\nVetor após passar pala função de raiz quadrada: \n");
      for (i=0; i<N; i++){
      printf("%.0f ",pow(vetor[i],0.5));
           }
 
  printf("\n--Thread principal terminou\n");
  pthread_exit(NULL);




    return 0;
}
