
/**
 * @file lexem.c
 * @author François Cayre <francois.cayre@grenoble-inp.fr>
 * @date Fri Jul  2 17:59:27 2021
 * @brief Lexems.
 *
 * Lexems.
 */

#define _POSIX_C_SOURCE 200809L /* strdup(3) */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

#include <pyas/pyobj.h>
#include <pyas/lexem.h>
#include <pyas/list.h>
#include <pyas/queue.h>




lexem_t lexem_new( char *type, char *value, int line, int column ) { 
  lexem_t lex = calloc( 1, sizeof( *lex ) );

  assert( lex );

  if ( type  && *type  ) lex->type  = strdup( type );
  if ( value && *value ) lex->value = strdup( value );

  lex->line   = line;
  lex->column = column; 
  
  return lex; 
}

int     lexem_print( void *_lex ) { 
  lexem_t lex = _lex; 
  if (_lex == NULL){
    return 0;
  }
  return printf( "[%d:%d:%s] %s\n",
		 lex->line,
		 lex->column,
		 lex->type,
		 lex->value );
}

int     lexem_delete( void *_lex ) { 
  lexem_t lex = _lex;
  
  if ( lex ) { 
    free( lex->type );
    free( lex->value );
  }
  
  free( lex );

  return 0; 
}

lexem_t lexem_peek(list_t *lexems) {
  if (list_next(*lexems) == NULL){
    return NULL;
  }

  *lexems = list_next(*lexems);
  list_t next_p = *lexems;
  while (next_p != NULL) {
    assert(next_p->content != NULL);
    lexem_t current_lexem = (lexem_t)next_p->content;
    if (strcmp(current_lexem->type, "blank::skip") == 0 || strcmp(current_lexem->type, "comment::skip") == 0) {
      next_p = next_p -> next;
      *lexems = list_next(*lexems);
  } else {
      break; 
    }
  }
  if (next_p->content != NULL) {
  return (lexem_t)next_p->content;

  } else {
  return NULL;
  }
}



int lexem_type_strict(lexem_t lexem, char * type_t){

  return strcmp(lexem->type, type_t) == 0;

}



int lexem_is( list_t *lexems, char *type_t ){
  

  list_t ptr = *lexems;
  
  
  while (ptr != NULL) {
    assert(ptr->content != NULL);
    

    lexem_t current_lexem = (lexem_t)ptr->content;

    
    if (strcmp(current_lexem->type, "blank::skip") == 0 || strcmp(current_lexem->type, "comment::skip") == 0) {
      ptr = ptr->next;
      
    } else {
      break;  
    }
  }
  
  
  if (ptr != NULL) {

    return lexem_type_strict((lexem_t)ptr->content, type_t);

  } else {
    
    return 0;
  }

}



lexem_t lexem_advance(list_t *lexems) {

  lexem_t temp = NULL ;

  temp = lexem_peek(lexems);

  temp = lexem_peek(lexems);


return temp;

}


void print_parse_error( char *msg, list_t *lexems ){


  lexem_t current_lexem = (lexem_t)(*lexems)->content;
  printf("\n Erreur : [%d:%d] --> %s \n", current_lexem->line, current_lexem->column, msg);
}


/*int next_parse_is(list_t *lexems, int (* parse_callback) (list_t *lexems, pyobj_t obj) ){ // BIZARRE
  if (NULL == lexems){
    return -1;
  }

  list_t p = list_next(*lexems);
  

  return parse_callback(&p), obj;

}
*/
int next_lexem_is(list_t *lexems, char * type_t){
  list_t ptr = *lexems;

  ptr = ptr->next;

  while (ptr != NULL) {
    assert(ptr->content != NULL);
    

    lexem_t current_lexem = (lexem_t)ptr->content;

    
    if (strcmp(current_lexem->type, "blank::skip") == 0 || strcmp(current_lexem->type, "comment::skip") == 0) {
      ptr = ptr->next;
      
    } else {
      break;  
    }
  }
  
  
  if (ptr != NULL) {

    return lexem_type_strict((lexem_t)ptr->content, type_t);

  } else {
    
    return 0;
  }

}





/*CODES FONCTIONS RECURSIVES POUR PARSER*/

/*
Nous retournons -1 si le parsing s'est mal passé et 0 si oui
*/



/* ENSEMBLES DES VALEURS DE TYPES POSSIBLES (correspondance décimal) : 

0 : type pyobj
91 : type list
40 : type tuple
115 : type string
105 : int_32
73 : int_64
102 : float (17 caractères max)
103 : float double
121 : complex
79 : NULL
78 : None
70 : False
84 : True



*/


int parse_pys(list_t *lexems, pyobj_t obj){

  
  printf("Parsing ...\n");
  printf("\n----------------------\n");

  parse_eol(lexems);

  lexem_peek(lexems);


  if (-1 == parse_prologue(lexems, obj)){
    printf("\n");
    printf("------Parsing prologue FAILED !------ \n");
    printf("\n");
    printf("Parsing FAILED !\n");
    printf("\n");
     printf("\n----------------------\n");
    return -1;
  }


  lexem_peek(lexems);

  if (-1 == parse_code(lexems)) {
        printf("\n");
        printf("------Parsing Code FAILED !------ \n");
        printf("\n");
        printf("Parsing FAILED !\n");
        printf("\n");
        printf("\n----------------------\n");
        return -1;
    }

    printf("\n");
    printf("------SUCCESS !------ \n");
    printf("\n");
    printf("VALID PARSING !\n");
    printf("\n");
    printf("\n----------------------\n");
  return 0;
}

int parse_prologue(list_t *lexems, pyobj_t obj){
  

  if (-1 == parse_set_directives(lexems, obj) ){
    return -1;
  }

  lexem_peek(lexems);

  if (-1 == parse_interned_strings(lexems, obj) ){
    return -1;
  }

  lexem_peek(lexems);

  if (-1 == parse_constants(lexems, obj) ){
    return -1;
  }

  lexem_peek(lexems);

  if (-1 == parse_names(lexems, obj) ){
    return -1;
  }

  // [<varnames>]
  if (0 == parse_varnames(lexems, obj)) {
      lexem_peek(lexems);
  }

  // [<freevars> <cellvars>]
  if (0 == parse_freevars(lexems, obj)) {
      lexem_peek(lexems);
      if (-1 == parse_cellvars(lexems, obj)) {
          return -1;
      }
  }

return 0;
}


