/**
 * @file test-howto.c
 * @author François Cayre <cayre@uvolante.org>
 * @date Sun Aug  7 21:22:53 2022
 * @brief Unit testing howto. 
 *
 * Unit testing howto. 
 */

/* #define NDEBUG // Uncomment this line to skip runtime evaluation of */
// pre/post-conditions and happily ruin your day: your code quality is not
// production-ready yet. 

#include <assert.h>

#include <unitest/unitest.h>

/* We will need to compare integers below. */
static int compare_integers( const void *p1, const void *p2 ) { 
  int i1 = *(int*)p1; 
  int i2 = *(int*)p2; 

  if ( i1 == i2 ) return 0; else return i1 < i2 ? -1 : 1; 
}

/*
  Writing software is an evolving, collaborative, incremental process. 
  
  Testing is the necessary pain for software to actually work in the real 
  world. 

  Software engineering relies on isolating and reusing pieces of code, which 
  are then called modules. Each module comes with its source code (`module.c` / 
  `module.h`) and tests. For example, the module `unitest.c` / `unitest.h` is
  being tested right now with this file you are reading. 

  Designing a set of tests for a module should ensure: 
  1. coverage of errors; 
  2. coverage of expected functionalities; 
  3. quick localization of new bugs and non-regression of the code. 

  Testing is an immense field of knowledge, and we can only give an insight of 
  how things really are made. We start by emphasizing the advantages of contract
  programming. 

  # Contract programming

  ## What it is

  A function operates in a restricted set of socalled pre-conditions, and its 
  result should verify a set of post-conditions. Verifying these 
  pre/post-conditions is called contract programming. 

  *Example* Let `int fun( int *array, int n );` a function that will sort an 
  array of growing integers. The pre-conditions are those required to make the 
  function work: 
  - Fully testable: `n` should be non-negative; 
  - Half-testable: `array` must exist somewhere in memory; 
  - Untestable: `array`'s length should actually be `<= n`. 

  The post-condition is easy too: Simply verify that `array` is actually sorted:
*/

static int array_is_sorted( int *array, int n ) { 
  int i;     

  for ( i = 1 ; n > 1 && i < n ; i++ ) { // Ensure 0 <= i-1 < i < n
    if ( array[ i-1 ] > array[ i ] ) return 0; 
  }  
  return 1; 
}

/*

  ## Why contract programming

  Contract programming is a way to detect errors as soon as they appear. This 
  saves time and effort in the not-so-long run. 

  ## How to do contract programming in C

  An unmet pre/post-condition signals an unrecoverable error and the program 
  must be killed since it cannot continue. 

  In C, the macro `assert( cond );` will test if `cond` is true, and cause an 
  abnormal termination (*abort*) of the program if it is evaluated to false 
  during runtime (prefer conditions without function evaluation to avoid 
  non-deterministic side-effects during function calls). 

  If the symbol `NDEBUG` is defined when `<assert.h>` is last included, then 
  `assert()` produces no code and is deactivated. The cost of `assert()`'s at 
  runtime is negligible and defining `NDEBUG` is one of the worst ideas you 
  could have. 

  The symbol `NDEBUG` may be defined (and pre/post-conditions checking becomes
  disabled) when you create the production version of your code. This is done 
  using the Makefile and therefore `NDEBUG` never actually appears in C code. 

  *Example* The contract-programming skeleton of `fun` above could be something
  like: 
*/
  
// By default, people expect the return value of functions to signal in/correct
// behaviour (unless they are predicates - like `array_is_sorted` -, or 
// comparison functions - like `compare_integers` -, for example). 
// 
// A `NULL` value is generally used to signal that something went wrong when the
// function must return a pointer. Similarly, a negative value (often `-1`) is 
// used when the function has to return an integer.
// 
// Even if your function is not expecting any internal issue or returning 
// additional information about its process, that may be the case of your next
// implementation. 
// 
// Also, functions returning void are non-testable. 
// 
// So we define `fun` as returning an integer, and it will always return zero 
// in production (the universal value for saying "No problem detected"): 

int fun( int *array, int n ) { 
  
  // Pre: C is a language that speaks about the memory of machines. If we have 
  // an invalid address for `array` and `n == 0`, then we should raise an error 
  // and not consider it a case we could easily accomodate (which it is). 
  // Computing is about maths that work, not fiddling with desperate moves.
  // The only invalid address we can detect when writing our C code is `NULL`. 
  // So our first pre-condition may only test for the existence of array (must 
  // be non-`NULL`). 
  // Non-negative array size is another pre-condition. One should be able to 
  // sort an array as soon as it exists in memory and its size is deemed to be 
  // non-negative (people sorting arrays of size 0 or 1 deserve some respect, 
  // too). 
  // It is *not* a good idea to factorize conditions in a single `assert()` 
  // because you want to know exactly which of them failed first. Write 
  // conditions in their order of dependence (here we separately test `array` 
  // and `n`, so our conditions may be written in any order): 
  
  assert( NULL != array ); 
  assert( n >= 0 ); 
  
  
  // Put your sorting logic here!
  // We use `qsort()` for (really) quick illustration purposes: 
  qsort( array, n, sizeof( *array ), compare_integers ); 
  
  
  
#ifndef NDEBUG // Explicitly mark code portions for error checking, this may be 
               // expected to be disabled to compile production code: 
  if ( !array_is_sorted( array, n ) ) return -1; 
#endif         // End of post-conditions checking, we can safely return to the
               // caller: 
  return 0; 

  // It may rightfully seem a little bit contrived to insert an O(n)
  // post-condition in a sorting function. That was useful only to demonstrate
  // the use of `NDEBUG`. In practice, you only test O(1) post-conditions inside
  // the functions (an integer being zero or not, etc.)
  // Here, the call to `is_array_sorted` would be more judiciously placed in the 
  // function `test_prop_sorting_fun` below. 
  // See an example of this in: `test-implementation.c`
}

