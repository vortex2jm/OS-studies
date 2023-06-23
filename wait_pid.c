#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

int main(int argc, char *argv[]) {

  pid_t fork_ret = fork();

  if (fork_ret < 0)
    perror("Fork error!\n");

  // child
  if (!fork_ret) {
    printf("[CHILD]: My pid is %d\n", getpid());
    fflush(stdout);
    sleep(5);
    exit(0);
  }

  // parent
  if (fork_ret > 0) {

    time_t current_time;
    pid_t wait_ret = 0;

    printf("[PARENT]: My pid is %d\n", getpid());
    fflush(stdout);
    sleep(2);

    while (!wait_ret) {
      wait_ret = waitpid(fork_ret, NULL, WNOHANG);
      if (wait_ret < 0)
        perror("Wait error!\n");

      current_time = time(&current_time);
      printf("Child's still running at %s\n", ctime(&current_time));
      sleep(1);
    }

    puts("Child exited!\n");
  }

  return 0;
}
