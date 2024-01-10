#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pyas/regexp.h>
#include <pyas/lexem.h>
#include <pyas/list.h>
#include <pyas/queue.h>
#include <pyas/lexem_type.h>
#include <pyas/lexer_code.h>

int main(int argc, char *argv[]){
    if (argc < 3) {
        fprintf(stderr, "Usage:\n\t%s regexp text\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    
    list_t les_lexems=lex(argv[1],argv[2]);
    list_print(les_lexems,lexem_print);
    // list_delete(les_lexems,lexem_delete);
    return 0;
}
