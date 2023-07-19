#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

// To make child end by signal, type something in args
int main(int argc, char *argv[]) {

  pid_t fork_ret = fork();

  if (fork_ret < 0)
    perror("Fork error!\n");

  // child
  if (!fork_ret) {
    printf("[CHILD]: My pid is %d\n", getpid());
    fflush(stdout);
    sleep(5);
    printf("[CHILD]: Bye bye!!\n");
    exit(5);
    // return 1;
  }

  // parent
  if (fork_ret > 0) {
    printf("[PARENT]: My pid is %d\n", getpid());

    if (argc > 1) {
      sleep(2);
      kill(fork_ret, SIGKILL);
    }

    int status;
    pid_t wait_ret = wait(&status);

    if (wait_ret < 0)
      perror("Wait error!\n");

    if (WIFEXITED(status)) {
      printf("[PARENT]: child exit with status = %d\n", WEXITSTATUS(status));
    }

    if (WIFSIGNALED(status)) {
      printf("[PARENT]: Child interrupted by signal %d\n", WTERMSIG(status));
    }
  }

  return 0;
}
