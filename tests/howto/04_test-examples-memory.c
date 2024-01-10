/**
 * @file test-examples-memory.c
 * @author François Cayre <cayre@uvolante.org>
 * @date Fri Jul 14 17:32:07 2023
 * @brief Demonstrating memory leaks. 
 *
 * Demonstrating memory leaks. 
 */

#include <unitest/unitest.h>

#define N 42

static int do_random_leaks( void ) { 
  int    i; 

  srand( getpid() ); 
  
  for ( i = 0 ; i < N ; i++ ) { 
    switch ( rand() % 5 ) {

    case 0 : malloc( 1 + rand()%50 );
      break; 

    case 1 : malloc( 1 + rand()%50 );
      break; 
      
    case 2 : malloc( 1 + rand()%50 );
      break; 
      
    case 3 : malloc( 1 + rand()%50 );
      break; 
      
    default : malloc( 1 + rand()%50 );
      break; 
    }    
  }
  
  return 0; 
}

int main ( int argc, char *argv[] ) { 

  /* All your test programs must start with: */
  unit_test( argc, argv ); 


  test_suite( "Run in 'valgrind --leak-check=full' to compare" ); 

  test_assert( !do_random_leaks( ),
	       "Doing %d random leak%s", N, N > 1 ? "s" : "" ); 

  exit( EXIT_SUCCESS );
}

