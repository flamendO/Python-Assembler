#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unitest/unitest.h>
#include "pyas/list.h"
#include "pyas/queue.h"
#include <assert.h>

static void queue_core(void) {
  test_suite("empty properties");
  fifo *q = fifo_new();
  test_assert(fifo_empty(q), "A new queue is empty");
  test_assert(0 == fifo_length(q), "An empty queue has zero elements");
  test_abort(NULL == fifo_first(q), "An empty list has no first element");
  fifo_delete(&q);
}

static void queue_build_and_remove(void) {
  test_suite("FIFO and remove properties ");
  fifo *q = fifo_new();
  int c1 = 1;
  int c2 = 2;
  int c3 = 3;
  int c4 = 4;
  int c5 = 5;
  fifo_enqueue(q, (int *)&c1);
  
  fifo_enqueue(q, (int *)&c2);
  
  fifo_enqueue(q, (int *)&c3);
  fifo_enqueue(q, (int *)&c4);
  int array_test[5] = {1, 2, 3, 4, 5};
  
  test_assert(fifo_length(q) == 4, "Can construct a queue of a defined length");
  test_assert(array_test[0] == *(int *)fifo_dequeue(q), "The first element to go out is the first arrived (FIFO)");

  fifo_enqueue(q, (int *)&c5);
  test_assert(array_test[4] == *(int *)fifo_last(q), "If we add an element, it is at the last place in the queue -> Order OK");

  for (int i=0; i<4; i++){
  fifo_dequeue(q);
  }



  test_assert(fifo_empty(q), "A queue can be empty after deleting elements");
  
  fifo_delete(&q);  
  
    test_assert(q == NULL, "The queue has been successfully deleted");
}


static void queue_conversion(void) {
  test_suite("conversion to list properties");
  fifo *q = fifo_new();
  int c1 = 1;
  int c2 = 2;
  int c3 = 3;
  int c4 = 4;
  fifo_enqueue(q, (int *)&c1);
  fifo_enqueue(q, (int *)&c2);
  fifo_enqueue(q, (int *)&c3);
  fifo_enqueue(q, (int *)&c4);

  list_t l = fifo_to_list(q);


  test_assert((int)list_length(l) == (int)fifo_length(q), "Converted list has the same length as the queue");

  test_assert(list_empty(l) == fifo_empty(q), "Converted list is empty if and only if the queue is empty");

  
  
  fifo_delete(&q);
}





int main(int argc, char *argv[]) {
  unit_test(argc, argv);
  queue_core();
  queue_build_and_remove();
  queue_conversion();
  return 0;
}
