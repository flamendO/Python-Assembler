#include <assert.h>
#include <stdio.h>
#include <stdlib.h>


typedef enum {ZERO_OR_ONE, ZERO_OR_MORE, ONE_OR_MORE, ONE_TIME} operator;
/* On utilise un type énuméré avec la constante ZERO_OR_ONE qui équivaut à ?, la
constante ZERO_OR_MORE qui équivaut à * et enfin la constante ONE_OR_MORE qui
équivaut à + */


typedef struct {
     int complement;// vaut 1 si il y'a ^ devant le groupe de caratères et 0 sinon
     operator op;
     int characters[256]; // le groupe de caractères
   } char_group;
