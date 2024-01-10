/**
 * @file test-examples-pass.c
 * @author François Cayre <cayre@uvolante.org>
 * @date Fri Jul 14 17:32:07 2023
 * @brief Basic test examples. 
 *
 * Basic test examples.
 */

#include <pyas/all.h>
#include <unitest/unitest.h>

#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

static int sum( int *array, int n ) { 
  int i, ret = 0; 

  assert( NULL != array ); 
  assert( n >= 0 ); 

  fprintf( stderr, "Simulating an error message" ); 
  
  for ( i = 0 ; i < n ; i++ ) { 
    ret += array[ i ]; 
  }
  return ret; 
}

static int use_sum( int *array, int n ) {
  int ret = sum( array, n ); 

  printf( "The sum is: %d\n", ret );

  return ret; 
}

int f ( int v ) { 
  printf( "Computing f(%d) -> %d\n", v, v+1 ); 

  return v+1; 
}

int main ( int argc, char *argv[] ) { 

  int array[ 4 ] = { 1, 2, 3, 4 }; 
  int  a = 10, b = 4; 
  
  /* All your test programs must start with: */
  unit_test( argc, argv ); 


  test_suite( "Basic features" );

  /* Suppose you want to check something is true: */
  test_assert( 6  == sum( array, 3 ),
	       "Positive test that passes" );

  /* Suppose you want to check something is false: */
  test_assert( 4 != sum( array, 2 ),
	       "Negative test that passes" );

  test_abort( sum( NULL, 3 ),
	      "Can check for abort()'s" );

  /* Sometimes, you want to check something that you print: */
  test_oracle( use_sum( array, 4 ), "The sum is: 10\n", NULL, 
	       "An inline oracle that passes" );

  test_oracle( use_sum( array, 4 ), "The sum is: 10", "Simulating an error message\n\n", 
	       "Trailing \\n's ignored in oracles and outputs" );


  test_suite( "Advanced features" ); 

  test_assert( a == sum( array, b ),
	       "Comment strings are interpreted, like a=%d", a );

  /* Oracle files are search in `oracle_dir` that may be set with 
     `--test-oracles=oracle_dir`. By default, `oracle_dir` is `"."` (the 
     current working directory), so the following test is equivalent to: 

     ```C
     test_oracle( a == use_sum( array, b ), "test.orc", "test.orc.err", 
                  "Oracles can be stored on disk, check test-data/test.orc.*std*" ); 
     ```
     Executed with: 
     ```bash
     $ ./bin/unit/test-examples-pass --test-oracles=test-data
     ```
   */
  test_oracle( a == use_sum( array, b ), "test-data/test.orc", "test-data/test.orc.err", 
	       "Oracles can be stored on disk, check test-data/test.orc.*std*" ); 
  
  test_oracle( 3 == f( 2 ), orc_out( "Computing f(%d) -> %d", 2, f( 2 ) ), NULL, 
	       "Use orc_{out,err}() for inline oracle parameters" ); 

  test_oracle( 3 == f( 2 ), orc_out( "test-data/test.parms.orc", 2, f( 2 ) ), orc_err( "" ), 
	       "Can find oracle parameters in files, too" ); 

  exit( EXIT_SUCCESS );
}

