#define _DEFAULT_SOURCE

#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define BUFFER_SIZE 100

struct header {
  uint64_t size;
  struct header *next;
};

#define BLOCK_SIZE 128
#define DATA_SIZE (BLOCK_SIZE - sizeof(struct header))

void handle_error(char *err) { perror(err); }

void print_out(char *format, void *data, size_t data_size) {
  char buf[BUFFER_SIZE];
  ssize_t len = snprintf(buf, BUFFER_SIZE, format,
                         data_size == sizeof(uint64_t) ? *(uint64_t *)data : *(void **)data);

  if (len < 0) {
    handle_error("snprintf");
  }

  write(STDOUT_FILENO, buf, len);
}

int main() {
  void *start = sbrk(256);

  if (start == (void *)-1) {
    handle_error("sbrk");
    return 1;
  }

  struct header *first = start;
  struct header *second = start + BLOCK_SIZE;

  first->size = BLOCK_SIZE;
  first->next = NULL;
  second->size = BLOCK_SIZE;
  second->next = first;

  memset(first + 1, 0, DATA_SIZE);
  memset(second + 1, 1, DATA_SIZE);

  print_out("first block:      %p\n", &first, sizeof(first));
  print_out("second block:     %p\n", &second, sizeof(second));
  print_out("first block size: %lu\n", &first->size, sizeof(first->size));
  print_out("first block next: %p\n", &first->next, sizeof(first->next));
  print_out("second block size: %lu\n", &second->size, sizeof(second->size));
  print_out("second block next: %p\n", &second->next, sizeof(second->next));

  char *p = start;
  char c;

  for (int i = 0; i < 256; i++) {
    if (i % BLOCK_SIZE >= sizeof(struct header)) {
      c = '0' + p[i];
      write(STDOUT_FILENO, &c, 1);
      write(STDOUT_FILENO, "\n", 1);
    }
  }

  return 0;
}
