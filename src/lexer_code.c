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

void removeSpaces(char *str){
    int count = 0;
    for (int i = 0; str[i]; i++)
        if (str[i] != ' ')
            str[count++] = str[i];
    str[count] = '\0';
}


list_t lex(char* regexp_file, char* source_file){
    FILE * fichier= fopen(source_file, "r");
    char ligne_texte_asm[1024];
    fgets(ligne_texte_asm,1024,fichier);
    list_t lexems_du_code_asm=list_new();
    fifo * file_des_lexems=fifo_new();
    int ligne_actuel=1;
    char* end=NULL;
    char* save_end=strdup(ligne_texte_asm);
    list_t regexp_list = list_new();
    regexp_list=lex_read(regexp_file);
    list_t p = list_new();
    p=regexp_list;
    int matching=0;
    while(!feof(fichier)){
        int success=0;
        while(p!=NULL && (*(save_end)!='\0')){
            matching=re_match(((lexem_type_t)(p->content))->l_value, save_end, &end);
            if(matching){
                lexem_t couple=calloc(1,sizeof(couple_type_lex));//contient le couple type et lexem
                success=1;

                couple->type=((lexem_type_t)(p->content))->type;
                removeSpaces(couple->type);
                //ligne où se situe le lexeme
                couple->line=ligne_actuel;

                //column de debut du léxeme
                couple->column=save_end-ligne_texte_asm;
              

                couple->value=calloc(end-save_end,sizeof(char));

                for(int i=0;i<end-save_end; i++){
                    couple->value[i]=*(save_end+i);
                }
                fifo_enqueue(file_des_lexems,(lexem_t)couple);
                
                p=regexp_list;
                save_end=end;
                end=NULL;
            }
            else{
                p=p->next;
            }
            
            

        
    }

    if(strcmp(save_end,"\0")){
        success=0;
    }

    if(!success){
        char* j=strdup(ligne_texte_asm);
        int col=0;
        while(j<save_end){
            col++; 
            j++;  
        }

        printf("Aucun lexeme n'est reconnaissable à partir de la colonne %d de la ligne %d \n",col,ligne_actuel);
        return NULL;
    }



    fgets(ligne_texte_asm,1024,fichier);
    ligne_actuel++;
    end=NULL;
    save_end=strdup(ligne_texte_asm);
    p=regexp_list;
    }

   
    lexems_du_code_asm=fifo_to_list(file_des_lexems);
    return lexems_du_code_asm;
}