int parse_set_directives(list_t *lexems, pyobj_t obj) {


    if (-1 == parse_set_version_pyvm(lexems, obj)) {
        return -1;
    }

    lexem_peek(lexems);

    if (-1 == parse_set_flags(lexems, obj)) {
        return -1;
    }

    lexem_peek(lexems);

    if (-1 == parse_set_filename(lexems, obj)) {
        return -1;
    }

    lexem_peek(lexems);

    if (-1 == parse_set_name(lexems, obj)) {
        return -1;
    }

    lexem_peek(lexems);

    if (0 == parse_set_source_size(lexems, obj)) { // [<set-source-size>]
        lexem_peek(lexems);
    }

    if (-1 == parse_set_stack_size(lexems, obj)) {
        return -1;
    }

    lexem_peek(lexems);

    if (-1 == parse_set_arg_count(lexems, obj)) {
        return -1;
    }

    lexem_peek(lexems);

  /* LES FONCTIONS SUIVANTES UTILISENT PYTHON 3.x */

    if (0 == parse_set_kwonly_arg_count(lexems, obj)) { // [set-kwonly-arg-count]
        lexem_peek(lexems);
    }

    if (0 == parse_set_posonly_arg_count(lexems, obj)) { // [set-posonly-arg-count]
        lexem_peek(lexems);
    }

    return 0;
}

int parse_set_version_pyvm(list_t *lexems, pyobj_t obj){

  if (0 == lexem_is(lexems, "dir::set") ){ //Si ce n'est pas dir::set
    print_parse_error("Erreur set version pyvm : dir::set error", lexems);
    return -1;    
  }

  lexem_peek(lexems);

  if (0 == lexem_is(lexems, "blank") ){ //Si ce n'est pas blank
    print_parse_error("Erreur set version pyvm : blank error", lexems);
    return -1;    
  }

  lexem_peek(lexems);

  if (0 == lexem_is(lexems, "version_pyvm") ){ //Si ce n'est pas version_pyvm
    return -1;    
    print_parse_error("Erreur set version pyvm : version_pyvm error", lexems);
  }

  list_t p = *lexems;
  lexem_t current_lexem = (lexem_t)p->content;
  obj->py.codeblock->version_pyvm = atoi(current_lexem->value);


  lexem_peek(lexems);

  if (0 == lexem_is(lexems, "blank") ){ //Si ce n'est pas blank
    print_parse_error("Erreur set version pyvm : blank error", lexems);
    return -1;    
  }

  lexem_peek(lexems);

  if (0 == lexem_is(lexems, "integer::dec") ){ //Si ce n'est pas dir::set
    print_parse_error("Erreur set version pyvm : integer::dec error", lexems);
    return -1;    
  }

  lexem_peek(lexems);

  if (-1 == parse_eol( lexems )){
    return -1;
  }

  return 0;

}

int parse_set_flags(list_t *lexems, pyobj_t obj){

  if (0 == lexem_is(lexems, "dir::set") ){ 
    print_parse_error("Erreur set flags : dir::set error", lexems);
    return -1;    
  }

  lexem_peek(lexems);


  if (0 == lexem_is(lexems, "blank") ){ 
    print_parse_error("Erreur set flags : blank error", lexems);
    return -1;    
  }

  lexem_peek(lexems);

  if (0 == lexem_is(lexems, "flags") ){ 
    print_parse_error("Erreur set flags : flags error", lexems);
    return -1;    
  }
   

  
  lexem_peek(lexems);

  if (0 == lexem_is(lexems, "blank") ){ 
    print_parse_error("Erreur set flags : blank error", lexems);
    return -1;    
  }

  lexem_peek(lexems);

  if (0 == lexem_is(lexems, "integer::hex") ){ 
    print_parse_error("Erreur set flags : integer::hex error", lexems);
    return -1;    
  }

  list_t p = *lexems;
  lexem_t current_lexem = (lexem_t)p->content;
  *(current_lexem->value) = '0'; // adresse de la forme ax1651541 on met a et x à 0.
  *(current_lexem->value + 1) = '0';
  obj->py.codeblock->header.flags = atoi(current_lexem->value);

  lexem_peek(lexems);

  if (-1 == parse_eol( lexems )){
    return -1;
  }

  return 0;
}

int parse_set_filename(list_t *lexems, pyobj_t obj){

  if (0 == lexem_is(lexems, "dir::set") ){ 
    print_parse_error("Erreur set filename : dir::set error", lexems);
    return -1;    
  }

  lexem_peek(lexems);

  if (0 == lexem_is(lexems, "blank") ){ 
    print_parse_error("Erreur set filename : blank error", lexems);
    return -1;    
  }

  lexem_peek(lexems);

  if (0 == lexem_is(lexems, "filename") ){ 
    print_parse_error("Erreur set filename : filename error", lexems);
    return -1;    
  }

  lexem_peek(lexems);

  if (0 == lexem_is(lexems, "blank") ){ 
    print_parse_error("Erreur set filename : blank error", lexems);
    return -1;    
  }

  lexem_peek(lexems);

  if (0 == lexem_is(lexems, "string") ){ 
    print_parse_error("Erreur set filename : string error", lexems);
    return -1;    
  }

  list_t p = *lexems;
  lexem_t current_lexem = (lexem_t)p->content;
  unsigned int n = strlen(current_lexem->value);
  
  pyobj_t file_name = malloc(sizeof(pyobj_t));
  char * rBuffer = malloc(sizeof(char)*n);
  assert(NULL != file_name);
  assert(rBuffer != NULL);

  file_name->py.string.buffer = rBuffer;
  obj->py.codeblock->binary.trailer.filename->type = 115;
  strncpy(file_name->py.string.buffer, current_lexem->value, n);
  file_name->py.string.length = n;
  file_name->type = 115; // Valeur décimale correspondante au string
  obj->py.codeblock->binary.trailer.filename = file_name;

  lexem_peek(lexems);

  if (-1 == parse_eol( lexems )){
    return -1;
  }

  return 0;

}



