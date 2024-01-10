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

int main(){
    //list_t l = lex_read("tests/the.conf");
    // // list_print(l,lexem_type_print);
    list_t les_lexems=lex("tests/the.conf","tests/python_test_folder/pys_folder/4.pys");
    list_print(les_lexems,lexem_print);
    // list_delete(les_lexems,lexem_delete);
    return 0;
}
