

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <math.h>


#define PRODUTORES 1
// #define CONSUMIDORES 3
// #define MAX (PRODUTORES+CONSUMIDORES)



sem_t slotCheio, slotVazio;  // semaforos para sincronizacao por condicao
sem_t mutexGeral; //semaforo UNICO para sincronizacao entre produtores e consumidores e para log
FILE * descritorArquivo; //descritor do arquivo de entrada
size_t ret; //retorno da funcao de leitura no arquivo de entrada
 
int *Buffer;
int *matriz;
int aux = 0;
int *maior;
int max;


typedef struct {
  int t_id;
  int tamanho;
  int *numeros;
} t_Args;


// Função para determinar se o numero e primo ou nao
int ehPrimo(long long int n) {
  int i;
  if (n<=1) return 0;
  if (n==2) return 1;
  if (n%2==0) return 0;
  for (i=3; i<sqrt(n)+1; i+=2)
  if(n%i==0) return 0;
    return 1;

}


//Funcao para inserir um elemento no buffer
void Insere (int item, int id,int N) {
   static int in=0;
   sem_wait(&slotVazio); //aguarda slot vazio para inserir // Começa em 5
   sem_wait(&mutexGeral); //exclusao mutua entre produtores (aqui geral para log)
   Buffer[in] = item; 
   in = (in + 1) % N;
    //  printf("Prod[%d]: inseriu %d\n", id, item);
   for(int i=0; i<N; i++) 
	 //  printf("%d ", Buffer[i]); 
   //puts("");
   sem_post(&mutexGeral);
   sem_post(&slotCheio); //sinaliza um slot cheio
}

//Funcao para retirar  um elemento no buffer
int Retira (int id, int N) {


   int item;
   static int out=0;
  

   sem_wait(&slotCheio); //aguarda slot cheio para retirar
   sem_wait(&mutexGeral); //exclusao mutua entre consumidores (aqui geral para log)

   item = Buffer[out];
   Buffer[out] = 0;
   out = (out + 1) % N;
   // printf("Cons[%d]: retirou %d\n", id, item);
   for(int i=0; i<N; i++) 
	 //  printf("%d ", Buffer[i]); 
   //  puts("");
   sem_post(&mutexGeral);
   sem_post(&slotVazio); //sinaliza um slot vazio
   return item;
}



//----------------------------------------------------------
// Função executada pela thread Produtor  

void *produtor(void * arg) {
  t_Args *args = (t_Args *) arg;

    for(int i=0; i<args->tamanho;i++){
      Insere(args->numeros[i],args->t_id, args->tamanho);
    
    }
  
  free(arg);
  pthread_exit(NULL);

}


//----------------------------------------------------------
// Consumidor
void *consumidor(void * arg) {
 

  t_Args *args = (t_Args *) arg;
  int item;
 // int id = *(int *)(arg);
  int id = args->t_id; 
 // int pares = 0;
  int primos = 0;


    for(int i=0; i<args->tamanho;i++){

      // Condicional com o intuito de evitar que threads tentem ler mesmo depois do numero de leituras
      // ser maior do que o numero de elementos presentes no buffer.
   
      sem_wait(&mutexGeral); 
      if(aux >= args->tamanho) {

      free(arg);
      printf("A thread %d achou %d primos!\n",id,primos);

      sem_post(&mutexGeral); 
      pthread_exit(NULL);

    }

    aux +=1;
    sem_post(&mutexGeral); 
 
    item = Retira(id,args->tamanho);

    if(ehPrimo(item) == 1){
     //printf("%d primo \n",item);
 
      primos++;

      // Trecho do código que calcula a quantidade de primo por thread + thread com maiores primos +
      // numero de primos total
      sem_wait(&mutexGeral); 
      
      maior[2] += 1;

      if(primos > maior[0]){
        maior[1] = args->t_id;
        maior[0] = primos;
      
      }

      sem_post(&mutexGeral); 
    }


  }


  free(arg);
  printf("A thread %d achou %d primos!\n",id,primos);
    pthread_exit(NULL);
}