int parse_set_name(list_t *lexems, pyobj_t obj){

  if (0 == lexem_is(lexems, "dir::set") ){ 
    print_parse_error("Erreur set name : dir::set error", lexems);
    return -1;    
  }

  lexem_peek(lexems);

  if (0 == lexem_is(lexems, "blank") ){ 
    print_parse_error("Erreur set name : blank error", lexems);
    return -1;    
  }

  lexem_peek(lexems);

  if (0 == lexem_is(lexems, "name") ){ 
    print_parse_error("Erreur set name : name error", lexems);
    return -1;    
  }


  lexem_peek(lexems);

  if (0 == lexem_is(lexems, "blank") ){ 
    print_parse_error("Erreur set name : blank error", lexems);
    return -1;    
  }

  lexem_peek(lexems);

  if (0 == lexem_is(lexems, "string") ){ 
    print_parse_error("Erreur set name : string error", lexems);
    return -1;    
  }
  
  list_t p = *lexems;
  lexem_t current_lexem = (lexem_t)p->content;
  unsigned int n = strlen(current_lexem->value);
  
  pyobj_t name = (pyobj_t) malloc(sizeof(pyobj_t));
  char * rBuffer = (char *) malloc(sizeof(char)*n);
  printf("%p", rBuffer);
  assert(NULL != name);
  assert(rBuffer != NULL);
  obj->py.codeblock->binary.trailer.name->type = 115;
  name->py.string.buffer = (char *) malloc(sizeof(char)*n);
  strncpy(name->py.string.buffer, current_lexem->value, n);
  name->py.string.length = n;
  name->type = 115; // Valeur décimale correspondante au string
  obj->py.codeblock->binary.trailer.name = name;
  
  lexem_peek(lexems);

  if (-1 == parse_eol( lexems )){
    return -1;
  }

  return 0;

}

int parse_set_source_size(list_t *lexems, pyobj_t obj){

  if (0 == lexem_is(lexems, "dir::set") ){ 
    print_parse_error("Erreur set source-size : dir::set error", lexems);
    return -1;    
  }

  lexem_peek(lexems);

  if (0 == lexem_is(lexems, "blank") ){ 
    print_parse_error("Erreur set source-size : blank error", lexems);
    return -1;    
  }

  lexem_peek(lexems);

  if (0 == lexem_is(lexems, "source_size") ){ 
    print_parse_error("Erreur set source-size : source_size error", lexems);
    return -1;    
  }

  lexem_peek(lexems);

  if (0 == lexem_is(lexems, "blank") ){ 
    print_parse_error("Erreur set source-size : blank error", lexems);
    return -1;    
  }

  lexem_peek(lexems);

  if (0 == lexem_is(lexems, "integer::dec") ){ 
    print_parse_error("Erreur set source-size : integer::dec error", lexems);
    return -1;    
  }

  list_t p = *lexems;
  lexem_t current_lexem = (lexem_t)p->content;
  *(current_lexem->value) = '0'; // adresse de la forme ax1651541 on met a et x à 0.
  *(current_lexem->value + 1) = '0';
  obj->py.codeblock->binary.header.source_size = atoi(current_lexem->value);
  lexem_peek(lexems);

  if (-1 == parse_eol( lexems )){
    return -1;
  }

  return 0;

}

int parse_set_stack_size(list_t *lexems, pyobj_t obj){

  if (0 == lexem_is(lexems, "dir::set") ){ 
    print_parse_error("Erreur set stack-size : dir::set error", lexems);
    return -1;    
  }

  lexem_peek(lexems);

  if (0 == lexem_is(lexems, "blank") ){ 
    print_parse_error("Erreur set stack-size : blank error", lexems);
    return -1;    
  }

  lexem_peek(lexems);

  if (0 == lexem_is(lexems, "stack_size") ){ 
    print_parse_error("Erreur set stack-size : stack_size error", lexems);
    return -1;    
  }

  lexem_peek(lexems);

  if (0 == lexem_is(lexems, "blank") ){ 
    print_parse_error("Erreur set stack-size : blank error", lexems);
    return -1;    
  }

  lexem_peek(lexems);

  if (0 == lexem_is(lexems, "integer::dec") ){ 
    print_parse_error("Erreur set stack-size : integer::dec error", lexems);
    return -1;    
  }

  list_t p = *lexems;
  lexem_t current_lexem = (lexem_t)p->content;
  *(current_lexem->value) = '0'; // adresse de la forme ax1651541 on met a et x à 0.
  *(current_lexem->value + 1) = '0';
  obj->py.codeblock->header.stack_size = atoi(current_lexem->value);

  lexem_peek(lexems);

  if (-1 == parse_eol( lexems )){
    return -1;
  }

  return 0;

}


int parse_set_arg_count(list_t *lexems, pyobj_t obj){

  if (0 == lexem_is(lexems, "dir::set") ){ 
    print_parse_error("Erreur set arg-count : dir::set error", lexems);
    return -1;    
  }

  lexem_peek(lexems);

  if (0 == lexem_is(lexems, "blank") ){ 
    print_parse_error("Erreur set arg-count : blank error", lexems);
    return -1;    
  }

  lexem_peek(lexems);

  if (0 == lexem_is(lexems, "arg_count") ){ 
    print_parse_error("Erreur set arg-count : arg-count error", lexems);
    return -1;    
  }

  lexem_peek(lexems);

  if (0 == lexem_is(lexems, "blank") ){ 
    print_parse_error("Erreur set arg-count : blank error", lexems);
    return -1;    
  }

  lexem_peek(lexems);

  if (0 == lexem_is(lexems, "integer::dec") ){ 
    print_parse_error("Erreur set arg-count : integer::dec error", lexems);
    return -1;    
  }

  list_t p = *lexems;
  lexem_t current_lexem = (lexem_t)p->content;
  *(current_lexem->value) = '0'; // adresse de la forme ax1651541 on met a et x à 0.
  *(current_lexem->value + 1) = '0';
  obj->py.codeblock->header.arg_count = atoi(current_lexem->value);

  lexem_peek(lexems);

  if (-1 == parse_eol( lexems )){
    return -1;
  }

  return 0;


}

