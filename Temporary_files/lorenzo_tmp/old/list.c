
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

list_t list_regexp(char regexp[]){ //Fonction qui transforme une chaine de caractère d'expression régulière en liste chainée de groupe de caractères
    unsigned long n = strlen(regexp) ;
    list_t list_regexp = list_new() ;
    char * p_regexp = regexp ;
    char * regexp2 = NULL ;
    for (int i = 0; i < n; i++){ //comme on ne peut ajouter un élement qu'au début de la liste on parcours la cdc de droite à gauche
        if(*(p_regexp + i ) == '['){ // si on detecte un crochet on compte combien d'elements sont a l'interieur pour les regrouper en une seule cdc
            int count = 2 ;
            int k = i + 1 ;
            while(*(p_regexp + k ) != ']'){
                count += 1 ;
                k += 1 ;
            }
            i = k ;
            regexp2 = malloc(count) ;
            for(int j = 0; j < count; j++){
                *(regexp2 + j) = *(p_regexp + k) ;
                k += -1 ;
            }

        }
         }
         // Pour associer \ avec les caractères spéciaux mais en attente du type final de liste
        if (*(p_regexp + i) == "\\" ){ // On regarde si il y à un anti slash pour récuperer le caractère associé
            regexp2 = malloc(1) ;
            *(regexp2) = *(p_regexp + i + 1) ;
            }
        else{
            regexp2 = malloc(1) ;
            *(regexp2) = *(p_regexp + i) ;
        
        list_regexp = list_add_first(list_regexp, regexp2) ;
        free(regexp2) ;
    }
    return list_regexp ;
}