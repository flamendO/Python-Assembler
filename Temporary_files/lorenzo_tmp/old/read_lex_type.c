

#include <pyas/lexem_type.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>


int main(int argc, char *argv[] ){
    char * file = argv[1];
    lexem_type_t * c = malloc(sizeof(lexem_type_t) * 100) ;
    c = lex_read(file);
    free(c);
    return 0 ;
}