/*
QUESTION A DEMANDER : UTILISE-T-ON LES DEUX FONCTIONS SUIVANTES?
*/

int parse_set_kwonly_arg_count(list_t *lexems, pyobj_t obj){

  if (0 == lexem_is(lexems, "dir::set") ){ 
    print_parse_error("Erreur set knonly-arg-count : dir::set error", lexems);
    return -1;    
  }

  lexem_peek(lexems);

  if (0 == lexem_is(lexems, "blank") ){ 
    print_parse_error("Erreur set knonly-arg-count : blank error", lexems);
    return -1;    
  }

  lexem_peek(lexems);

  if (0 == lexem_is(lexems, "kwonly_arg_count") ){ 
    print_parse_error("Erreur set knonly-arg-count : kwonly_arg_count error", lexems);
    return -1;    
  }

  lexem_peek(lexems);

  if (0 == lexem_is(lexems, "blank") ){ 
    print_parse_error("Erreur set knonly-arg-count : blank error", lexems);
    return -1;    
  }

  lexem_peek(lexems);

  if (0 == lexem_is(lexems, "integer::dec") ){ 
    print_parse_error("Erreur set knonly-arg-count : integer::dec error", lexems);
    return -1;    
  }

  lexem_peek(lexems);

  if (-1 == parse_eol( lexems )){
    return -1;
  }

  return 0;

}

int parse_set_posonly_arg_count(list_t *lexems, pyobj_t obj){

  if (0 == lexem_is(lexems, "dir::set") ){ 
    print_parse_error("Erreur set posonly arg-count : dir::set error", lexems);
    return -1;    
  }

  lexem_peek(lexems);

  if (0 == lexem_is(lexems, "blank") ){ 
    print_parse_error("Erreur set posonly arg-count : blank error", lexems);
    return -1;    
  }

  lexem_peek(lexems);

  if (0 == lexem_is(lexems, "posonly_arg_count") ){ 
    print_parse_error("Erreur set posonly arg-count : posonly_arg_count error", lexems);
    return -1;    
  }

  lexem_peek(lexems);

  if (0 == lexem_is(lexems, "blank") ){ 
    print_parse_error("Erreur set posonly arg-count : blank error", lexems);
    return -1;    
  }

  lexem_peek(lexems);

  if (0 == lexem_is(lexems, "integer::dec") ){ 
    print_parse_error("Erreur set posonly arg-count : integer::dec error", lexems);
    return -1;    
  }

  lexem_peek(lexems);

  if (-1 == parse_eol( lexems )){
    return -1;
  }

  return 0;

}

int parse_interned_strings(list_t *lexems, pyobj_t obj){

  if (0 == lexem_is(lexems, "dir::interned") ){ 
    print_parse_error("Erreur set interned-strings : dir::interned error", lexems);
    return -1;    
  }

  lexem_peek(lexems);

  if (-1 == parse_eol( lexems )){
    return -1;
  }

  pyobj_t *p_list = malloc(sizeof(pyobj_t));
  pyobj_t interned = malloc(sizeof(pyobj_t)); 
  assert(interned != NULL);
  assert(p_list != NULL);
  int i = 0;
  list_t p = *lexems;

  if (next_lexem_is(lexems, "string")){
    p = list_next(p);
    obj->py.codeblock->binary.content.interned = interned;
    obj->py.codeblock->binary.content.interned->py.list.value = p_list;
    obj->py.codeblock->binary.content.interned->py.list.size = 0;
    obj->py.codeblock->binary.content.interned->type = 91;
    lexem_t current_lexem = (lexem_t )p->content;
    int n = strlen(current_lexem->value);
    obj->py.codeblock->binary.content.interned->py.list.value[i] = malloc(sizeof(pyobj_t));
    obj->py.codeblock->binary.content.interned->py.list.value[i]->py.string.buffer = malloc(sizeof(char*)*n);
    obj->py.codeblock->binary.content.interned->py.list.value[i]->type = 115;
    strncpy(obj->py.codeblock->binary.content.interned->py.list.value[i]->py.string.buffer , current_lexem->value, n);
    obj->py.codeblock->binary.content.interned->py.list.value[i]->py.string.length = n;
    obj->py.codeblock->binary.content.interned->py.list.size++;
    p = list_next(p);
    p = list_next(p);
  }else{
    free(p_list);
    free(interned);
  }
    

    
    while ( next_lexem_is(lexems, "string") ){

      if (strcmp(((lexem_t)p->content)->type, "string")==0){

        p_list = (pyobj_t *)realloc(p_list, sizeof(p_list)+sizeof(pyobj_t));

        assert(p_list != NULL);

        //obj->py.codeblock->binary.content.interned->py.list.value[i+1] = ;
        //obj->py.codeblock->binary.content.interned->py.list.size++;

        lexem_t current_lexem = (lexem_t)p->content;
        int n_prime = strlen(current_lexem->value);
        obj->py.codeblock->binary.content.interned->py.list.value[i+1] = malloc(sizeof(pyobj_t));
        obj->py.codeblock->binary.content.interned->py.list.value[i+1]->py.string.buffer = malloc(sizeof(char*)*n_prime);
        obj->py.codeblock->binary.content.interned->py.list.value[i+1]->type = 115;
        strncpy(obj->py.codeblock->binary.content.interned->py.list.value[i+1]->py.string.buffer, current_lexem->value, n_prime);
        obj->py.codeblock->binary.content.interned->py.list.value[i+1]->py.string.length = n_prime;
        obj->py.codeblock->binary.content.interned->py.list.size++;
        p = list_next(p);
        //int incr = 1;

      }



      lexem_advance(lexems);
      if (-1 == parse_eol( lexems )){
      return -1;
      }

      i++;

    }
  

  return 0;

}

