#ifndef _LEXEM_TYPE_H_
#define _LEXEM_TYPE_H_



    typedef struct lexem_type *lexem_type_t;
    lexem_type_t * lex_read(char *filename);
    int lexem_type_print( void *_lex ); 

#endif