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
void print_couple_type_lex(couple_type_lex_t couple){
    char* type;
    char* lexem_in_code;
    int ligne;
    int colonne;

    printf("[%d:%d:%s] %s\n",couple->ligne, couple->colonne,couple->type,couple->lexem_in_code);
}

int main(){
    printf("voyons");
    // list_t l = lex_read("tests/the.conf");
    // list_print(l,lexem_type_print);
    list_t les_lexems=lex("tests/the.conf","tests/python_test_folder/pys_folder/4.pys");
    list_print(les_lexems,print_couple_type_lex);
    return 0;
}