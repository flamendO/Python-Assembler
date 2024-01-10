// #include <assert.h>
// #include <stdio.h>
// #include <stdlib.h>
#include <pyas/list.h>

#ifndef _COUPLE_TYPE_LEX_H_
#define _COUPLE_TYPE_LEX__H

//sous l'hypothèse que le nom du type ne contienne pas
    //plus de 100 caractères
typedef struct{
    char* type;
    char* lexem_in_code;
    int ligne;
    int colonne;
}*couple_type_lex_t;

list_t lex(char* regexp_file, char* source_file);
#endif