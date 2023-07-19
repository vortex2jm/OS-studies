#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#define key(A) (A)
#define less(A, B) (key(A) < key(B))
#define exch(A, B)                                                             \
  {                                                                            \
    int t = A;                                                                 \
    A = B;                                                                     \
    B = t;                                                                     \
  }
#define compexch(A, B)                                                         \
  if (less(B, A))                                                              \
  exch(A, B)
#define SIZE 1000

void bubble_sort(int *a, int lo, int hi);
void quickSort(int valor[], int esquerda, int direita);

int main(int argc, char *argv[]) {

  int array[SIZE];

  srand(time(NULL));
  for (int x = 0; x < SIZE; x++) {
    array[x] = rand() % 10000;
  }

  int fork_ret = fork();
  clock_t bubble_start, bubble_end, quick_start, quick_end;
  double bubble_time, quick_time;

  if (fork_ret > 0) {
    bubble_start = clock();
    bubble_sort(array, 0, SIZE - 1);
    bubble_end = clock();
    bubble_time = ((double)bubble_end - bubble_start) / CLOCKS_PER_SEC;
    printf("Tempo de ordenação do bubble = %lf\n", bubble_time);
    kill(fork_ret, SIGINT);
  }

  else if (!fork_ret) {
    quick_start = clock();
    quickSort(array, 0, SIZE - 1);
    quick_end = clock();
    quick_time = ((double)quick_end - quick_start) / CLOCKS_PER_SEC;
    printf("Tempo de ordenação do quick = %lf\n", quick_time);
    kill(getppid(), SIGINT);
  }

  return 0;
}

void bubble_sort(int *a, int lo, int hi) {
  if (!hi)
    return;
  for (int x = lo; x < hi; x++) {
    compexch(a[x], a[x + 1]);
  }
  bubble_sort(a, lo, hi - 1);
}

void quickSort(int valor[], int esquerda, int direita) {
  int i, j, x, y;
  i = esquerda;
  j = direita;
  x = valor[(esquerda + direita) / 2];
  while (i <= j) {
    while (valor[i] < x && i < direita) {
      i++;
    }
    while (valor[j] > x && j > esquerda) {
      j--;
    }
    if (i <= j) {
      y = valor[i];
      valor[i] = valor[j];
      valor[j] = y;
      i++;
      j--;
    }
  }
  if (j > esquerda) {
    quickSort(valor, esquerda, j);
  }
  if (i < direita) {
    quickSort(valor, i, direita);
  }
}
