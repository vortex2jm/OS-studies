#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  int ret = fork();
  pid_t ppid, pid;

  if (ret > 0) {
    // Retorno do fork = pid do filho
    printf("processo pai retorno fork = %d\n", ret);

    // Retorna seu próprio pid 
    pid = getpid();
    printf("processo pai retorno getpid = %d\n", pid);

    /* Se não usarmos esta função, este processo pode terminar antes do processo
    filho e o retorno de getppid() não será o pid deste processo */
    wait(NULL);
  }

  if (ret == 0) {
    // Retorna zero por ser o processo filho
    printf("processo filho retorno fork = %d\n", ret);

    // Retorna seu próprio pid
    pid = getpid();
    printf("processo filho retorno getpid = %d\n", pid);

    // Retorna o pid do processo pai
    ppid = getppid();
    printf("processo filho retorno getppid = %d\n", ppid);
  }

  if (ret < 0) {
    perror("Falha no fork!\n");
  }

  return 0;
}
