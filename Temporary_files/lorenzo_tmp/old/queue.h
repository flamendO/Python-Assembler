/**
 * @file queue.h
 * @author François Cayre <francois.cayre@grenoble-inp.fr>
 * @date Fri Jul  2 19:02:34 2021
 * @brief Queue.
 *
 * Queue.
 */

#ifndef _QUEUE_H_
#define _QUEUE_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <pyas/list.h> 
#include <pyas/chargroup.h>

typedef struct link_t {
  void *content;
  struct link_t *next;
} link_t;

typedef struct {
  link_t *head;
  link_t *tail;
} fifo;

fifo *fifo_new(void);
int fifo_empty(fifo *q);
void fifo_enqueue(fifo *q, void *object);
list_t fifo_to_list(fifo *q);
void fifo_print(fifo *q, void (*print_callback)(void *));
void print_char_callback(void *data);
void print_int_callback(void *data);
void *fifo_dequeue(fifo *q);
int fifo_length(fifo *q);
void *fifo_first(fifo *q);
void *fifo_last(fifo *q);
void fifo_delete(fifo **q);
char_group * read_bracket(int k,  char * p_regexp, int * k_final);
char_group * read_point(char_group * regexp2) ;
operator is_special(int k, char * p_regexp) ;
fifo * char_to_queue(char *regexp) ;

#ifdef __cplusplus
}
#endif

#endif /* _QUEUE_H_ */
