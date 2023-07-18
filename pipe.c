// Simulando | grep
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{
  int fd[2];
  pipe(fd);

  if(!fork()){
    // Fechando ponta de escrita
    close(fd[1]);
    dup2(fd[0], 0);
    close(fd[0]);
    execlp("grep","grep",".c",NULL);
  }
  else{
    // Fechando ponta de leitura
    close(fd[0]);
    dup2(fd[1], 1);
    close(fd[1]);
    execlp("ls", "ls", NULL);
  }
  return 0;
}
