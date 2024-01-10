#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "pyas/queue.h" // Inclure d'abord queue.h
#include "pyas/list.h"  // Puis list.h
#include <unitest/unitest.h>
#include "pyas/lexem_type.h"


static void conf_read_test(void){
    list_t l = list_new();
    l = lex_read("tests/test.conf");
    test_suite("Reading is correct");
    lexem_type_t lex = list_first(l);
    test_assert(strcmp(lex->type, "number :: float ") == 0, "Correct type 1 : number :: float");
    l = list_next(l);
    l = list_next(l);
    lex = list_first(l);
    test_assert(strcmp(lex->value, "[a-zA-Z][a-zA-Z0-9]*") == 0, "Correct value 1 :[a-zA-Z][a-zA-Z0-9]*");
    l = list_next(l);
    lex = list_first(l);
    test_assert(strcmp(lex->type, "keyword :: else ") == 0, "Correct type 2 : keyword :: else");
    test_assert(strcmp(lex->value, "else") == 0, "Correct value 1 :[a-zA-Z][a-zA-Z0-9]*");
}


int main(int argc, char *argv[]) {
    unit_test(argc, argv);
    conf_read_test();
}