int parse_constants(list_t *lexems, pyobj_t obj){

  if (0 == lexem_is(lexems, "dir::consts") ){ 
    print_parse_error("Erreur constants : dir::consts error", lexems);
    return -1;    
  }

  lexem_peek(lexems);
  
  if (-1 == parse_eol( lexems )){
    
    return -1;
  }
  

  pyobj_t *p_list = malloc(sizeof(pyobj_t));
  pyobj_t consts = malloc(sizeof(pyobj_t));

  assert(p_list != NULL);
  assert(consts != NULL);

  int i = 0;

  if (next_lexem_is(lexems, "integer") || next_lexem_is(lexems, "float") || next_lexem_is(lexems, "string") || next_lexem_is(lexems, "pycst") || next_lexem_is(lexems, "paren::left")) {

    obj->py.codeblock->binary.content.consts = consts;
    obj->py.codeblock->binary.content.consts->py.list.value = p_list;
    obj->py.codeblock->binary.content.consts->py.list.size = 0;


  }else{
    free(p_list);
    free(consts);
  }



  while ( next_lexem_is(lexems, "integer") || next_lexem_is(lexems, "float") || next_lexem_is(lexems, "string") || next_lexem_is(lexems, "pycst") || next_lexem_is(lexems, "paren::left")){ // A VOIR

      obj->py.codeblock->binary.content.consts->py.list.value = realloc(obj->py.codeblock->binary.content.consts->py.list.value, sizeof(obj->py.codeblock->binary.content.consts->py.list)+sizeof(pyobj_t));
      obj->py.codeblock->binary.content.consts->py.list.value[i] = malloc(sizeof(pyobj_t));
      obj->py.codeblock->binary.content.consts->py.list.size++;
      lexem_peek(lexems);
      if (-1==parse_constant(lexems, obj, i)){

        return -1;
      }

      lexem_peek(lexems);

      if (-1 == parse_eol( lexems )){
        return -1;
      }
      i++;
    }

  return 0;

}


int parse_constant(list_t *lexems, pyobj_t obj, int i){
  list_t p = *lexems;
  lexem_t current_lexem = (lexem_t )p->content;
  if (lexem_is(lexems, "integer") || lexem_is(lexems, "float") || lexem_is(lexems, "string") || lexem_is(lexems, "pycst") || 0 == parse_tuple(lexems, obj, i)){
    
    if (lexem_is(lexems, "integer")){
      
      obj->py.codeblock->binary.content.consts->py.list.value[i]->type = 105;
      obj->py.codeblock->binary.content.consts->py.list.value[i]->py.number.integer = atoi(current_lexem->value);
    }

    else if (lexem_is(lexems, "float")){
      obj->py.codeblock->binary.content.consts->py.list.value[i]->type = 102;
      obj->py.codeblock->binary.content.consts->py.list.value[i]->py.number.real = atof(current_lexem->value);
    }

    else if (lexem_is(lexems, "string")){
      obj->py.codeblock->binary.content.consts->py.list.value[i]->py.string.buffer = malloc(sizeof(char)*strlen(current_lexem->value));
      obj->py.codeblock->binary.content.consts->py.list.value[i]->type = 115;
      assert(obj->py.codeblock->binary.content.consts->py.list.value[i]->py.string.buffer != NULL);
      strncpy(obj->py.codeblock->binary.content.consts->py.list.value[i]->py.string.buffer, current_lexem->value,(int)strlen(current_lexem->value));
      obj->py.codeblock->binary.content.consts->py.list.value[i]->py.string.length = (int) strlen(current_lexem->value);
    }

    else if (lexem_is(lexems, "pycst")){
      obj->py.codeblock->binary.content.consts->py.list.value[i]->py.string.buffer = malloc(sizeof(char)*strlen(current_lexem->value));
      assert(obj->py.codeblock->binary.content.consts->py.list.value[i]->py.string.buffer != NULL);
      strncpy(obj->py.codeblock->binary.content.consts->py.list.value[i]->py.string.buffer, current_lexem->value,(int)strlen(current_lexem->value));
      obj->py.codeblock->binary.content.consts->py.list.value[i]->py.string.length = (int) strlen(current_lexem->value);

      if (strcmp("None", current_lexem->value)==0){
        obj->py.codeblock->binary.content.consts->py.list.value[i]->type = 78;
      }
      else if (strcmp("True", current_lexem->value)==0){
        obj->py.codeblock->binary.content.consts->py.list.value[i]->type = 84;
      }

      else if (strcmp("False", current_lexem->value)==0){
        obj->py.codeblock->binary.content.consts->py.list.value[i]->type = 70;
      }

    }


    return 0;
  }
  print_parse_error("Erreur parse_constant : integer or float or ... error", lexems);
  return -1;

}

int parse_list(list_t *lexems, pyobj_t obj, int i){

  if (0 == lexem_is(lexems, "brack::left") ){
    print_parse_error("Erreur list : brack::left error", lexems);
    return -1;
  }

  if (next_lexem_is(lexems, "blank")){
    lexem_peek(lexems);
  }

  

  /*if (next_lexem_is(lexems, "integer") || next_lexem_is(lexems, "float") || next_lexem_is(lexems, "string") || next_lexem_is(lexems, "pycst") || next_lexem_is(lexems, "paren::left")){
    pyobj_t p_list = malloc(sizeof(pyobj_t));
    pyobj_t *value = malloc(sizeof(pyobj_t)); 
    assert(value != NULL);
    assert(p_list != NULL);
    int i = 0;
    list_t p = *lexems;
    obj->py.list.value = value;
    obj->py.list
  }*/



    while (!next_lexem_is(lexems,"brack::right") && lexems != NULL){

      lexem_peek(lexems);

      if (-1 == parse_constant(lexems,obj,i)){
        print_parse_error("Erreur list : parse_constant error", lexems);
        return -1;
      }

      if (next_lexem_is(lexems, "blank")){
        lexem_peek(lexems);
      }
      i++;
    }

    if (0 == parse_constant(lexems, obj,i)){
      lexem_peek(lexems);
    }

    else if (-1 == parse_constant(lexems, obj,i)){
      print_parse_error("Erreur list : brack::right error", lexems);
      return -1;
    }

    if (lexem_is(lexems, "brack::right")){
      return 0;
    }
    print_parse_error("Erreur list : brack::right error", lexems);
    return -1;





}


