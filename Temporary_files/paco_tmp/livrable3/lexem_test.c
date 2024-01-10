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


int main(void) {
    /*list_t lexems = list_new();
    

    lexem_t lexem8 = lexem_new("newline", "\n", 10, 1);
    lexems = list_add_first(lexems, lexem8);

    lexem_t lexem7 = lexem_new("float", "2.5", 2, 9);
    lexems = list_add_first(lexems, lexem7);

    lexem_t lexem6 = lexem_new("newline", "\n", 2, 8);
    lexems = list_add_first(lexems, lexem6);

    lexem_t lexem5 = lexem_new("string", "lolilop", 1, 8);
    lexems = list_add_first(lexems, lexem5);

    lexem_t lexem2 = lexem_new("newline", "\n", 1, 5);
    lexems = list_add_first(lexems, lexem2);

    lexem_t lexem4 = lexem_new("integer", "6", 6, 1);
    lexems = list_add_first(lexems, lexem4);


    lexem_t lexem1 = lexem_new("newline", " ", 1, 1);
    lexems = list_add_first(lexems, lexem1);

    lexem_t lexem3 = lexem_new("dir::consts", "[", 5, 1);
    lexems = list_add_first(lexems, lexem3);*/

    //assert(lexems != NULL);

    /*pyobj_t obj = (pyobj_t)malloc(sizeof(pyobj_t)); 
    obj->py.codeblock = malloc(sizeof(py_codeblock));
    assert(obj != NULL);

    list_print(lexems, lexem_print);
    

    int result = parse_constants(&lexems, obj);
    printf("La première constante est %s\n", obj->py.codeblock->binary.content.consts->py.list.value[1]->py.string.buffer);
    //printf("%s",obj->py.codeblock->binary.content.interned->py.list.value[1]->py.string.buffer);
    printf("Le résultat est : %d", result);
    printf("\n");
    */

    list_t list_lexem = list_new();
    list_lexem = lex("/home/fremist/Bureau/Projets/C/abdoulwi_azerinel_lardynup_mbayeab/tests/the.conf", "/home/fremist/Bureau/Projets/C/abdoulwi_azerinel_lardynup_mbayeab/tests/python_test_folder/pys_folder/6.pys");
    list_print(list_lexem, lexem_print);

    
    //list_delete(list_lexem, (action_t)lexem_delete);


    return 0;
}