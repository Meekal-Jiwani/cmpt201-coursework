#include <stdio.h>
#include <stdlib.h>

struct Node {
  int data;
  struct Node *next;
};

void append(struct Node **plist, int data) {
  // Make new node
  struct Node *newNode = malloc(sizeof(*newNode));
  if (newNode == NULL) {
    perror("Malloc failed.");
    exit(EXIT_FAILURE);
  }

  newNode->data = data;
  newNode->next = NULL;

  // link into list
  if (*plist == NULL) {
    // Make this the first element
    *plist = newNode;
  } else {
    // Find the end
    struct Node *current = *plist;
    while (current->next != NULL) {
      current = current->next;
    }
    current->next = newNode;
  }
}

void printlist(struct Node *list) {
  printf("The list is: ");
  struct Node *current = list;
  while (current != NULL) {
    printf("%d, ", current->data);
    current = current->next;
  }
  printf("\n");
}

void freelist(struct Node **plist) {
  struct Node *current = *plist;
  while (current != NULL) {
    struct Node *next = current->next;
    free(current);
    current = next;
  }
  *plist = NULL;
}

int main() {
  // Welcome!
  printf("C linked list Demo\n");

  // Create a linked list (head)
  struct Node *head = NULL;

  // Insert some data
  append(&head, 10);
  append(&head, 20);
  append(&head, 30);
  append(&head, 40);

  // Print list
  printlist(head);

  // Free memory
  freelist(&head);
}
