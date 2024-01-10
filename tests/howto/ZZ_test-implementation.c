/**
 * @file test-implementation.c
 * @author François Cayre <cayre@uvolante.org>
 * @date Sun Aug  7 21:22:53 2022
 * @brief Implementation testing howto. 
 *
 * Implementation testing howto. 
 */

#include <assert.h>

#include <unitest/unitest.h>

/*

  # Laziness hacking: Quick prototyping 

  The following is for the lazy hacker in you. If you feel too lazy to become a
  lazy hacker, you can safely skip it. 

  We assume the same running example as in `test-howto.c`. 
*/

/* We will need to compare integers below: */
static int compare_integers( const void *p1, const void *p2 ) { 
  int i1 = *(int*)p1; 
  int i2 = *(int*)p2; 

  if ( i1 == i2 ) return 0; else return i1 < i2 ? -1 : 1; 
}

/* And also to check whether an array of integers is sorted: */
static int array_is_sorted( int *array, int n ) { 
  int i; 
  for ( i = 1 ; n > 1 && i < n ; i++ ) { // Ensure 0 <= i-1 < i < n
    if ( array[ i-1 ] > array[ i ] ) return 0; 
  }
  
  return 1; 
}

/* 
  Now imagine we have two implementations of a sorting function: 
  - `int sorting_fun1( int*, int ); // One that works`
  - `int sorting_fun2( int*, int ); // A tentative, buggy replacement`

  Any code that only relies on checked properties of our sorting function will 
  continue to work just as is if we replaced it by another sorting function that 
  would enforce the same properties. 

  So let's have these functions defined as: 
*/

int sorting_fun1( int *array, int n ) { // One that works

  assert( array ); 
  assert( n >= 0 ); 
  
  qsort( array, sizeof( *array ), n, compare_integers ); 

  return 0; 
}

int sorting_fun2( int *array, int n ) { // A tentative, buggy replacement

  qsort( array, sizeof( *array ), n, compare_integers ); 

  return 0; 
}

/*
  This is key for fast prototyping: 
  1. You first write tests and a simple implementation that passes the tests, 
     and you continue to build the other parts of the project similarly! 
  2. Once the whole project works as planned, progressively improve selected 
     parts by providing an alternate implementation. 

  Then you can use the tests to quickly tell if you have a valid replacement, 
  or how far you are (by concentrating on the failed tests). 

  So you want to be able to check a set of defining properties against any 
  arbitrary piece of code you might write -- so as to validate it as an 
  alternate, checked implementation. 

  This is done with function pointers as parameters like this: 
*/

int test_pre_post_sorting( int(*fun)(int*,int) ) { 
  // Now `fun` is the name of any sorting function
  // Paste here the code of `test_pre_post_sorting_fun()` from `test-howto.c`: 
  
  int array[ 4 ] = { 1, 3, 2, 4 }; // Local testing data

  test_abort( !fun( array, -1 ), 
	      "Pre: Array size must be non-negative" ); 
  
  test_abort( !fun( NULL, 3 ), 
	      "Pre: Array must be non-NULL" ); 
  
  
  test_assert( !fun( array, 4 ), 
	       "Post: Sorting finishes on valid inputs" ); 
  
  return 0; 
}

int test_prop_sorting( int(*fun)(int*,int) ) { 
  // Slightly adapt the code of `test_prop_sorting_fun()` from `test-howto.c`: 

  int array[ 4 ] = { 1, 3, 2, 4 }; // Local testing data

  /* Notice how testing whether the array is actally sorted, is moved at 
     this level for more generality and robustness: 
  */
  fun( array, 4 );   
  test_assert( array_is_sorted( array, 4 ), 
	       "Prop: Sorting sorts" ); 
  
  fun( array, 4 );   
  test_assert( array_is_sorted( array, 4 ), 
	       "Prop: Sorting is idempotent" ); 

  test_assert( !fun( array, 0 ), 
	       "Prop: Array size can be zero" ); 

  // Expand with any other property you might want to check: stable sorting, 
  // how it behaves for already-sorted data, etc. 

  return 0; 
}

void test_sorting( int(*sorting_fun)(int*, int) ) { 
  
  test_suite( "Sorting: pre/post-conditions" ); 
  test_pre_post_sorting( sorting_fun ); 
  
  test_suite( "Sorting: properties" ); 
  test_prop_sorting( sorting_fun ); 
}

/*
  This code will segfault on testing the implementation `sorting_fun2`. 

  Now try this example with option `-g` to attach a debugger after the crash: 

  ```bash
  $ ./bin/unit/test-implementation.exe -v -g
  ```

 */

int main ( int argc, char *argv[] ) {
  
  unit_test( argc, argv ); 
  
  test_suite( "Validating implementation sorting_fun1" ); 
  test_sorting( sorting_fun1 ); 
  
  test_suite( "Validating implementation sorting_fun2" ); 
  test_sorting( sorting_fun2 ); 
  
  exit( EXIT_SUCCESS ); 
}

