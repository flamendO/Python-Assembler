#include <pyas/queue.h>

#ifndef _LEXEM_TYPE_H_
#define _LEXEM_TYPE_H_


    struct lexem_type { 
        char *type;
        char *value;
        list_t l_value ; 
    };

    typedef struct lexem_type * lexem_type_t;
    //Prends un chemin de fichier de definition de lexems et renvoie une liste de lexem_type
    //return : la liste si pas de probleme, 
    //NULL si fichier vide 
    list_t lex_read(char *filename);
    //Affiche ce que la fonction precedente a lue
    int lexem_type_print( void *_lex ); 

#endif
