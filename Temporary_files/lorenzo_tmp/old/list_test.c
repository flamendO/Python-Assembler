//
//  list_test.c
//  Listes_chainees_dynamiques
//
//  Created by Lorenzo Azerine on 11/08/2023.
//

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "list.h"

int main(int argc, char *argv[]){
    list_t test = NULL ;
    test = list_regexp(argv[1]) ;
    printf("Chaine d'entrée : %s \n", argv[1]) ;
    list_print(test) ;
    return 0 ;
}
