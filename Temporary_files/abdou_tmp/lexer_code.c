#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pyas/regexp.h>
#include <pyas/lexem.h>
#include <pyas/list.h>
#include <pyas/queue.h>
#include <pyas/lexem_type.h>
#include <pyas/lexer_code.h>


list_t lex(char* regexp_file, char* source_file){
    FILE * fichier_counter = fopen(source_file, "r"); //sert juste à compter le nombre de 
    // de caracteres du texte asm pour pouvoir bien allouer le_texte_asm
    char c_counter;

    //NOMBRE DE CARACTERES DU TEXTE ASM
    int nb_caracters=0; //va contenir le nombre de caracteres du fichier
    while(c_counter!=EOF){
        c_counter=fgetc(fichier_counter);
        nb_caracters++;
    }
    fclose(fichier_counter);
    FILE * fichier= fopen(source_file, "r");
    char* le_texte_asm=calloc(nb_caracters, sizeof(char));

    int indice=0;
    while(indice<nb_caracters-1){

        le_texte_asm[indice]=fgetc(fichier);;
        indice++;
    }

    list_t lexems_du_code_asm=list_new();
    fifo * file_des_lexems=fifo_new();
    char** end=NULL;
    char** save_end=end;
    list_t regexp_list=lex_read(regexp_file);
    
    link_t * p=regexp_list;
    while(p!=NULL){
        couple_type_lex_t couple;//contient le couple type et lexem
        couple->ligne=1;
        couple->colonne=0;
        int success=0;
        if(re_match(((lexem_type_t)(p->content))->l_value, le_texte_asm, end) && success==0){
            success=1;
            couple->type=((lexem_type_t)(p->content))->type;
            //ligne où se situe le lexeme
            int j=0;
            while(j<**save_end){
                if((int)le_texte_asm[j]==10){ // 10 correspond au code ascii du retour à la ligne
                    couple->ligne++;
                    couple->colonne=-1;
                }
                j++;
                couple->colonne++;
                
            }
            couple->colonne++;
            // j=0;
            // int k=0;
            // while(j<**save_end && k<couple.ligne){
            //     if((int)le_texte_asm[j]==10){ // 10 correspond au code ascii du retour à la ligne
            //         k++;
            //     }
                
            // }

        // colonne où se situe le lexeme
            // couple.colonne=**save_end-j-1;
            // j++;
            // for(j=j;j<**save_end+1;j++){
            //     if((int)le_texte_asm[j]==9){ // 9 est le code ascii d'une tabulation
            //         couple.colonne=couple.colonne+3;
            //     }
            // }


            couple->lexem_in_code=calloc(*end-*save_end,sizeof(char));
            for(int i=0;i<*end-*save_end; i++){
                
                couple->lexem_in_code[i]=*(*save_end+i);
            }

            fifo_enqueue(file_des_lexems,(couple_type_lex_t)couple);

            
            p=regexp_list;
            save_end=end;
            
        }
        p=p->next;
        if(!success){
            //ligne où se situe le début de non matching
        //     int ligne=0;
        //     int j=0;

        //     while(j<**save_end){
        //         if((int)le_texte_asm[j]==10){ // 10 correspond au code ascii du retour à la ligne
        //             ligne++;
        //         }
        //         j++;
        //     }
        //     j=0;
        //     int k=0;
        //     while(j<**save_end && k<ligne){
        //         if((int)le_texte_asm[j]==10){ // 10 correspond au code ascii du retour à la ligne
        //             k++;
        //         }
                
        //     }

        // // colonne où se situe le lexeme
        //     int colonne=**save_end-j-1;
        //     j++;
        //     for(j=j;j<**save_end+1;j++){
        //         if((int)le_texte_asm[j]==9){ // 9 est le code ascii d'une tabulation
        //             colonne=colonne+3;
        //         }
        //     }


            printf("aucun lexme n'est reconnaissable à partir du colonne \n") ;// %d de la ligne %d \n",colonne,ligne);
        }

        
    }
    lexems_du_code_asm=fifo_to_list(file_des_lexems);
    return lexems_du_code_asm;
}


// void main(){
//     lexem_type_t group=lex_read("./include/test.conf");
//     list_print(group);

// }