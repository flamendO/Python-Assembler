#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <pyas/queue.h>
#include <pyas/list.h>
#include <pyas/regexp.h>
#include <pyas/chargroup.h>

int issFull(int characters[256]) { // permet de dire si le tableau de caractere est complet ou pas 
    for (int i = 0; i < 256; i++) {
        if (characters[i] == 0) {
            return 0;
        }
    }
    return 1;
}

int re_match_zero_or_more(int characters[256], list_t regexp, char *source, char **end) {
    char *t = source;

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

int re_match_one_or_more(int characters[256], list_t regexp, char *source, char **end) {
    char *t = source;
    int matchedOnce = 0;

    while ('\0' != *t && (1 == characters[(int)*t] || issFull(characters))) {
        t++;

        if (re_match(regexp, t, end)) {
            
            matchedOnce = 1;
        }
    }

    if (matchedOnce) {
        return 1;
    }

    if (end) *end = source;
    return 0;
}

int re_match_empty(list_t regexp, char *source, char **end) {
    if (list_empty(regexp)) {
        if (end) *end = source;
        return 1;
    }

    char_group *group = (char_group *)(list_first(regexp));

    if (group->op == ZERO_OR_MORE) {
        return re_match_empty(list_next(list_next(regexp)), source, end);
    }

    if (group->op == ONE_OR_MORE) {
        return re_match_empty(group->characters, source, end);
    }

    if (group->op == ZERO_OR_ONE) {
        return re_match_empty(list_next(regexp), source, end);
    }

    return 0;
}



int re_match_zero_or_one(int characters[256], list_t regexp, char *source, char **end) {
    char *t = source;

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





int re_match(list_t regexp, char *source, char **end) {
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
        if (re_match_zero_or_more(group->characters, list_next(regexp), source, end)) {
            return 1;
        }
    } else if (group->op == ONE_OR_MORE) {
        if (re_match_one_or_more(group->characters, list_next(regexp), source, end)) {
            return 1;
        }
    } else if (group->op == ZERO_OR_ONE) {
        if (re_match_zero_or_one(group->characters, list_next(regexp), source, end)) {
            return 1;
        }
    } else {
        if (*source != '\0' && (issFull(group->characters) || group->characters[(int)*source] == 1)) {
            if (re_match(list_next(regexp), source + 1, end)) {
                return 1;
            }
        }
    }

    return 0;
}
