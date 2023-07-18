#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

#define ARRAY_SIZE 100000000
#define THREADS_AMOUNT 1

long int sum=0;
long int array_index=0;
pthread_mutex_t mutex;
long int * array_global;

void * routine(void * arg);
void * alternative_routine(void * arg);

int main(int argc, char const *argv[])
{
  //=======================================//
  if(argc < 2){
    perror("Digite qual rotina deseja usar\n");
    exit(1);
  }

  int rout = atoi(argv[1]);
  if(rout != 1 && rout != 2){
    perror("Rotina invalida\n");
    exit(1);
  }
  //=========================================//

  //========================================================//
  long int * array = malloc(sizeof(long int) * ARRAY_SIZE);
  for(int x=0; x<ARRAY_SIZE; x++){
    array[x] = x+1;
  }
  array_global = array;
  //========================================================//

  pthread_mutex_init(&mutex, NULL);

  //=============================================//
  if(rout == 1){
    pthread_t threads[THREADS_AMOUNT];
    
    for(int x=0; x<THREADS_AMOUNT; x++){
        if(pthread_create(&threads[x], NULL, routine, array)){
          perror("Erro ao criar thread");
          exit(1);
        } 
    }

    for(int x=0; x<THREADS_AMOUNT; x++){
      pthread_join(threads[x], NULL);
    }
  }
  
  //=============================================//
  else{
    int arg1=1, arg2=2;
    pthread_t threads[2];
    if(pthread_create(&threads[0], NULL, alternative_routine, &arg1)){
      perror("Erro ao criar thread 1");
      exit(1);
    }
    if(pthread_create(&threads[1], NULL, alternative_routine, &arg2)){
      perror("Erro ao criar thread 2");
      exit(1);
    }
    for(int x=0; x<2; x++){
      pthread_join(threads[x], NULL);
    }
  }

  //=============================//
  if(rout==1){
    printf("//====Resultado obtido utilizando %d threads alternando entre os índices do vetor====//");
  }
  else{
        printf("//====Resultado obtido utilizando 2 threads somando cada metade do vetor====//");
  }
  printf("A soma dos valores do vetor eh = %ld\n", sum);
  
  //================//
  pthread_mutex_destroy(&mutex);
  return 0;
}

//=======funcoes de rotina========//

//Pegando o proximo indice livre e somando
void * routine(void * arg){
  long int local_index=0;
  long int * local_array = (long int*)arg;
  long int partial_sum=0;

  while(local_index < ARRAY_SIZE){
    pthread_mutex_lock(&mutex);
    local_index = array_index;
    array_index++;
    pthread_mutex_unlock(&mutex);
    if(local_index < ARRAY_SIZE){
      partial_sum += local_array[local_index];
    }
  }

  pthread_mutex_lock(&mutex);
  sum += partial_sum;
  pthread_mutex_unlock(&mutex);

  pthread_exit(NULL);
}

// Somando cada metade em uma thread
void * alternative_routine(void * arg){
  long int partial_sum=0;

  if(*(int*)arg == 1){   
    for(int x=0; x<ARRAY_SIZE/2; x++){
      partial_sum+= array_global[x];
    }
  }
  else{
    for(int x=ARRAY_SIZE/2; x<ARRAY_SIZE; x++){
      partial_sum+= array_global[x];
    }
  }
  pthread_mutex_lock(&mutex);
  sum += partial_sum;
  pthread_mutex_unlock(&mutex);

  pthread_exit(NULL);
}
