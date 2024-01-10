//
//  list.h
//  Listes_chainees_dynamiques
//
//  Created by Lorenzo Azerine on 11/08/2023.
//

#ifndef list_h
#define list_h

#include <stdio.h>

typedef struct link_t *list_t;

  list_t list_new( void );
  int    list_empty( list_t l );
  char  list_first( list_t l );
  list_t list_next( list_t l );
  list_t list_add_first( list_t l, char *object );
  //list_t list_del_first( list_t l, action_t delete );
  size_t list_length( list_t l );
  //int    list_print( list_t l, action_t print );
  //void   list_delete( list_t l, action_t delete );
void list_print( list_t l ) ;
list_t list_regexp(char regexp[]) ;
#endif
/* list_h */