/*

  ## How to test contract programming in C 

  Testing your code includes:
  - checking that failed pre-conditions will actually raise an unrecoverable 
    error -- we provide the macro `test_abort()` for this. 
  - checking that post-conditions hold with correct inputs -- and we provide 
    the macro `test_assert()` for this. 

  *Example* A set of tests for the pre/post-conditions of `fun` may look like: 
*/

int test_pre_post_sorting_fun() { 
  
  int array[ 4 ] = { 1, 3, 2, 4 }; // Local testing data

  test_abort( !fun( array, -1 ), 
	      "Pre: Array size must be non-negative" ); 
  
  test_abort( !fun( NULL, 3 ), 
	      "Pre: Array must be non-NULL" ); 
  
  
  test_assert( !fun( array, 4 ), 
	       "Post: Sorting finishes on valid inputs" ); 
  
  return 0; 
}

/*
  # Documenting by testing

  Checking pre/post-conditions is key to maximizing the focus on essential
  properties of your code. Obviously, they should be tested too! 

  The comment of a test will make explicit which property of the code is 
  actually verified. Better think of it as a form of documentation that is 
  *automatically* *always* *proven* to be *in sync* with it. 

  That's likely to be our best offer for the programmers of you who dislike 
  writing doc and tests. 

  *Example* We can now group tests for the actual sorting properties we would 
  like to check for `fun`: 
*/

int test_prop_sorting_fun() { 

  int array[ 4 ] = { 1, 3, 2, 4 }; // Local testing data

  test_assert( !fun( array, 4 ), 
	       "Prop: Sorting sorts" ); 
  
  test_assert( !fun( array, 4 ), 
	       "Prop: Sorting is idempotent" ); 
  
  test_assert( !fun( array, 0 ), 
	       "Prop: Array size can be zero" ); 
  
  // Expand with any other property you might want to check: stable sorting, 
  // how it behaves for already-sorted data, etc. 

  return 0; 
}

/*
  The macro `test_suite()` will introduce a new set of tests. 

  Calling mandatory boiler plate code with `unit_test()`, our final testing 
  program will look like: 
*/

int main ( int argc, char *argv[] ) { 

  fprintf( stderr, "\n  Let's start with the whole basic example:\n\n" ); 

  unit_test( argc, argv ); 

  test_suite( "Sorting: pre/post-conditions" ); 
  test_pre_post_sorting_fun(); 

  test_suite( "Sorting: properties" ); 
  test_prop_sorting_fun(); 


  fprintf( stderr, "\n  One more thing...\n" ); 

  INFO( "\nYou may also want to use such printf-like info blocks\n" ); 
  WARNING( "Or even some warning blocks like this one at %s:%d\n", __func__, __LINE__ ); 
  VERBOSE( this.env.verbose > 1,
	   "This block appears from -v=%d onwards\n", 2 ); 
  ERROR( "\nAnd this kind of blocks\nare for error messages!\n\n" ); 

  exit( EXIT_SUCCESS ); /* *EndOfExample* */
}

/*

  # Oracles 

  In various situations, testing what a function will *print* can be the 
  handiest solution. In particular, it implements checking higher-level 
  behaviours or situations of particular interest. 

  An oracle is what the function should print during a test. 

  An oracle may be specified as a string, or as the name of a file containing 
  it -- we provide the macro `test_oracle()` for this. 

  # More test examples

  For basic tests (including using oracles for output checking), see: 
  - `test-examples-pass.c` 
  - `test-examples-fail.c` 

  *Hacker level* To learn how to check different implementations (not only a 
  single function), see: `test-implementation.c` 

  # Debugging while testing

  Debugging is turned on by providing your test executable with option `-g`. 

  This has two effects: 
  1. a debugger is launched on SIGSEGV or unexpected SIGABRT; 
  2. stderr is no longer captured. 

  Consequences: 
  - *always* use option `-g` until your code passes the tests; 
  - *always* print your debugging information with: 

  ```C
  fprintf( stderr, "Why the hell do we have a=%d\n", a ); 
  ```

  # Memory leaks during tests

  Aside from unrecoverable or functional errors, we should ensure that 
  our software will use its memory wisely. That's because we are coding in C. 

  More often than not, tracing and solving memory leaks in C code (having each 
  `malloc()` its corresponding `free()`) leads to cleaner code that is much 
  more easily maintained. 

  `unitest` will print a list of code locations where unfreed blocks were 
  allocated. This list is ranked by the number of unfreed blocks. 

  See: `test-examples-memory.c` 

  This is only intended to provide a quick output on the matter. 

  Use Valgrind.   


  -- fc
*/

