#include <assert.h>
#include <stdio.h>
#include <stdlib.h> 
#include <string.h>

#include <pyas/queue.h>
#include <pyas/list.h>
#include <pyas/regexp.h>
#include <pyas/chargroup.h>

int main ( int argc, char *argv[] ) { 
  char     *end = NULL; 
  int  is_match; 
  fifo * char_fifo;
  list_t char_list; 
  

    if (argc < 3) {
        fprintf(stderr, "Usage :\n\t%s regexp text\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    char *arg = argv[1];
    char_fifo = char_to_queue(arg);
    char_group * g1=(char_group *)fifo_dequeue(char_fifo);
    int p;
    for (p=0; p<256;p++){
        if (g1->characters[p]==1)
        printf("Le caractère %c à pour code ASCII %d \n",(char)p,p);
    }
    int k=g1->complement;
    if(k==1){
        printf("Il y a négation \n");
    }
    else {
        printf("Il n'y a pas négation \n");
    }
    char_list = fifo_to_list(char_fifo);
    char_group * g2=(char_group *)(char_list->content);
    int q;
    for (q=0; q<256;q++){
        if (g1->characters[q]==1)
        printf("Le caractère %c à pour code ASCII %d \n",(char)q,q);
    }
    int r=g2->complement;
    if(r==1){
        printf("Il y a négation \n");
    }
    else {
        printf("Il n'y a pas négation \n");
    }
}







    // is_match = re_match(char_list, argv[2], &end);

    // if ( is_match ) {
    //     printf( "The start of '%s' is in %s, %s: '%s'.\n", argv[2], argv[ 1 ], *end ? "next" : "END", end );
    // }
    // else {
    //     printf( "The start of '%s' is *NOT* in %s.\n", argv[2], argv[ 1 ] );
    // }

    // exit( EXIT_SUCCESS );


