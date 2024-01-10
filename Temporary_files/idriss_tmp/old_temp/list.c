
/**
 * @file list.c
 * @author François Cayre <francois.cayre@grenoble-inp.fr>
 * @date Fri Jul  2 18:07:23 2021
 * @brief Lists.
 *
 * Lists.
 */

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include <pyas/list.h>

struct link_t { 
  void          *content;
  struct link_t *next; 
}; 

list_t list_new( void ) { 
  return NULL; 
}

int    list_empty( list_t l ) { 
  return list_new() == l;
}

void*  list_first( list_t l ) { 

  assert( !list_empty( l ) );
  
  return l->content; 
}

list_t list_next( list_t l ) { 

  assert( !list_empty( l ) );
  
  return l->next; 
}

list_t list_add_first( list_t l, void* object ) { 
  struct link_t *new = malloc( sizeof( *new ) );

  assert( new ); 

  new->content = object; 
  new->next    = l; 
  
  return new; 
}

list_t list_del_first( list_t l, action_t delete ) { 
  list_t next; 

  assert( !list_empty( l ) ); 

  next = l->next; 

  if ( delete ) delete( l->content ); 

  free( l ); 

  return next; 
}

size_t list_length( list_t l ) { 
  size_t len; 

  for ( len = 0 ; !list_empty( l ) ; l = list_next( l ), len++ ); 

  return len; 
}

int    list_print( list_t l, action_t print ) { 
  int ret = printf( "(%s", list_empty( l ) ? "" : " " ); 

  for ( ; !list_empty( l ) ; l = list_next( l ) ) { 
    ret += print( list_first( l ) ); 
    ret += printf( " " ); 
  }

  ret += printf( ")" ); 

  return ret; 
}

void   list_delete( list_t l, action_t delete ) { 

  for ( ; !list_empty( l ) ; l = list_del_first( l, delete ) ); 
}

list_t lex_def(char *file){ //Lis un fichier et en fait une liste de lexem
    list_t l =list_new();
    FILE *new_file = fopen(file, "r");
    if (new_file == NULL){
        printf("Le fichier est vide :( \n");
        return NULL;
    }
    char files[256];

    while (fgets(files, sizeof(files),new_file)!=NULL){
        if (files[0]=='\n' || files[0] == '#'){
            continue;
        }

    char * lex_type = strtok(files, "\t\n");
    char * lex_val = strtok (NULL, "\t\n");

    lexem_t lex = calloc( 1, sizeof( *lex ) );
    lex->type = strdup(lex_type);
    lex->value = strdup(lex_val);

    l=list_add_first(l, lex );

    }
    fclose(new_file);
    return l;


}

// list_t lex(char *regexp_file, char *source_file){
//     list_t l =list_new();
//     lexem_t lexem = lexem_new(); //Le but est de faire une liste de lexem
//     FILE *regexp = fopen(regexp_file, "r");
//     if (regexp==NULL){
//         //Cas où le fichier est vide
//         re
//     }
    
//     //regexp_file contient les définitions des expressions régulières
//     //source_file contient du code assembleur pyhton 2.7

// }
