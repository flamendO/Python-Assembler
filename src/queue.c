

#include <assert.h>
#include <stdio.h>
#include <stdlib.h> 
#include <string.h>

#include <pyas/queue.h>

fifo *impossible_fifo = NULL; 



fifo *fifo_new(void) {
  fifo *q = (fifo *)malloc(sizeof(fifo));
  if (q == NULL) {
    fprintf(stderr, "Erreur d'allocation de mémoire.\n");
    exit(EXIT_FAILURE);
  }

  q->head = NULL;
  q->tail = NULL;
  return q;
}

int fifo_empty(fifo *q) {
  return q->head == NULL;
}

void fifo_enqueue(fifo *q, void *object) {
  link_t *new_link = (link_t *)malloc(sizeof(link_t));
  if (new_link == NULL) {
    fprintf(stderr, "Erreur d'allocation de mémoire.\n");
    exit(EXIT_FAILURE);
  }

  new_link->content = object;
  new_link->next = NULL;

  if (q->tail == NULL) {
    q->head = new_link;
    q->tail = new_link;
  } else {
    q->tail->next = new_link;
    q->tail = new_link;
  }
}

list_t fifo_to_list(fifo *q) {
  
  if (q == impossible_fifo){
    
    return q;
  }

  if (fifo_empty(q)) {
        return NULL; 
    }
  link_t * li = malloc(sizeof(struct link_t));

  li->content = (q->head)->content;
  li->next = (q->head)->next;

  return li;
}

void fifo_print(fifo *q, void (*print_callback)(void *)) {
    link_t *current = q->head;

    while (current != NULL) {
        if (current->content != NULL) {
            print_callback(current->content);
        }
        current = current->next;
    }

    printf("\n");
}


void print_char_callback(void *data) {
  printf("%c", *(char *)data);
}

void print_int_callback(void *data) {
  printf("%d", *(int *)data);
}

void *fifo_dequeue(fifo *q) {
  if (fifo_empty(q)) {
    fprintf(stderr, "La file est vide.\n");
    exit(EXIT_FAILURE);
  }

  link_t *first_link = q->head;
  q->head = first_link->next;

  if (q->head == NULL) {
    q->tail = NULL;
  }

  void *content = first_link->content;
  free(first_link);
  return content;
}

int fifo_length(fifo *q) {
  int length = 0;
  link_t *current = q->head;

  while (current != NULL) {
    length++;
    current = current->next;
  }

  return length;
}

void *fifo_first(fifo *q) {
  if (fifo_empty(q)) {
    return NULL;
  }

  return q->head->content;
}

void *fifo_last(fifo *q) {
  if (fifo_empty(q)) {
    return NULL;
  }

  return q->tail->content;
}

void fifo_delete(fifo **q) {
  link_t *current = (*q)->head;

  while (current != NULL) {
    link_t *temp = current;
    current = current->next;
    free(temp);
  }

  free(*q);
  *q = NULL;
}


void print_char_group_callback(void *data) {
    char_group *group = (char_group *)data;
    if (group->complement) {
        printf("^");
    }
    for (int i = 0; i < 128; i++) {
        if (group->characters[i]) {
            printf("%c", (char)i);
        }
    }

    
    switch (group->op) {
        case ZERO_OR_ONE:
            printf("?");
            break;
        case ZERO_OR_MORE:
            printf("*");
            break;
        case ONE_OR_MORE:
            printf("+");
            break;
        
        case ONE_TIME:
            break;
    }
    printf(" ");
}

int condition = 0;

char_group * read_bracket(int k,  char * p_regexp, int * k_final){ //lis un crochet
  k += 1;
  int j = k ;
  int count = 0;
  char_group * group_of_charac = malloc(sizeof(char_group)) ;
  while(*(p_regexp + k) != ']'){
    if(is_special(k, p_regexp) != ONE_TIME){
      printf("Erreur caractère spécial sans chaine\n");
      //*cond = 1;
      exit(EXIT_FAILURE);
      
    }
    if(*(p_regexp + k ) == '-'){
      if(*(p_regexp + k - 1 ) == '['){
        printf("Caractère spécial non échappé\n");
        condition += 1 ;
        fifo *empty_fifo = fifo_new();
        impossible_fifo = empty_fifo;
        return group_of_charac;
      }
      int first = *(p_regexp + k - 1) ;
      int last = *(p_regexp + k + 1) ;
      for(; first < last + 1 ; first ++){
        group_of_charac ->characters[first] = 1 ;
      }
      count += 1 ;
      k += 1;
    }
    else if(*(p_regexp + k) == '\\'){
      if(is_special(k+1, p_regexp) == ONE_TIME && *(p_regexp + k+1) != 'n' && *(p_regexp + k+1) != 't' && *(p_regexp + k+1) != '-' && *(p_regexp + k+1) != '.' && *(p_regexp + k+1) != '^' && *(p_regexp + k+1) != '\\'  && *(p_regexp + k + 1) != '\"'){
        printf("Erreur caractère non spécial echappé \n");
        exit(EXIT_FAILURE);
      }
      if(*(p_regexp + k + 1) == 'n'){
        group_of_charac ->characters[10] = 1;
      }
      else if(*(p_regexp + k + 1) == 't'){
        group_of_charac->characters[9] = 1;
        group_of_charac->characters[32] = 1;
      }
      else{
      	group_of_charac ->characters[(int)*(p_regexp + k + 1)] = 1;
      }
      j += 2 ;
      k += 2;
      //printf("%c\n", *(p_regexp + k));
      j = k ;
      continue;
    }
    
    group_of_charac ->characters[(int)*(p_regexp + k)] = 1;

    k += 1;
  }

  if (count == 0 && *(p_regexp + j) != ']'){
    for(; j < k; j ++){ 
      if(*(p_regexp + j) == '\\'){
        if(is_special(j+1, p_regexp) == ONE_TIME && *(p_regexp + j+1) != 'n' && *(p_regexp + j+1) != 't' && *(p_regexp + j+1) != '-' && *(p_regexp + j+1) != '.' && *(p_regexp + j+1) != '^' && *(p_regexp + k+1) != '\\'  && *(p_regexp + k + 1) != '\"'){
        printf("Erreur caractère non spécial echappé \n");
        //*cond = 1;
        exit(EXIT_FAILURE);
      }
        if(*(p_regexp + j + 1) == 'n'){
          group_of_charac ->characters[10] = 1;
          //group_of_charac ->characters[32] = 1;
          j += 1;
        }
        else if(*(p_regexp + j + 1) == 't'){
          group_of_charac->characters[9] = 1;
          group_of_charac->characters[32] = 1;
          j += 1;
        }
        else{
          group_of_charac ->characters[(int)*(p_regexp + j + 1)] = 1;
          j += 1; 
        }
      }else{
        group_of_charac ->characters[(int)*(p_regexp + j)] = 1;
      }
    }
  }
  group_of_charac ->op = is_special(k + 1, p_regexp) ;
  if(*(p_regexp + k-1)=='^' && *(p_regexp + k - 2) !='\\'){
    printf("Erreur : la négation doit précéder un caractère\n");
    //*cond = 1;
    exit(EXIT_FAILURE);
    
    
  }
  if(group_of_charac ->op != ONE_TIME){
    *k_final = k + 1 ;
  }else{
    *k_final = k ;
  }
  return group_of_charac ;
}

