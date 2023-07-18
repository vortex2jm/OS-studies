#include <stdio.h>
#include <pthread.h>

void * routine(void * arg);

int main(int argc, char const *argv[])
{
  pthread_t thread1;
  void * t_return;
  int argument = 0;

  printf("Digite o valor que deseja dobrar: ");
  scanf("%d", &argument);

  pthread_create(&thread1, NULL,routine, &argument);
  pthread_join(thread1, &t_return);
  printf("Seu valor foi duplicado tem resultado = %d\n", *(int*)t_return);

  return 0;
}

void * routine(void * arg){
  pthread_t self = pthread_self();
  printf("Ola, sou a thread %ld e vou fazer seus calculos\n", self);
  *(int*)arg *= 2;
  return arg;
}
