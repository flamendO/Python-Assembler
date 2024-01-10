#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <pyas/chargroup.h>

char_group* new_char_group(){
  char_group * stock;
  stock=calloc(1,sizeof(char_group));
  stock->complement=0;
  stock->op=ONE_TIME;
  for(int i=0; i<128; i++){
    stock->characters[i]=0;
  }
  return stock;
} 

void copy_char_group(char_group* dest,char_group src){
  dest->complement=src.complement;
  dest->op=src.op;
  for(int j=0; j<128; j++){
    dest->characters[j]=src.characters[j];
  }
}