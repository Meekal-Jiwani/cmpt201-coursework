#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
  char *line = NULL;
  size_t len = 0;

  while (1) {
    printf("Enter programs to run.\n ");

    ssize_t path = getline(&line, &len, stdin);
    if (path == -1) {
      break;
    }

    line[path - 1] = '\0';

    pid_t pid = fork();
    if (pid == 0) {
      execlp(line, line, (char *)NULL);
      printf("Exec failure\n");

      free(line);
      exit(1);
    }

    if (waitpid(pid, NULL, 0) == -1) {
      break;
    }
  }

  free(line);
  return 0;
}