char_group * read_point(char_group * regexp2){
  for(int j = 0; j <128; j++){
        regexp2->characters[j] = 1 ;
    }
  return regexp2 ;
}

operator is_special(int k, char * p_regexp){ //ça verifie si il y a un caractère spécial non échappé à l'indice k 
  if(*(p_regexp + k) == '?'){
    return ZERO_OR_ONE ;
  }
  else if(*(p_regexp + k) == '+'){
    return ONE_OR_MORE ;
  }
  else if(*(p_regexp + k) == '*'){
    return ZERO_OR_MORE ;
  }
  else{
    return ONE_TIME ;
  }
}



fifo *char_to_queue(char *p_regexp) {
  int *p_condition = &condition;
  unsigned long n = strlen(p_regexp);
  fifo *fifo_re = fifo_new();
  int negation = 0;

  if(*(p_regexp + n - 1)=='^' && *(p_regexp + n - 2) !='\\'){
    //printf("Erreur : la négation doit précéder un caractère\n");
    //exit(EXIT_FAILURE);
    fifo *empty_fifo = fifo_new();
    impossible_fifo = empty_fifo;
    return empty_fifo;
  }

  for (unsigned long int i = 0; i < n; i++) {
    char_group *regexp2 = (char_group *)calloc(1,sizeof(char_group));
    if(is_special(i, p_regexp) != ONE_TIME){
      fifo *empty_fifo = fifo_new();
      impossible_fifo = empty_fifo;
      return empty_fifo;
    }

    if (*(p_regexp + i) == '^') {
      negation = 1;
      continue;
    } else if (*(p_regexp + i) == '[') {
      int j = 0;
      regexp2 = read_bracket(i, p_regexp, &j);
      if (1 == *p_condition){
        fifo *empty_fifo = fifo_new();
        impossible_fifo = empty_fifo;
        return empty_fifo;
      }
      i = j;
    } else if (*(p_regexp + i) == '.') {
      regexp2 = read_point(regexp2);
      regexp2->op = is_special(i + 1, p_regexp);
      if (regexp2->op != ONE_TIME) {
        i += 1;
      }
    } else if (*(p_regexp + i) == '\\') {
      i += 1; // saute le caractere d'echappement '\'
      if(is_special(i, p_regexp) == ONE_TIME && *(p_regexp + i) != 'n' && *(p_regexp + i) != 't' && *(p_regexp + i) != '-' && *(p_regexp + i) != '.' && *(p_regexp + i) != '\\' && *(p_regexp + i) != '[' && *(p_regexp + i) != ']' && *(p_regexp + i) != '^'  && *(p_regexp + i) != '\"'){
        fifo *empty_fifo = fifo_new();
        impossible_fifo = empty_fifo;
        return empty_fifo;
      }
      else if(*(p_regexp + i) == 'n'){
        regexp2 ->characters[10] = 1;
        //regexp2 ->characters[32] = 1;
      }
      else if(*(p_regexp + i) == 't'){
        regexp2->characters[9] = 1;
        regexp2->characters[32] = 1;
      }
      else{
        regexp2->characters[(int)*(p_regexp + i)] = 1;
      }
      regexp2->op = is_special(i + 1, p_regexp);
      if (regexp2->op != ONE_TIME) {
        i += 1;
      }
    } else {
      regexp2->characters[(int)*(p_regexp + i)] = 1;
      regexp2->op = is_special(i + 1, p_regexp);
      if (regexp2->op != ONE_TIME) {
        i += 1;
      }
    }
    
    regexp2->complement = negation;
    fifo_enqueue(fifo_re, regexp2);
    negation = 0;
  }

  return fifo_re;
}
