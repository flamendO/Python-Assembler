
/**
 * @file test-list.c
 * @author François Cayre <francois.cayre@grenoble-inp.fr>
 * @date Fri Jul  2 17:58:47 2021
 * @brief Driver for list of lexems.
 *
 * Tests unitaires pour les "listes de lexems"
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "pyas/queue.h" // Inclure d'abord queue.h
#include "pyas/list.h"  // Puis list.h
#include <unitest/unitest.h>

static void list_core( void ) { 

  test_assert( list_empty( list_new() ),
	       "A new list is empty" ); 
  test_assert( 0 == list_length( list_new() ),
	       "An empty list has zero elements" ); 

  test_abort( list_first( list_new() ),
	      "An empty list has no first element" ); 
  test_abort( list_del_first( list_new(), NULL ),
	      "So trying to delete it will fail" ); 
  test_abort( list_next( list_new() ),
	      "An empty list has no next element" ); 

  test_oracle( list_print( list_new(), NULL ), "()", NULL, 
	       "An empty list is printed as ()" ); 
}

static void *int_new( int v ) { 
  int *p = calloc( 1, sizeof( *p ) ); 
  assert( p ); 
  *p = v; 
  return p; 
}

static int int_delete( void *p ) { 
  free( p ); 
  return 0; 
}

static int int_print( void *p ) { 
  return printf( "%d", *(int*)p ); 
}

static void list_construct( void ) { 
  int array[ 4 ] = { 1, 2, 3, 4 }; 
  int i; 

  list_t l = list_new(); 


  for ( i = 0 ; i < 4 ; i++ ) { 
    l = list_add_first( l, int_new( array[ i ] ) ); 
    test_assert( (size_t)(i+1) == list_length( l ),
		 "Can construct a list of %d element%s", i+1, (i+1)>1 ? "s" : "" ); 
    test_assert( array[ i ] == *(int*)list_first( l ),
		 "Insertion order is OK" ); 
  }

  test_assert( !list_empty( l ),
	       "A constructed list is not empty" );
  test_oracle( list_print( l, int_print ), "( 4 3 2 1 )", NULL, 
	       "Can print a non-empty list" ); 

  for ( i = 0 ; i < 4 ; i++ ) { 
    l = list_del_first( l, int_delete ); 
    test_assert( (size_t)(4-i-1) == list_length( l ),
		 "Can remove from a list of %d element%s", 4-i, (4-i)>1 ? "s" : "" ); 
  }

  test_assert( list_empty( l ),
	       "List is empty after removal of all elements" ); 
  
  return; 
}

int main ( int argc, char *argv[] ) { 

  unit_test( argc, argv );

  test_suite( "Empty list core properties" );

  list_core( );

  test_suite( "Constructing and deleting lists" ); 

  list_construct( ); 

  exit( EXIT_SUCCESS );
}
