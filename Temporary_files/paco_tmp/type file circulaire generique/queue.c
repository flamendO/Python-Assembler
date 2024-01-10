/**
 * @file queue.c
 * @author François Cayre <francois.cayre@grenoble-inp.fr>
 * @date Fri Jul  2 19:02:17 2021
 * @brief Queue.
 *
 * Queue.
 */

#include <assert.h>
#include <stdio.h>
#include <stdlib.h> 

#include <pyas/queue.h>



fifo *fifo_new(void) {
  fifo *q = (fifo *)malloc(sizeof(fifo));
  if (q == NULL) {
    fprintf(stderr, "Erreur d'allocation de mémoire.\n");
    exit(EXIT_FAILURE);
  }

  q->head = NULL;
  q->tail = NULL;
  return q;
}

int fifo_empty(fifo *q) {
  return q->head == NULL;
}

void fifo_enqueue(fifo *q, void *object) {
  link_t *new_link = (link_t *)malloc(sizeof(link_t));
  if (new_link == NULL) {
    fprintf(stderr, "Erreur d'allocation de mémoire.\n");
    exit(EXIT_FAILURE);
  }

  new_link->content = object;
  new_link->next = NULL;

  if (q->tail == NULL) {
    q->head = new_link;
    q->tail = new_link;
  } else {
    q->tail->next = new_link;
    q->tail = new_link;
  }
}

list_t *fifo_to_list(fifo *q) {
  list_t *l = list_new();

  if (fifo_empty(q)) {
    return l;
  }

  link_t *current = q->head;
  while (current != NULL) {
    l = list_add_first(l, current->content);
    current = current->next;
  }

  return l;
}

void fifo_print(fifo *q, void (*print_callback)(void *)) {
  printf("File : ");
  link_t *current = q->head;
  printf("|\t");
  while (current != NULL) {
    print_callback(current->content);
    printf("\t | \t ");
    current = current->next;
  }

  printf("\n");
}

void print_char_callback(void *data) {
  printf("%c", *(char *)data);
}

void print_int_callback(void *data) {
  printf("%d", *(int *)data);
}

void *fifo_dequeue(fifo *q) {
  if (fifo_empty(q)) {
    fprintf(stderr, "La file est vide.\n");
    exit(EXIT_FAILURE);
  }

  link_t *first_link = q->head;
  q->head = first_link->next;

  if (q->head == NULL) {
    q->tail = NULL;
  }

  void *content = first_link->content;
  free(first_link);
  return content;
}

int fifo_length(fifo *q) {
  int length = 0;
  link_t *current = q->head;

  while (current != NULL) {
    length++;
    current = current->next;
  }

  return length;
}

void *fifo_first(fifo *q) {
  if (fifo_empty(q)) {
    return NULL;
  }

  return q->head->content;
}

void *fifo_last(fifo *q) {
  if (fifo_empty(q)) {
    return NULL;
  }

  return q->tail->content;
}

void fifo_delete(fifo **q) {
  link_t *current = (*q)->head;

  while (current != NULL) {
    link_t *temp = current;
    current = current->next;
    free(temp);
  }

  free(*q);
  *q = NULL;
}