int parse_tuple(list_t *lexems, pyobj_t obj, int i){

  if (0 == lexem_is(lexems, "paren::left") ){
    print_parse_error("Erreur tuple : paren::left error", lexems);
    return -1;
  }

  if (next_lexem_is(lexems, "blank")){
    lexem_peek(lexems);
  }


    while (!next_lexem_is(lexems,"paren::right") && lexems != NULL){

      lexem_peek(lexems);

      if (-1 == parse_constant(lexems, obj, i)){
        print_parse_error("Erreur tuple : parse_constant error", lexems);
        return -1;
      }

      if (next_lexem_is(lexems, "blank")){
        lexem_peek(lexems);
      }
      i++;
    }

    if (0 == parse_constant(lexems, obj,i)){
      lexem_peek(lexems);
    }

    else if (-1 == parse_constant(lexems,obj,i)){
      print_parse_error("Erreur tuple : paren::right error", lexems);
      return -1;
    }

    if (lexem_is(lexems, "paren::right")){
      return 0;
    }
    print_parse_error("Erreur tuple : paren::right error", lexems);
    return -1;  

}


int parse_names(list_t *lexems, pyobj_t obj){

  if (0 == lexem_is(lexems, "dir::names")){
    print_parse_error("Erreur names : dir::names error", lexems);
    return -1;
  } 

  lexem_peek(lexems);

  if (-1 == parse_eol( lexems )){
    return -1;
  }

  pyobj_t *p_list = malloc(sizeof(pyobj_t));
  pyobj_t names = malloc(sizeof(pyobj_t)); 
  assert(names != NULL);
  assert(p_list != NULL);
  int i = 0;
  list_t p = *lexems;

  if (next_lexem_is(lexems, "string")){
    p = list_next(p);
    obj->py.codeblock->binary.content.names = names;
    obj->py.codeblock->binary.content.names->py.list.value = p_list;
    obj->py.codeblock->binary.content.names->py.list.size = 0;
    obj->py.codeblock->binary.content.names->type = 91;
    lexem_t current_lexem = (lexem_t )p->content;
    int n = strlen(current_lexem->value);
    obj->py.codeblock->binary.content.names->py.list.value[i] = malloc(sizeof(pyobj_t));
    obj->py.codeblock->binary.content.names->py.list.value[i]->py.string.buffer = malloc(sizeof(char*)*n);
    obj->py.codeblock->binary.content.names->py.list.value[i]->type = 115;
    strncpy(obj->py.codeblock->binary.content.names->py.list.value[i]->py.string.buffer , current_lexem->value, n);
    obj->py.codeblock->binary.content.names->py.list.value[i]->py.string.length = n;
    obj->py.codeblock->binary.content.names->py.list.size++;
    p = list_next(p);
    p = list_next(p);
  }else{
    free(p_list);
    free(names);
  }



  while ( next_lexem_is(lexems, "string") ){
      if (strcmp(((lexem_t)p->content)->type, "string")==0){

        p_list = (pyobj_t *)realloc(p_list, sizeof(p_list)+sizeof(pyobj_t));

        assert(p_list != NULL);

        //obj->py.codeblock->binary.content.interned->py.list.value[i+1] = ;
        //obj->py.codeblock->binary.content.interned->py.list.size++;

        lexem_t current_lexem = (lexem_t)p->content;
        int n_prime = strlen(current_lexem->value);
        obj->py.codeblock->binary.content.names->py.list.value[i+1] = malloc(sizeof(pyobj_t));
        obj->py.codeblock->binary.content.names->py.list.value[i+1]->py.string.buffer = malloc(sizeof(char*)*n_prime);
        obj->py.codeblock->binary.content.names->py.list.value[i+1]->type = 115;
        strncpy(obj->py.codeblock->binary.content.names->py.list.value[i+1]->py.string.buffer, current_lexem->value, n_prime);
        obj->py.codeblock->binary.content.names->py.list.value[i+1]->py.string.length = n_prime;
        obj->py.codeblock->binary.content.names->py.list.size++;
        p = list_next(p);
        //int incr = 1;

      }
      lexem_advance(lexems);
      if (-1 == parse_eol( lexems )){
      return -1;
      }

    }

  return 0;
}


int parse_varnames(list_t *lexems, pyobj_t obj){

  if (0 == lexem_is(lexems, "dir::varnames")){
    print_parse_error("Erreur varnames : dir::varnames error", lexems);
    return -1;
  } 



  lexem_peek(lexems);

  if (-1 == parse_eol( lexems )){
    return -1;
  }

  pyobj_t *p_list = malloc(sizeof(pyobj_t));
  pyobj_t varnames = malloc(sizeof(pyobj_t)); 
  assert(varnames != NULL);
  assert(p_list != NULL);
  int i = 0;
  list_t p = *lexems;

  if (next_lexem_is(lexems, "string")){
    p = list_next(p);
    obj->py.codeblock->binary.content.varnames = varnames;
    obj->py.codeblock->binary.content.varnames->py.list.value = p_list;
    obj->py.codeblock->binary.content.varnames->py.list.size = 0;
    obj->py.codeblock->binary.content.varnames->type = 91;
    lexem_t current_lexem = (lexem_t )p->content;
    int n = strlen(current_lexem->value);
    obj->py.codeblock->binary.content.varnames->py.list.value[i] = malloc(sizeof(pyobj_t));
    obj->py.codeblock->binary.content.varnames->py.list.value[i]->py.string.buffer = malloc(sizeof(char*)*n);
    obj->py.codeblock->binary.content.varnames->py.list.value[i]->type = 115;
    strncpy(obj->py.codeblock->binary.content.varnames->py.list.value[i]->py.string.buffer , current_lexem->value, n);
    obj->py.codeblock->binary.content.varnames->py.list.value[i]->py.string.length = n;
    obj->py.codeblock->binary.content.varnames->py.list.size++;
    p = list_next(p);
    p = list_next(p);
  }else{
    free(p_list);
    free(varnames);
  }

  while ( next_lexem_is(lexems, "string") ){
    if (strcmp(((lexem_t)p->content)->type, "string")==0){

        p_list = (pyobj_t *)realloc(p_list, sizeof(p_list)+sizeof(pyobj_t));

        assert(p_list != NULL);

        //obj->py.codeblock->binary.content.interned->py.list.value[i+1] = ;
        //obj->py.codeblock->binary.content.interned->py.list.size++;

        lexem_t current_lexem = (lexem_t)p->content;
        int n_prime = strlen(current_lexem->value);
        obj->py.codeblock->binary.content.varnames->py.list.value[i+1] = malloc(sizeof(pyobj_t));
        obj->py.codeblock->binary.content.varnames->py.list.value[i+1]->py.string.buffer = malloc(sizeof(char*)*n_prime);
        obj->py.codeblock->binary.content.varnames->py.list.value[i+1]->type = 115;
        strncpy(obj->py.codeblock->binary.content.varnames->py.list.value[i+1]->py.string.buffer, current_lexem->value, n_prime);
        obj->py.codeblock->binary.content.varnames->py.list.value[i+1]->py.string.length = n_prime;
        obj->py.codeblock->binary.content.varnames->py.list.size++;
        p = list_next(p);
        //int incr = 1;

      }
      lexem_advance(lexems);
      if (-1 == parse_eol( lexems )){
      return -1;
      }

    }

  return 0;
}

