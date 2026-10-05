#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 5

char *read_input() {
  char *buffer = NULL;
  size_t n = 0;

  printf("Enter input: ");

  if (getline(&buffer, &n, stdin) == -1) {
    free(buffer);
    return NULL;
  }

  return buffer;
}

void add_to_history(char *hist[], int *num, char *input) {
  if (*num == SIZE) {
    free(hist[0]);

    for (int i = 0; i < SIZE - 1; i++) {
      hist[i] = hist[i + 1];
    }

    hist[SIZE - 1] = input;
  }

  else {
    hist[*num] = input;
    (*num)++;
  }
}

int main() {
  char *hist[SIZE];
  int num = 0;
  char *input;

  while ((input = read_input()) != NULL) {
    add_to_history(hist, &num, input);

    if (strcmp(input, "print\n") == 0) {

      for (int i = 0; i < num; i++) {
        printf("%s", hist[i]);
      }
    }
  }

  for (int i = 0; i < num; i++) {
    free(hist[i]);
  }

  return 0;
}
