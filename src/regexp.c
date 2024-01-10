#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <pyas/queue.h>
#include <pyas/list.h>
#include <pyas/regexp.h>
#include <pyas/chargroup.h>

int re_read(char * regexp){
    
    fifo *regex_queue = char_to_queue(regexp);

    if (fifo_empty(regex_queue)) {
        fprintf(stderr, "Error: Invalid regular expression.\n");
        return EXIT_FAILURE;
    }

    while (!fifo_empty(regex_queue)) {
        char_group *group = (char_group *)fifo_dequeue(regex_queue);

        printf("One ");
        if (group->complement) {
            printf("not ");
        }
        printf("in '");
        for (int i = 0; i < 128; i++) {
            if (group->characters[i]) {
                printf("%c", (char)i);
            }
        }
        printf("', ");

        switch (group->op) {
            case ZERO_OR_ONE:
                printf("zero or one time.\n");
                break;
            case ZERO_OR_MORE:
                printf("zero or more times.\n");
                break;
            case ONE_OR_MORE:
                printf("one or more times.\n");
                break;
            case ONE_TIME:
                printf("one time.\n");
                break;
            default:
                break;
        }

        free(group);
    }

    return EXIT_SUCCESS;

}



int issFull(int characters[128]) {
    for (int i = 0; i < 128; i++) {
        if (characters[i] == 0) {
            return 0;
        }
    }
    return 1;
}

int re_match_zero_or_more(int characters[128], list_t regexp, char *source, char **end, int complement) {
    char *t = source;
    if (0 == complement){
    
    while ('\0' != *t && (1 == characters[(int)*t] || issFull(characters))) {
        t++;
    }

    do {
        if (re_match(regexp, t, end)) {
            return 1;
        }
    } while (t-- > source);

    if (end) *end = source;
    return 0;
    }

    else{

        while ('\0' != *t && 0 == characters[(int) *t]){
            t++;
        }

    do{
        if (re_match(regexp, t, end)){
            return 1;
        }
    }while (t-- > source);

    if (end) *end = source;
    return 0;

    }
}

int re_match_one_or_more(int characters[128], list_t regexp, char *source, char **end, int complement) { // remarque : '^a+g*' 'bbbggkoalah' dira que tout correspond à cause du tout sauf a
    char *t = source;
    int matchedOnce = 0;
    if (0 == complement){
    while ('\0' != *t && (1 == characters[(int)*t] || issFull(characters))) {
        t++;
        matchedOnce = 1;
        }
        do{
        if (re_match(regexp, t, end)){
            if (matchedOnce ==1){
            return 1;}
        }
        }while (t-- > source);


    if (end) *end = source;
    return 0;
    }

    else{
        while ('\0' != *t && 0 == characters[(int) *t] ){
            t++;
            matchedOnce = 1;
        }
        do{
        if (re_match(regexp, t, end)){
            if (matchedOnce ==1){
            return 1;}
        }
        }while (t-- > source);


    if (end) *end = source;
    return 0;
    }
}





int re_match_zero_or_one(int characters[128], list_t regexp, char *source, char **end, int complement) {
    char *t = source;
    if (0 == complement){
    if (*t != '\0' && (1 == characters[(int)*t] || issFull(characters))) {
        t++;

        
        if (re_match(regexp, t, end) == 1) {
            return 1;
        }
    }

    
    if (re_match(regexp, t, end) == 1) {
        return 1;
    }

    
    if (end) *end = source;
    return 0;
    }

    else{
        if (*t != '\0' && (0 == characters[(int)*t] || issFull(characters))) {
        t++;

        
        if (re_match(regexp, t, end) == 1) {
            return 1;
        }
    }

    
    if (re_match(regexp, t, end) == 1) {
        return 1;
    }

    
    if (end) *end = source;
    return 0;

    }
}


int re_match(list_t regexp, char *source, char **end) {
    
    if ((list_t) regexp == impossible_fifo && !list_empty(regexp)) { //si c'est la liste impossible
        if (end) *end = source;
    return 0;
  }


    if (source == NULL) {
        if (end) *end = source;
        return 0;
    }

    if (list_empty(regexp)) {
        if (end) *end = source;
        return 1;
    }

    char_group *group = (char_group *)(list_first(regexp));

    

    if (group->op == ZERO_OR_MORE) {
        if (re_match_zero_or_more(group->characters, list_next(regexp), source, end, (int)group->complement)) {
            return 1;
        }
    } else if (group->op == ONE_OR_MORE) {
        if (re_match_one_or_more(group->characters, list_next(regexp), source, end, (int)group->complement)) {
            return 1;
        }
    } else if (group->op == ZERO_OR_ONE) {
        if (re_match_zero_or_one(group->characters, list_next(regexp), source, end, (int)group->complement)) {
            return 1;
        }
    } else {
        if (group->complement == 0){
         // il n'y a pas ^
        if (*source != '\0' && (issFull(group->characters) || (int)group->characters[(int)*source] == 1)) {
            
            
            if (re_match(list_next(regexp), source + 1, end)) { //si la suite match
                return 1;
            }
            }
        }
        else{ //il y a un ^

            if (issFull(group->characters)){ // cas du ^.   -> ' ^.a+ ' considère que si ça match avec a+ c'est bon
                if (0 == strlen(source) || *source == '\0' ){
                    return 1; // La source est vide, cela correspond à '^.'
                    }
                else{
                    if (re_match(list_next(regexp), source + 1, end)) { //si la suite match
                        return 1;
                    }
                }
            }

        

            if (*source != '\0' && group->characters[(int)*source] == 1){ // Si le caractère dans la source apparait dans le groupe de caractere, par exemple '^a' avec 'a'
                if (end) *end = source;
                return 0; //ça match pas
            }

            if (*source != '\0' && group->characters[(int)*source] == 0){ //si ça apparait pas, on verifie la suite
                if (re_match(list_next(regexp), source + 1, end)){
                    return 1;
                }
            }
        }
        }
    

    return 0;
    }

        