int parse_freevars(list_t *lexems, pyobj_t obj){

  if (0 == lexem_is(lexems, "dir::freevars")){
    print_parse_error("Erreur freevars : dir::freevars error", lexems);
    return -1;
  } 

  lexem_peek(lexems);

  if (-1 == parse_eol( lexems )){
    return -1;
  }

  pyobj_t *p_list = malloc(sizeof(pyobj_t));
  pyobj_t freevars = malloc(sizeof(pyobj_t)); 
  assert(freevars != NULL);
  assert(p_list != NULL);
  int i = 0;
  list_t p = *lexems;

  if (next_lexem_is(lexems, "string")){
    p = list_next(p);
    obj->py.codeblock->binary.content.freevars = freevars;
    obj->py.codeblock->binary.content.freevars->py.list.value = p_list;
    obj->py.codeblock->binary.content.freevars->py.list.size = 0;
    obj->py.codeblock->binary.content.freevars->type = 91;
    lexem_t current_lexem = (lexem_t )p->content;
    int n = strlen(current_lexem->value);
    obj->py.codeblock->binary.content.freevars->py.list.value[i] = malloc(sizeof(pyobj_t));
    obj->py.codeblock->binary.content.freevars->py.list.value[i]->py.string.buffer = malloc(sizeof(char*)*n);
    obj->py.codeblock->binary.content.freevars->py.list.value[i]->type = 115;
    strncpy(obj->py.codeblock->binary.content.freevars->py.list.value[i]->py.string.buffer , current_lexem->value, n);
    obj->py.codeblock->binary.content.freevars->py.list.value[i]->py.string.length = n;
    obj->py.codeblock->binary.content.freevars->py.list.size++;
    p = list_next(p);
    p = list_next(p);
  }else{
    free(p_list); //BIZARRE
    free(freevars);
  }

  while ( next_lexem_is(lexems, "string") ){
    if (strcmp(((lexem_t)p->content)->type, "string")==0){

        p_list = (pyobj_t *)realloc(p_list, sizeof(p_list)+sizeof(pyobj_t));

        assert(p_list != NULL);

        //obj->py.codeblock->binary.content.interned->py.list.value[i+1] = ;
        //obj->py.codeblock->binary.content.interned->py.list.size++;

        lexem_t current_lexem = (lexem_t)p->content;
        int n_prime = strlen(current_lexem->value);
        obj->py.codeblock->binary.content.freevars->py.list.value[i+1] = malloc(sizeof(pyobj_t));
        obj->py.codeblock->binary.content.freevars->py.list.value[i+1]->py.string.buffer = malloc(sizeof(char*)*n_prime);
        obj->py.codeblock->binary.content.freevars->py.list.value[i+1]->type = 115;
        strncpy(obj->py.codeblock->binary.content.freevars->py.list.value[i+1]->py.string.buffer, current_lexem->value, n_prime);
        obj->py.codeblock->binary.content.freevars->py.list.value[i+1]->py.string.length = n_prime;
        obj->py.codeblock->binary.content.freevars->py.list.size++;
        p = list_next(p);
        //int incr = 1;

      }
      lexem_advance(lexems);
      if (-1 == parse_eol( lexems )){
      return -1;
      }

    }

  return 0;
}

int parse_cellvars(list_t *lexems, pyobj_t obj){

  if (0 == lexem_is(lexems, "dir::cellvars")){
    print_parse_error("Erreur cellvars : dir::cellvars error", lexems);
    return -1;
  } 

  lexem_peek(lexems);

  if (-1 == parse_eol( lexems )){
    return -1;
  }

  pyobj_t *p_list = malloc(sizeof(pyobj_t));
  pyobj_t cellvars = malloc(sizeof(pyobj_t)); 
  assert(cellvars!= NULL);
  assert(p_list != NULL);
  int i = 0;
  list_t p = *lexems;

  if (next_lexem_is(lexems, "string")){
    p = list_next(p);
    obj->py.codeblock->binary.content.cellvars = cellvars;
    obj->py.codeblock->binary.content.cellvars->py.list.value = p_list;
    obj->py.codeblock->binary.content.cellvars->py.list.size = 0;
    obj->py.codeblock->binary.content.cellvars->type = 91;
    lexem_t current_lexem = (lexem_t )p->content;
    int n = strlen(current_lexem->value);
    obj->py.codeblock->binary.content.cellvars->py.list.value[i] = malloc(sizeof(pyobj_t));
    obj->py.codeblock->binary.content.cellvars->py.list.value[i]->py.string.buffer = malloc(sizeof(char*)*n);
    obj->py.codeblock->binary.content.cellvars->py.list.value[i]->type = 115;
    strncpy(obj->py.codeblock->binary.content.cellvars->py.list.value[i]->py.string.buffer , current_lexem->value, n);
    obj->py.codeblock->binary.content.cellvars->py.list.value[i]->py.string.length = n;
    obj->py.codeblock->binary.content.cellvars->py.list.size++;
    p = list_next(p);
    p = list_next(p);
  }else{
    free(p_list); //BIZARRE
    free(cellvars);
  }

  while ( next_lexem_is(lexems, "string") ){
    if (strcmp(((lexem_t)p->content)->type, "string")==0){

        p_list = (pyobj_t *)realloc(p_list, sizeof(p_list)+sizeof(pyobj_t));

        assert(p_list != NULL);

        //obj->py.codeblock->binary.content.interned->py.list.value[i+1] = ;
        //obj->py.codeblock->binary.content.interned->py.list.size++;

        lexem_t current_lexem = (lexem_t)p->content;
        int n_prime = strlen(current_lexem->value);
        obj->py.codeblock->binary.content.cellvars->py.list.value[i+1] = malloc(sizeof(pyobj_t));
        obj->py.codeblock->binary.content.cellvars->py.list.value[i+1]->py.string.buffer = malloc(sizeof(char*)*n_prime);
        obj->py.codeblock->binary.content.cellvars->py.list.value[i+1]->type = 115;
        strncpy(obj->py.codeblock->binary.content.cellvars->py.list.value[i+1]->py.string.buffer, current_lexem->value, n_prime);
        obj->py.codeblock->binary.content.cellvars->py.list.value[i+1]->py.string.length = n_prime;
        obj->py.codeblock->binary.content.cellvars->py.list.size++;
        p = list_next(p);
        //int incr = 1;

      }
      lexem_advance(lexems);
      if (-1 == parse_eol( lexems )){
      return -1;
      }

    }

  return 0;
}


