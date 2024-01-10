
/**
 * @file lexem.h
 * @author François Cayre <francois.cayre@grenoble-inp.fr>
 * @date Fri Jul  2 17:59:42 2021
 * @brief Lexems.
 *
 * Lexems.
 */

#include <pyas/list.h>
#include <pyas/pyobj.h>

#ifndef _LEXEM_H_
#define _LEXEM_H_

#ifdef __cplusplus
extern "C" {
#endif
struct lexem { 
  char *type;
  char *value;
  int   line;
  int   column; 
};

  typedef struct lexem *lexem_t;

  lexem_t lexem_new( char *type, char *value, int line, int column ); 
  int     lexem_print( void *_lex );
  int     lexem_delete( void *_lex ); 

  
  int lexem_type_strict(lexem_t lexem, char * type_t); // Prend un lexeme en entrée et renvoie 1 si il est du type demandé, 0 sinon
  lexem_t lexem_peek(list_t *lexems); //  renverra le prochain lexème utile dans la liste de lexèmes, en avançant de une case dans la liste de lexèmes
  lexem_t lexem_advance( list_t *lexems ); // retourne la liste en enlevant les lexemes pas utiles
  int lexem_is( list_t *lexems, char *type ); // détermine si le premier lexeme utile est bien du type demandé
  void print_parse_error( char *msg, list_t *lexems ); // permettra d’afficher le message d’erreur msg en le situant grâce aux coordonnées du lexème en tête de la liste *lexems.
  //int next_parse_is(list_t *lexems, int (* parse_callback) (list_t *lexems, pyobj_t obj) ); // Renvoie -1 si la liste des lexeme suivant le lexeme actuel ne parse pas avec la fonction callback, 0 sinon
  int next_lexem_is(list_t *lexems, char * type_t); // Renvoie 1 si le prochain lexeme de la liste est bien du type demandé, 0 sinon 
  
  /*FONCTIONS RECURSIVES : Renvoient 0 si il y a parsing, et -1 sinon */

  int parse_pys(list_t *lexems, pyobj_t obj);
  int parse_prologue(list_t *lexems, pyobj_t obj);
  int parse_set_directives(list_t *lexems, pyobj_t obj);
  int parse_set_version_pyvm(list_t *lexems, pyobj_t obj);
  int parse_set_flags(list_t *lexems, pyobj_t obj);
  int parse_set_filename(list_t *lexems, pyobj_t obj);
  int parse_set_name(list_t *lexems, pyobj_t obj);
  int parse_set_source_size(list_t *lexems, pyobj_t obj);
  int parse_set_stack_size(list_t *lexems, pyobj_t obj);
  int parse_set_arg_count(list_t *lexems, pyobj_t obj);
  int parse_set_kwonly_arg_count(list_t *lexems, pyobj_t obj);
  int parse_set_posonly_arg_count(list_t *lexems, pyobj_t obj);
  int parse_interned_strings(list_t *lexems, pyobj_t obj);
  int parse_constants(list_t *lexems, pyobj_t obj);
  int parse_constant(list_t *lexems, pyobj_t obj, int i);
  int parse_list(list_t *lexems, pyobj_t obj, int i);
  int parse_tuple(list_t *lexems, pyobj_t obj, int i);
  int parse_names(list_t *lexems, pyobj_t obj);
  int parse_varnames(list_t *lexems, pyobj_t obj);
  int parse_freevars(list_t *lexems, pyobj_t obj);
  int parse_cellvars(list_t *lexems, pyobj_t obj);
  int parse_code(list_t *lexems);
  int parse_assembly_line(list_t *lexems);
  int parse_label(list_t *lexems);
  int parse_source_lineno(list_t *lexems);
  int parse_insn(list_t *lexems);
  int parse_eol(list_t *lexems);



  
  



#ifdef __cplusplus
}
#endif

#endif /* _LEXEM_H_ */
