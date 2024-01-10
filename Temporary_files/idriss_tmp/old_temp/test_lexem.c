#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pyas/chargroup.h>
#include <pyas/lexem.h>
#include <pyas/list.h>
#include <pyas/queue.h>
#include <unitest/unitest.h>


int main(int argc, char *argv[]){
    char *file_lex=argv[1];
    list_t l=list_new();
    l=lex_def(file_lex);
    link_t *p;
    p=l;
    while (p!=NULL){
        lexem_print(p->content);
        p=p->next;
    }
}