int parse_code(list_t *lexems){

  if (0 == lexem_is(lexems, "dir::text")){
    print_parse_error("Erreur code : dir::text error", lexems);
    return -1;
  } 

  lexem_peek(lexems);

  if (-1 == parse_eol( lexems )){
    return -1;
  }

  while ( next_lexem_is(lexems, "insn::0") || next_lexem_is(lexems, "insn::1") || next_lexem_is(lexems, "dir::line") || next_lexem_is(lexems, "symbol")){ // A VOIR
      lexem_advance(lexems);
      if (-1 == parse_eol( lexems )){
      return -1;
      }

    }

  return 0;
}


int parse_assembly_line(list_t * lexems){

  if (-1 == parse_insn(lexems) && -1 == parse_source_lineno(lexems) && -1 == parse_label(lexems)){
    return -1;
  }
  return 0;

}


int parse_label(list_t * lexems){

  if (0 == lexem_is(lexems, "symbol")){
    print_parse_error("Erreur label : symbol error", lexems);
    return -1;
  }

  lexem_peek(lexems);

  if (0 == lexem_is(lexems, "blank")){
    print_parse_error("Erreur label : blank error", lexems);
    return -1;
  }

  lexem_peek(lexems);

  if (0 == lexem_is(lexems, "colon")){
    print_parse_error("Erreur label : colon error", lexems);
    return -1;
  }

  return 0;
}



int parse_source_lineno(list_t * lexems){


  if (0 == lexem_is(lexems, "dir::line")){
    print_parse_error("Erreur source-lineno : dir::line error", lexems);
    
    return -1;
  }

  lexem_peek(lexems);

  if (0 == lexem_is(lexems, "blank")){
    print_parse_error("Erreur source-lineno : blank error", lexems);
    
    return -1;
  }

  lexem_peek(lexems);

  if (0 == lexem_is(lexems, "integer::dec")){
    print_parse_error("Erreur source-lineno : integer::dec error", lexems);
    return -1;
  }

  return 0;
}


int parse_insn(list_t *lexems){

  

  if (lexem_is(lexems, "insn::0")){ // cas ou on a {‘insn::0’}
    
    return 0;
  }

  if (lexem_is(lexems, "insn::1")){ // cas ou on a {‘insn::1’} 
    lexem_peek(lexems);

    if (0 == lexem_is(lexems, "integer::dec") && 0 == lexem_is(lexems, "symbol")){
      print_parse_error("Erreur insn : integer::dec or symbol error", lexems);
      
      return -1;
    }

    
    return 0;

  }
  

  return -1; // Si il n'y a aucune correspondance
  
}




int parse_eol(list_t *lexems){

  int incr = 0;
  int is_blank=0;
  int is_newline=0;
  printf("salut\n");
  while ( (lexem_is(lexems, "blank") || lexem_is(lexems, "comment") || lexem_is(lexems, "newline") )&& (is_blank == 0) && (is_newline == 0) ){
    
    if (lexem_is(lexems, "blank")){
      if (next_lexem_is(lexems, "comment") || next_lexem_is(lexems, "newline") ){
        lexem_peek(lexems);
        if (lexem_is(lexems, "comment")){
          if (next_lexem_is(lexems, "newline")){
            lexem_peek(lexems);
            if (next_lexem_is(lexems, "blank")){
              lexem_peek(lexems);
              incr ++;

            }else{
              incr++;
            }

          }
          
          
        }else if (lexem_is(lexems, "newline")){
          if (next_lexem_is(lexems, "blank")){
            lexem_peek(lexems);
            incr++;
          }else{
            incr++;
          }
          if (next_lexem_is(lexems, "comment") || next_lexem_is(lexems, "newline")){
            lexem_peek(lexems);
          }
          else{
            is_newline++;
          }
        }

      }else{
        is_blank++;
      }

    }

    else if(lexem_is(lexems, "comment")){
      if (next_lexem_is(lexems, "newline")){
        lexem_peek(lexems);

        if (next_lexem_is(lexems, "blank")){
          lexem_peek(lexems);
          incr++;

        }else{
          incr++;
        }

      }
      if (next_lexem_is(lexems, "newline") || next_lexem_is(lexems, "comment")){
        lexem_peek(lexems);
      }
      else{
        is_newline++;
      }
    }

    else if (lexem_is(lexems, "newline")){
      if (next_lexem_is(lexems, "blank")){
        lexem_peek(lexems);
        incr++;

      }else{
        incr++;
      }
    }

    if (next_lexem_is(lexems, "newline") || next_lexem_is(lexems, "comment")){
        lexem_peek(lexems);
      }
      else{
        is_newline++;
      }


  }

  if (incr>0){
    return 0;

  }else{
    print_parse_error("Erreur : eol failed ! ", lexems);
    return -1;
    
  }

  }



