

#include <assert.h>
#include <stdio.h>
#include <stdlib.h> 
#include <string.h>

#include <pyas/queue.h>
#include <pyas/list.h>
#include <pyas/regexp.h>
#include <pyas/lexem.h>
#include <pyas/lexem_type.h>
#include <pyas/lexer_code.h>
#include <pyas/pyobj_print.h>


int main(int argc, char *argv[]){

    if (argc != 3){
        printf("Error --> Regular using : ./bin/parser.exe <lexem_conf_file> <pys_file>\n");
        return EXIT_FAILURE;

    }
    list_t lexem_list = list_new();
    lexem_list = lex(argv[1], argv[2]);
    pyobj_t objet = parse(&lexem_list);

    pyobj_print(objet);


    list_free(&lexem_list);


    return EXIT_SUCCESS;
}