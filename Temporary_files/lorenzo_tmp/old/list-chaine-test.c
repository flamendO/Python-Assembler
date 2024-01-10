#include <pyas/all.h>
#include <unitest/unitest.h>

#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <pyas/list.h>


int main ( int argc, char *argv[] ) {
    
    list_t list_1 = "0x[0-9]" ;
    list_1 = list_regexp(list_1) ;

    unit_test( argc, argv ); 
    test_suite( "Basic features" );

    // La liste n'est pas vide :
    test_assert(list_1 != NULL, "La liste n'est pas vide") ;

    // La liste est dans le bon ordre :
    //test_oracle() ;


    // 

}