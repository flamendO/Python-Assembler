#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#ifndef _CHARGROUP_H_
#define _CHARGROUP_H_

typedef enum {
    ZERO_OR_ONE,
    ZERO_OR_MORE,
    ONE_OR_MORE,
    ONE_TIME
} operator;
/* On utilise un type enumere avec la constante ZERO_OR_ONE qui equivaut à ?, la
constante ZERO_OR_MORE qui equivaut à * et enfin la constante ONE_OR_MORE qui
equivaut à + */


typedef struct {
     int complement;// vaut 1 si il y'a ^ devant le groupe de caratères et 0 sinon
     operator op;
     int characters[129]; // le groupe de caractères
   } char_group;

char_group* new_char_group();
void copy_char_group(char_group* dest,char_group src);
#endif /* _CHARGROUP_H_ */
