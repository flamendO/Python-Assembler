#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unitest/unitest.h>
#include "pyas/list.h"
#include "pyas/queue.h"
#include <assert.h>
#include "pyas/regexp.h"

static void basic_re(void){
    test_suite("No special character : 'abcde\\+'") ;
    fifo * q = fifo_new() ;
    q = char_to_queue("abcde\\+") ;
    char_group * t = fifo_first(q) ;
    char_group * t2 = fifo_last(q) ;
    test_assert(fifo_length(q) == 6, "the length of the char is the length of the queue") ;
    test_assert(t ->characters['a'] == 1, "first element of the fifo is the first one of the char") ;
    test_assert(t2 ->characters['+'] == 1, "last") ;
}

static void with_brackets(void){
  test_suite("With bracket and a group of characters : '[a-z][AZERT]'") ;
  fifo * q = fifo_new() ;
  q = char_to_queue("[a-z][AZERT]") ;
  char_group * t = fifo_first(q) ;
  char_group * t2 = fifo_last(q) ;
  for(int i = 'a'; i < 'z' + 1; i++){
    test_assert(t ->characters[i] == 1, "charachter %c is inside the group", i) ;
  }
  test_assert(t2 ->characters['R'] == 1, "single characters too") ;
  test_assert(t2 ->characters['b']== 0, "characters not in the char are not in the queue") ;
}

static void with_operator(void){
  test_suite("With + and ? and * operator") ;
  fifo * q = fifo_new() ;
  q = char_to_queue("a+b?c*") ;
  char_group * t = fifo_first(q) ;
  char_group * t2 = fifo_last(q) ;
  test_assert(t->characters['a'] == 1, "the first expected characters is correct") ;
  test_assert(t->characters['c']== 0, "Only the expected character") ;
  test_assert(t->op == ONE_OR_MORE, "+ : one or more is valid");
  test_assert(t2 ->characters['c']== 1, "the last expected characters is correct") ;
  test_assert(t2->op == ZERO_OR_MORE, "* : zero or more is valid");
}

static void with_negation_and_all_characters(void){
  test_suite("With ^ and . operators") ;
  fifo * q = fifo_new() ;
  q = char_to_queue("^a.") ;
  char_group * t = fifo_first(q) ;
  char_group * t2 = fifo_last(q) ;
  test_assert(t->complement == 1, "^ : negation is valid");
  test_assert(t->characters['a'] == 1, "negative character is inside the group");

  test_assert(t2 ->characters['c']== 1, "any characters is in the group") ;
  test_assert(t2 ->complement== 0, "the negataion is only on the first character") ;
  test_assert(t2 ->op == ONE_TIME, "No opertaor leads to one time only") ;
}
/*
static void re_read_test(void){
  test_suite("Re_read basic expression");
  test_oracle(re_read("abcde"), "One in 'a', one time.One in 'b', one time.One in 'c', one time.One in 'd', one time.One in 'e', one time.", NULL, "Reading of abcde valid");
}

*/

int main(int argc, char *argv[]) {
  unit_test(argc, argv);
  basic_re();
  with_brackets() ;
  with_operator() ;
  with_negation_and_all_characters() ;
  //re_read_test();
  return 0;
}