// Funcao principal
int main(int argc, char **argv) {


  int i, *id;
  int tamanho_buffer;
  

  // Trata erros de input impróprio na linha de comando
   if(argc < 2) {
      printf("Digite: <arquivo entrada> <numero de threads>\n");
      return 1;
   }
 
  // Recebe o numero de threads
  int consumidores = atoi(argv[2]);

  pthread_t tid[consumidores+1];

  // Trata erros na abertura do arquivo
   descritorArquivo = fopen(argv[1], "rb");
   if(!descritorArquivo) {
      fprintf(stderr, "Erro de abertura do arquivo\n");
      return 2;
   }

  // Le a quantidade de numeros do arquivo binario
  ret = fread(&tamanho_buffer , sizeof(int), 1, descritorArquivo);
   if(!ret) {
      fprintf(stderr, "Erro de leitura dos numeros \n");
      return 3;
   }
 

  // Aloca o vetor que contém os numeros do arquivo binario
  matriz = malloc(sizeof(int)*tamanho_buffer);
  if (!matriz) {
      fprintf(stderr, "Erro de alocao da memoria da matriz\n");
      return 3;
  }


  // Bota os numeros contidos no arquivo binario em um vetor
  ret = fread(matriz, sizeof(int), tamanho_buffer, descritorArquivo);
  if(ret < tamanho_buffer) {
    fprintf(stderr, "Erro de leitura dos elementos da matriz\n");
    return 4;
  }

  // Descomentar caso queira ler os numeros
  /*
  for(int i=0; i<tamanho_buffer; i++) { 
    fprintf(stdout, "%d ", matriz[i]);
    fprintf(stdout, "\n");
  }
  */

  
  t_Args *args;
  t_Args *args2;

  Buffer = malloc(tamanho_buffer*sizeof(int));
  maior = malloc(3*sizeof(int));
  maior[2] = 0;

  // Inicia os semaforos
  sem_init(&mutexGeral, 0, 1); //binario
  sem_init(&slotCheio, 0, 0); //contador // Vai indicar slots cheios
  sem_init(&slotVazio, 0, tamanho_buffer); //contador  // Vai indicar slots vazios
  


  args = malloc(sizeof(t_Args));
  args2 = malloc(sizeof(t_Args));


  // Inicia os threads produtores
  for(i=0;i<PRODUTORES;i++) {
    
    args = malloc(sizeof(t_Args));
    args->tamanho = tamanho_buffer;
    args->numeros = matriz;

    id = (int *) malloc(sizeof(int));
    *id = i+1;

    args->t_id = *(id);

    if (pthread_create(&tid[i], NULL, produtor, (void *) args)) {
      printf("Erro na criacao do thread produtor\n");
      exit(1);
    }
  }
  // Inicia os threads consumidores
  for(i=0;i<consumidores;i++) {


    args2 = malloc(sizeof(t_Args));
    args2->tamanho = tamanho_buffer;
    args2->numeros = matriz;


    id = (int *) malloc(sizeof(int));
    *id = i+1;
    args2->t_id = *(id);

    if (pthread_create(&tid[PRODUTORES+i], NULL, consumidor, (void *) (args2))) {
      printf("Erro na criacao do thread produtor\n");
      exit(1);
    }
  }



  // Parte do programa que espera todas as threads consumidoras terminarem
    for(int i=0; i<consumidores+1; i++) {
        
        if(pthread_join(tid[i],NULL)) {

            printf("--ERRO: pthread_join() \n"); exit(-1);
        }


    }
  printf("A quantidade de primos total é de %d\n",maior[2]);
  printf("A thread vencedora foi a %d com %d numeros primos",maior[1],maior[0]); 



  pthread_exit(NULL);
}




