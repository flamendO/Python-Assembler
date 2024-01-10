/**
 * @file regexp.c
 * @author François Cayre <francois.cayre@grenoble-inp.fr>
 * @date Fri Jul  28 09:56:03 2022
 * @brief regexp
 *
 * regexp code, as in the project's pdf document
 *
 */

#include <assert.h>
#include <stdio.h>
#include <stdlib.h> 
#include <string.h>

#include <pyas/queue.h>
#include <pyas/list.h>
#include <pyas/regexp.h>
#include <pyas/chargroup.h>


int re_match_one_group(char_group * group,char caractère){
  int i;
  if (group->complement){ //On observe s'il y'a un ^ en début de chaine de caractère
    for (i=0;i<256;i++){
      if (group->characters[i]!=1 && i!=(int)caractère){ //Tout les éléments en excluant les éléments dans le tableau de char du char_group
        printf("(Négation) - Le caractère matchant est %c de code ASCII %d \n",(char)i,i);
        return 1;
      }
    return 0;
    }
  }
  else {
    for (i=0;i<256;i++){
      if (group->characters[i]==1 && i==(int)caractère){ //Tout les éléments présents dans le tableau de char
        printf("Le caractère matchant est %c de code ASCII %d \n",(char)i,i);
        return 1;
    }
    return 0;
}
  }
}

int re_match_zero_or_one_time(list_t regexp, char *source, char **end) {
    char_group *char_regexp;
    char_regexp = regexp->content;
    if (!char_regexp) {
        if (end) {
            *end = source;
        }
        return 0;
    }

    if (re_match_one_group(char_regexp, *source)) {
        if (end) {
            *end = source + 1;
        }
        return 1;
    } else {
        if (end) {
            *end = source;
        }
        return 0;
    }
}

int re_match_zero_or_more(list_t regexp, char *source, char **end) {
    char_group *char_regexp;
    char_regexp = regexp->content;
    if (!char_regexp) {
        if (end) {
            *end = source;
        }
        return 1; 
    }
    char * compare_source=source; //On pose un point de départ
    while (*source && re_match_one_group(char_regexp, *source)) { //tant que source est différent de null et qu'elle matche avec l'expression régulière
        source = source + 1;
    }

    if (end) {
        *end = source;
    }
  return 1;
//Conditions de sorties pour Zero or More ? On return 1 dans tout les cas ?
}




int re_match_one_or_more (list_t regexp, char * source, char ** end){
  char_group * char_regexp;
  char_regexp=regexp->content;
  char * compare_source=source;
  while (re_match_one_group(char_regexp,source)){ //Vérifie si le groupe de la liste chainée correspond avec la source
    source=source+1; //Tant que l'expression régulière matche avec la source, on itère la source
  }
  if (source > compare_source){ // Observe si l'adresse de source est plus grande que celle de compare_source, si c'est le cas, cela veut dire que l'élément est déjà présent au moins une fois
    if (end){
      *end=source;
    }
    return 1;
  }
  else { 
    if (end){
      *end=compare_source;
    }
    return 0;
  }

  if (end){
    *end=source; 
    }
  return (source > compare_source);
//Conditions de sorties pour One or More ? (source > compare_source)?
}



int re_match(list_t regexp, char *source, char **end) {
    if (!source) {
        if (end) {
            *end = source;
        }
        return 0;
    }

    if (!regexp) {
        if (end) {
            *end = source;
        }
        return 1;
    }

    link_t *rgxp = regexp;
    char *new_end=NULL; //On initialise pour éviter des soucis
    char_group * rgxp_group = (char_group *)(rgxp->content);

    if (rgxp_group) { //On s'assure que rgxp n'est pas nulle avant d'émettre des conditions
        if (rgxp_group->op == ONE_TIME || rgxp_group->op == ZERO_OR_ONE) {
            return re_match_zero_or_one_time(rgxp, source, &new_end);
        } else if (rgxp_group->op == ZERO_OR_MORE) {
            return re_match_zero_or_more(rgxp, source, &new_end);
        } else if (rgxp_group->op == ONE_OR_MORE) {
            return re_match_one_or_more(rgxp, source, &new_end);
        } else {
            if (re_match_one_group(rgxp->content, *source)) {
                rgxp = rgxp->next; //itération de la liste une fois les conditions remplises
                source = source + 1;
                return re_match(rgxp, source, end);
            } else {
                if (end) {
                    *end = source;
                }
                return 0;
            }
        }
    } else {
    
        if (end) {
            *end = source;
        }
        return 0;
    }
}

// static int re_match_zero_or_more( char c, char *regexp, char *source , char **end ) { 
//   char *t = source; 

//   while ( '\0' != *t && ( *t == c || '.' == c ) ) t++; 

//   do { 
//     if ( re_match( regexp, t, end ) ) return 1; 
//   } while ( t-- > source ); 

//   if ( end ) *end = source; 
//   return 0;
// }

// int re_match( char *regexp, char *source, char **end ) { 

//   if ( NULL == source ) { 
//     if ( end ) *end = source; 
//     return 0;
//   }

//   if ( NULL == regexp || '\0' == regexp[ 0 ] ) { 
//     if ( end ) *end = source; 
//     return 1; 
//   }
//   if ( '*' == regexp[ 1 ] ) { 
//     return re_match_zero_or_more( regexp[ 0 ], regexp+2, source, end); 
//   }
  
//   if (   '\0' != *source && 
//        ( '.'  == regexp[ 0 ] || *source == regexp[ 0 ] ) ) { 
//     return re_match( regexp+1, source+1, end ); 
//   }

//   if ( end ) *end = source; 
//   return 0; 
// }
