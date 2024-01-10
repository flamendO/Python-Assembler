#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <pyas/lexem_type.h>
//#include <pyas/list.h>
//#include <pyas/queue.h>


int     lexem_type_print( void *_lex ) { 
  lexem_type_t lex = _lex; 

  return printf( "[%s] %s",
		 lex->type,
		 lex->value );
}

int char_q_print(char_group *lex){

  for (int i = 0; i < 128; i++) {
            if (lex->characters[i]) {
                printf("%c", (char)i);
            }
        }
  return 0;
}

list_t lex_read(char *filename){
  FILE * pf = NULL;
  pf = fopen(filename, "r");
  if(pf == NULL) {
    printf("Erreur d'ouverture du fichier");
    exit(EXIT_FAILURE);
  }
  char * read_line = calloc(150,sizeof(char));
  list_t group_lexem = list_new();
  lexem_type_t current_lexem = NULL;
  list_t re_list = list_new() ;

  while (! feof( pf )){
    fgets(read_line, 150, pf);
    current_lexem = calloc(1, sizeof(struct lexem_type));
      if(*read_line == '\n'){
        continue ;
      }
      else if(*read_line == '#'){
        continue;
      }
      else{
        int k = 0;
        int j = 0;
        while(*(read_line + k) != '\t'){
          k += 1 ;
        }
        current_lexem->type = calloc(k+1, sizeof(char));
        if(current_lexem->type== NULL) {
          printf("Erreur d'allocation mémoire");
          exit(EXIT_FAILURE);
        }
        strncpy(current_lexem ->type, read_line, k);
        
        while(*(read_line + k) == '\t'){
          k += 1 ;
        }
        j = k ;
        while(*(read_line + k) != '\0'){
          k += 1 ;
        }
        current_lexem->value = calloc(k+1, sizeof(char));
        if(current_lexem->value== NULL) {
          printf("Erreur d'allocation mémoire");
          exit(EXIT_FAILURE);
        }
        strncpy(current_lexem ->value, read_line + j, k);
      } 
      re_list = malloc(sizeof(list_t));
      if(re_list== NULL) {
          printf("Erreur d'allocation mémoire");
          exit(EXIT_FAILURE);
        }
      //le if suivant permet de supprimer le \n généré par fgets si le lexem n'est pas un commentaire ou un retour à la ligne
      if(strcmp(current_lexem->type, "newline ") != 0 && strcmp(current_lexem->type, "comment ") != 0){
        *(current_lexem->value + strcspn(current_lexem->value, "\n")) = 0;
      }
      fifo * char_queue = malloc(sizeof(fifo*));
      char_queue= char_to_queue(current_lexem->value);
      re_list = fifo_to_list(char_queue);
      current_lexem->l_value = list_new();
      current_lexem->l_value = re_list;
      group_lexem = list_add_first(group_lexem, (lexem_type_t) current_lexem);
  }
  if(group_lexem == NULL){
    return NULL;
  }
  free(current_lexem);
  return group_lexem;
} 
