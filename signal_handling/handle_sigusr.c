#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

void signal_handler(int signal);

int main(int argc, char *argv[]) {
  int pid = fork();

  if (pid < 0)
    perror("Fork error!\n");

  if (!pid) {
    signal(SIGUSR1, signal_handler);
    while (1)
      sleep(1);
  }

  else {
    printf("Eu sou o processo pai, pid = %d\n", getpid());
    printf("O pid do meu filho eh = %d\n", pid);
    fflush(stdout);
    sleep(5);
    kill(pid, SIGUSR1);
    sleep(20);
    if (!waitpid(pid, NULL, WNOHANG)) {
      printf("Meu filho ainda não terminou. Cansei de esperar, vou vazar com u"
             "m sinal SIGKILL\n");
      // kill(getpid(), SIGKILL);
      raise(SIGKILL);
    }
    printf("Meu filho terminou normalmente (:\n");
  }

  return 0;
}

void signal_handler(int signal) {
  if (signal == SIGUSR1) {
    printf("Eu apanhei o SIGUSR1\n");
    char buffer[1000];
    printf("Digite alguma coisa no terminal: ");
    scanf("%[^\n]", buffer);
    printf("%s\n", buffer);
    exit(0);
  }
}
