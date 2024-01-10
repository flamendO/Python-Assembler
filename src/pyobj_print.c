
#include <assert.h>
#include <stdio.h>
#include <stdlib.h> 
#include <string.h>

#include <pyas/queue.h>
#include <pyas/list.h>
#include <pyas/regexp.h>
#include <pyas/lexem.h>
#include <pyas/lexem_type.h>
#include <pyas/lexer_code.h>
#include <pyas/pyobj_print.h>

void pyobj_print(pyobj_t objet){

    printf("Pyobj : \n");
    printf("  pycodeblock :\n");
    printf("    header :\n");
    printf("      arg_count : %u\n",objet->py.codeblock->header.arg_count);
    printf("      local_count : %u\n",objet->py.codeblock->header.local_count);
    printf("      stack_size : %u\n",objet->py.codeblock->header.stack_size);
    printf("      flags : 0x%u\n",objet->py.codeblock->header.flags);
    printf("    binary :\n");
    printf("      header :\n");
    printf("        magic : %u\n", objet->py.codeblock->binary.header.magic);
    time_t temps = time(NULL);
    printf("        timestamp : %ld\n", temps);
    printf("        source_size : %u\n", objet->py.codeblock->binary.header.source_size);
    printf("        content : \n");
    printf("        interned :\n");
    interned_pyobj_print(objet);
    printf("/// Manque de temps pour terminer cette fonction\n");
}

void interned_pyobj_print(pyobj_t objet){
    int j = objet->py.codeblock->binary.content.interned->py.list.size;
    printf("          pyobj_t list\n");
    for(int i = 0; i < j; i++ ){
        printf("            element %i : %s\n",i+1,objet->py.codeblock->binary.content.interned->py.list.value[i]->py.string.buffer);
    }
}