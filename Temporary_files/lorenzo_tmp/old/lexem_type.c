#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <pyas/lexem_type.h>
//#include <pyas/list.h>
#include <pyas/queue.h>

struct lexem_type { 
  char *type;
  char *value;
  list_t l_value ; 
};

int     lexem_type_print( void *_lex ) { 
  lexem_type_t lex = _lex; 

  return printf( "[%s] %s",
		 lex->type,
		 lex->value );
}


lexem_type_t * lex_read(char *filename){
  FILE * pf = NULL;
  pf = fopen(filename, "r");
  if(pf == NULL) {
    printf("Erreur d'ouverture du fichier");
    exit(EXIT_FAILURE);
  }
  int i = 0 ;
  //int column = 0;
  //int line = 1;
  char * read_line = malloc(sizeof(char) * 150);
  char * value = NULL; 
  char * type = NULL;
  char * commentary = NULL;
  lexem_type_t *group_lexem = malloc(sizeof(lexem_type_t) * 100);
  lexem_type_t current_lexem = NULL;
  list_t re_list = NULL ;

  while (! feof( pf )){
    //column = 0 ;
    fgets(read_line, 150, pf);
    current_lexem = malloc(sizeof(struct lexem_type));
    //printf("%s", read_line);
      if(*read_line == '\n'){
        //line += 1;
        continue ;
      }
      else if(*read_line == '#'){
        i += 1; // Utile pour ajouter dans le tableau de pointeur à la fin
        current_lexem->type = malloc(sizeof("comment"));
        current_lexem->value = malloc(sizeof(char)*strlen(read_line));
        if(current_lexem->type== NULL || current_lexem->value == NULL) {
          printf("Erreur d'allocation mémoire");
          exit(EXIT_FAILURE);
        }
        strcpy(current_lexem->type, "comment");
        strcpy(current_lexem->value, read_line);
        //current_lexem->column = column ;
        //current_lexem->line = line ;
        //column += strlen(read_line) - 1;
      }
      else{
        i += 1; // Utile pour ajouter dans le tableau de pointeur à la fin
        int k = 0;
        int j = 0;
        while(*(read_line + k) != '\t'){
          k += 1 ;
        }
        current_lexem->type = malloc(sizeof(char)*k);
        if(current_lexem->type== NULL) {
          printf("Erreur d'allocation mémoire");
          exit(EXIT_FAILURE);
        }
        strncpy(current_lexem ->type, read_line, k);
        //current_lexem->line = line ;
        //current_lexem ->column = column ;
        while(*(read_line + k) == '\t'){
          k += 1 ;
        }
        j = k ;
        while(*(read_line + k) != '\0'){
          k += 1 ;
        }
        current_lexem->value = malloc(sizeof(char)*k);
        if(current_lexem->value== NULL) {
          printf("Erreur d'allocation mémoire");
          exit(EXIT_FAILURE);
        }
        strncpy(current_lexem ->value, read_line + j, k);
        //current_lexem->line = line ;
        //current_lexem ->column = column + j;
      } 
      //line += 1;
      //lexem_print(current_lexem);
      re_list = malloc(sizeof(list_t));
      re_list = fifo_to_list(char_to_queue(current_lexem->value));
      *(group_lexem + i) = current_lexem ;
      lexem_type_print(*(group_lexem + i));
  }
  free(current_lexem);
  return group_lexem;
} 
