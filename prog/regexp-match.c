/**
 * @file regexp.c
 * @author François Cayre <francois.cayre@grenoble-inp.fr>
 * @date Fri Jul  28 09:56:03 2022
 * @brief Regexp parsing and matching. 
 *
 * Program for regexp parsing, and regexp matching. 
 */

#include <assert.h>
#include <stdio.h>
#include <stdlib.h> 
#include <string.h>

#include <pyas/queue.h>
#include <pyas/list.h>
#include <pyas/regexp.h>

int main(int argc, char *argv[]) {
    char *end = NULL;
    int is_match = 0;
    fifo *char_fifo;
    list_t char_list = list_new();

    if (argc < 3) {
        fprintf(stderr, "Usage:\n\t%s regexp text\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    char *arg = argv[1];
    
    char_fifo = char_to_queue(arg);

    char_list = fifo_to_list(char_fifo);
    
    is_match = re_match(char_list, argv[2], &end);

    if (is_match) {
        printf("The start of '%s' is in %s, %s: '%s'.\n", argv[2], argv[1], *end ? "next" : "END", end);
    } else {
        printf("The start of '%s' is *NOT* in %s.\n", argv[2], argv[1]);
    }

    fifo_delete(&char_fifo);
    //list_free(&char_list);

    exit(EXIT_SUCCESS);
}
