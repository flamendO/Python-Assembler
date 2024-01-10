#include <assert.h>
#include <stdio.h>
#include <stdlib.h> 
#include <string.h>

#include <pyas/queue.h>
#include <pyas/list.h>
#include <pyas/regexp.h>
#include <pyas/lexem.h>


int main() {
    list_t lexems = list_new();
    

    lexem_t lexem8 = lexem_new("newline", "   ", 10, 1);
    lexems = list_add_first(lexems, lexem8);

    lexem_t lexem7 = lexem_new("string", "test", 2, 9);
    lexems = list_add_first(lexems, lexem7);

    lexem_t lexem6 = lexem_new("newline", "\n", 2, 8);
    lexems = list_add_first(lexems, lexem6);

    lexem_t lexem5 = lexem_new("string", "bla", 1, 8);
    lexems = list_add_first(lexems, lexem5);

    lexem_t lexem2 = lexem_new("blank", "abc", 1, 5);
    lexems = list_add_first(lexems, lexem2);

    lexem_t lexem4 = lexem_new("newline", "\n", 6, 1);
    lexems = list_add_first(lexems, lexem4);


    lexem_t lexem1 = lexem_new("blank", " ", 1, 1);
    lexems = list_add_first(lexems, lexem1);

    lexem_t lexem3 = lexem_new("dir::interned", ".interned", 5, 1);
    lexems = list_add_first(lexems, lexem3);

    assert(lexems != NULL);

    pyobj_t obj = (pyobj_t)malloc(sizeof(pyobj_t)); 
    obj->py.codeblock = malloc(sizeof(py_codeblock));
    assert(obj != NULL);

    list_print(lexems, lexem_print);
    

    int result = parse_interned_strings(&lexems, obj);
    printf("%s",obj->py.codeblock->binary.content.interned->py.list.value[1]->py.string.buffer);
    printf("Le résultat est : %d", result);
    printf("\n");



    /*int verification1 = next_lexem_is(&lexems, "blank");
    printf("\n------------------\n");
    printf("Le type du premier élément est bien un blank ? %d", verification1);
    printf("\n------------------\n");


    lexem_t next = lexem_peek(&lexems);
    printf("\nLe prochain lexeme utile est : ");
    lexem_print(next);
    printf("\n");

    list_print(lexems, lexem_print);

    printf("\n");

    int verification2 = next_lexem_is(&lexems, "newline");
    printf("\n------------------\n");
    printf("Le type du premier élément est bien un newline ? %d", verification2);
    printf("\n------------------\n");

    


    lexem_t next2 = lexem_peek(&lexems);
    printf("\nLe prochain lexeme utile est : ");
    lexem_print(next2);
    printf("\n");

    list_print(lexems, lexem_print);

    printf("\n");


    lexem_t next3 = lexem_peek(&lexems);
    printf("\nLe prochain lexeme utile est : ");
    lexem_print(next3);
    printf("\n");

    list_print(lexems, lexem_print);

    printf("\n");


    lexem_peek(&lexems);
    printf("\nLe prochain lexeme utile est : ");
    printf("\n");

    list_print(lexems, lexem_print);

    //int work = parse_eol(&lexems);
    //printf("L'expression est : %d\n", work);


    printf("\n");
    int result = next_lexem_is(&lexems, "operation");
    printf("Le prochain lexeme est bien de la bonne operation ? %d \n", result);

    printf("---------------------------\n");

    //lexem_advance(&lexems);
    lexem_t next2 = lexem_peek(&lexems);
    lexem_print(next2);

    printf("Maintenant, apres lexem_advance, la liste de lexeme devient : ");
    list_print(lexems, lexem_print);
    printf("\n");

    print_parse_error("Erreur Synthaxe", &lexems);

    
    list_delete(lexems, (action_t)lexem_delete);*/


    return 0;
}