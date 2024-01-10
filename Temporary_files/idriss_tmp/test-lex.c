/**
 * @file test-lex.c
 * @author François Cayre <cayre@uvolante.org>
 * @date Sun Aug  7 21:22:53 2022
 * @brief units test for lex. 
 *
 * Unit tests for lex. 
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pyas/lexem_type.h>
#include <pyas/lexem.h>
#include <unitest/unitest.h>


// La fonction lex n'est pas encore achevé
// A réadapter car il faut travailler sur des fichiers .pys et non .py



void test_basic_lexem1(){

  lexem_type_t lex_defs = lex_read('test_lex_def.conf');
  list_t lex = lex(lex_defs, "python_test_folder/pys_folder/1.pys");
  test_assert(list_length(lex)==122, "Le nombre de lexèmes est de 122");
  //Créer un tableau de char de comparaison
  lexem_t lex_expected [] = {
    {"\n+", "newline", 1, 0},
    
    {"\n+", "newline", 2, 0},

    {"# Start pyc-objdump output", "comment", 3, 0},
    {"\n+", "newline", 3, 26},

    {"\n+", "newline", 4, 0},

    {".set", "dir::set", 5, 0},
    {"[ \t]+","blank",5,4},
    {"version_pyvm","version_pyvm",5,5},
    {"[ \t]+", "blank", 5, 17},
    {"62211", "interger::dec", 5, 21},
    {"\n+", "newline", 5, 26},

    {".set", "dir::set", 6, 0},
    {"[ \t]+","blank",6,4},
    {"flags","flags",6,5},
    {"[ \t]+", "blank", 6, 10},
    {"0x00000040", "integer::hex", 6, 17},
    {"\n+", "newline", 6, 27}, 

    {".set", "dir::set", 7, 0},
    {"[ \t]+","blank",7,4},
    {"filename","filename",7,5},
    {"[ \t]+", "blank", 7, 13},
    {'"3.py"', "str", 7, 21},
    {"\n+", "newline", 7, 27}, 

    {".set", "dir::set", 8, 0},
    {"[ \t]+","blank",8,4},
    {"name","names",8,5},
    {"[ \t]+", "blank", 8, 9},
    {'"<module>"', "str", 8, 17},
    {"\n+", "newline", 8, 28}, 

    {".set", "dir::set", 9, 0},
    {"[ \t]+","blank",9,4},
    {"stack_size","stack_size",9,5},
    {"[ \t]+", "blank", 9, 15},
    {"1", "integer::dec", 9, 21},
    {"\n+", "newline", 9, 23}, 

    {".set", "dir::set", 10, 0},
    {"[ \t]+","blank",10,4},
    {"arg_count","arg_count",10,5},
    {"[ \t]+", "blank", 10, 14},
    {"0", "integer::dec", 10, 21},
    {"\n+", "newline", 10, 22}, 

    {"\n+", "newline", 11, 0},

    {".interned","dir::interned",12,0},
    {"\n+", "newline", 12, 9}, 

    {"[ \t]+","blank",13,0},
    {'"a"', "str", 13, 4},
    {"\n+", "newline", 13, 7}, 

    {"[ \t]+","blank",14,0},
    {'"<module>"', "str", 14, 4},
    {"\n+", "newline", 14, 14}, 

    {"\n+", "newline", 15, 0},

    {".consts","dir::consts",16,0}, 
    {"\n+", "newline", 16, 7},

    {"[ \t]+","blank",17,0},
    {"1", "interger::dec", 17, 4},
    {"\n+", "newline", 17, 5},

    {"[ \t]+","blank",18,0},
    {"None", "identifier", 18, 4},
    {"\n+", "newline", 18, 8},

    {"\n+", "newline", 19, 0},

    {".names","dir::names",20,0}, 
    {"\n+", "newline", 20, 6},

    {"[ \t]+","blank",21,0},
    {'"a"', "str", 21, 4},
    {"\n+", "newline", 21, 7},

    {"\n+","newline",22,0},

    {".text","dir::text",23,0},
    {"\n+","newline",23,5},

    {".line","dir::text",24,0},
    {"[ \t]+","blank",24,5},
    {"3","interger::dec",24,6},
    {"\n+","newline",24,7},

    {"[ \t]+", "blank",25,0},
    {"LOAD_CONST","insn::0::LOAD_CONST",25,4}
    {"[ \t]+", "blank",25,14},
    {"0","interger::dec",25,26},
    {"[ \t]+", "blank",25,27},
    {'# 1', "comment",25,28},
    {"\n+","newline",25,31},

    {"[ \t]+", "blank",26,0},
    {"STORE_NAME","insn::0::STORE_NAME",26,4}
    {"[ \t]+", "blank",26,14},
    {"0","interger::dec",26,26},
    {"[ \t]+", "blank",26,27},
    {'# "a"', "comment",26,28},
    {"\n+","newline",26,33},

    {".line","dir::text",27,0},
    {"[ \t]+","blank",27,5},
    {"4","interger::dec",27,6},
    {"\n+","newline",27,7},

    {"[ \t]+", "blank",28,0},
    {"LOAD_NAME","insn::0::LOAD_NAME",28,4}
    {"[ \t]+", "blank",28,13},
    {"0","interger::dec",28,26},
    {"[ \t]+", "blank",28,27},
    {'# "a"', "comment",28,28},
    {"\n+","newline",28,33},

    {"[ \t]+", "blank",29,0},
    {"PRINT_ITEM","insn::0::PRINT_ITEM",29,4}
    {"[ \t]+", "blank",29,14},
    {"\n+","newline",29,26},

    {"[ \t]+", "blank",30,0},
    {"PRINT_NEWLIN","insn::0::PRINT_NEWLINE",30,4}
    {"[ \t]+", "blank",30,17},
    {"\n+","newline",30,26},

    {"[ \t]+", "blank",31,0},
    {"LOAD_CONST","insn::0::LOAD_CONST",31,4}
    {"[ \t]+", "blank",31,14},
    {"1","interger::dec",31,26},
    {"[ \t]+", "blank",31,27},
    {'# None', "comment",31,28},
    {"\n+","newline",31,34},

    {"[ \t]+", "blank",32,0},
    {"RETURN_VALUE","insn::0::RETURN_VALUE",32,4}
    {"[ \t]+", "blank",32,16},
    {"\n+","newline",32,26},

    {"\n+","newline",33,0},

    {"# Disassembled Mon Oct  9 14:39:57 2023", "comment", 34, 0},
    {"\n+","newline",34,39},

    {"\n+","newline",35,0},


};
  //Comparaison de la liste lex, lexème par lexème
  link_t *p=lex;
  int i=0;
  while (p!=NULL){
    test_assert (strcmp(p->content->value,lex_expected[0][i])==0, "Verification des valeurs de lex");
    test_assert (strcmp(p->content->value,lex_expected[1][i])==0, "Verification des types de lex");
    test_assert (strcmp(p->content->value,lex_expected[2][i])==0, "Verification des lignes de lex");
    test_assert (strcmp(p->content->value,lex_expected[3][i])==0, "Verification des colonnes de lex");
    i=i+1;
    p=p->next;
  }

}
void test_basic_lexem2(){

  lexem_type_t lex_defs = lex_read('test_lex_def.conf');
  list_t lex = lex(lex_defs, "python_test_folder/pys_folder/2.pys");
  test_assert(list_length(lex)==167, "Le nombre de lexèmes est de 167");
  //Créer un tableau de char de comparaison
  lexem_t lex_expected [] = {
    {"\n+", "newline", 1, 0},

    {"\n+", "newline", 2, 0},

    {"# Start pyc-objdump output", "comment", 3, 0},
    {"\n+", "newline", 3, 26},

    {"\n+", "newline", 4, 0},

    {".set", "dir::set", 5, 0},
    {"[ \t]+","blank",5,4},
    {"version_pyvm","version_pyvm",5,5},
    {"[ \t]+", "blank", 5, 17},
    {"62211", "interger::dec", 5, 21},
    {"\n+", "newline", 5, 26},

    {".set", "dir::set", 6, 0},
    {"[ \t]+","blank",6,4},
    {"flags","flags",6,5},
    {"[ \t]+", "blank", 6, 10},
    {"0x00000040", "integer::hex", 6, 17},
    {"\n+", "newline", 6, 27}, 

    {".set", "dir::set", 7, 0},
    {"[ \t]+","blank",7,4},
    {"filename","filename",7,5},
    {"[ \t]+", "blank", 7, 13},
    {'"2.py"', "str", 7, 21},
    {"\n+", "newline", 7, 27}, 

    {".set", "dir::set", 8, 0},
    {"[ \t]+","blank",8,4},
    {"name","names",8,5},
    {"[ \t]+", "blank", 8, 9},
    {'"<module>"', "str", 8, 17},
    {"\n+", "newline", 8, 28}, 

    {".set", "dir::set", 9, 0},
    {"[ \t]+","blank",9,4},
    {"stack_size","stack_size",9,5},
    {"[ \t]+", "blank", 9, 15},
    {"2", "integer::dec", 9, 21},
    {"\n+", "newline", 9, 23}, 

    {".set", "dir::set", 10, 0},
    {"[ \t]+","blank",10,4},
    {"arg_count","arg_count",10,5},
    {"[ \t]+", "blank", 10, 14},
    {"0", "integer::dec", 10, 21},
    {"\n+", "newline", 10, 22}, 

    {"\n+", "newline", 11, 0},

    {".interned","dir::interned",12,0},
    {"\n+", "newline", 12, 9},   

    {"[ \t]+","blank",13,0},
    {'"a"', "str", 13, 4},
    {"\n+", "newline", 13, 7},

    {"[ \t]+","blank",14,0},
    {'"b"', "str", 14, 4},
    {"\n+", "newline", 14, 7},

    {"[ \t]+","blank",15,0},
    {'"c"', "str", 15, 4},
    {"\n+", "newline", 15, 7}, 

    {"[ \t]+","blank",16,0},
    {'"<module>"', "str", 16, 4},
    {"\n+", "newline", 16, 14}, 

    {"\n+", "newline", 17, 0},

    {".consts","dir::consts",18,0}, 
    {"\n+", "newline", 18, 7},

    {"[ \t]+","blank",19,0},
    {"3", "interger::dec", 19, 4},
    {"\n+", "newline", 19, 5},

    {"[ \t]+","blank",20,0},
    {"4", "interger::dec", 20, 4},
    {"\n+", "newline", 20, 5},

    {"[ \t]+","blank",21,0},
    {"None", "identifier", 21, 4},
    {"\n+", "newline", 21, 8},

    {"\n+", "newline", 22, 0},

    {".names","dir::names",23,0},
    {"\n+", "newline", 23, 6}, 

    {"[ \t]+","blank",24,0},
    {'"a"', "str", 24, 4},
    {"\n+", "newline", 24, 7},

    {"[ \t]+","blank",25,0},
    {'"b"', "str", 25, 4},
    {"\n+", "newline", 25, 7},

    {"[ \t]+","blank",26,0},
    {'"c"', "str", 26, 4},
    {"\n+", "newline", 26, 7},

    {"\n+","newline",27,0},

    {".text","dir::text",28,0},
    {"\n+","newline",28,5},

    {".line","dir::text",29,0},
    {"[ \t]+","blank",29,5},
    {"1","interger::dec",29,6},
    {"\n+","newline",29,7},

    {"[ \t]+", "blank",30,0},
    {"LOAD_CONST","insn::0::LOAD_CONST",30,4}
    {"[ \t]+", "blank",30,14},
    {"0","interger::dec",30,26},
    {"[ \t]+", "blank",30,27},
    {'# 3', "comment",30,28},
    {"\n+","newline",30,31},

    {"[ \t]+", "blank",31,0},
    {"STORE_NAME","insn::0::STORE_NAME",31,4}
    {"[ \t]+", "blank",31,14},
    {"0","interger::dec",31,26},
    {"[ \t]+", "blank",31,27},
    {"#", "comment",31,28},
    {"[ \t]+", "blank",31,29},
    {'# "a"', "comment",31,30}, //attention !
    {"\n+","newline",31,33},

    {".line","dir::text",32,0},
    {"[ \t]+","blank",32,5},
    {"2","interger::dec",32,6},
    {"\n+","newline",32,7},

    {"[ \t]+", "blank",33,0},
    {"LOAD_CONST","insn::0::LOAD_CONST",33,4}
    {"[ \t]+", "blank",33,14},
    {"1","interger::dec",33,26},
    {"[ \t]+", "blank",33,27},
    {'# 4', "comment",33,28},
    {"\n+","newline",33,31},
    
    {"[ \t]+", "blank",34,0},
    {"STORE_NAME","insn::0::STORE_NAME",34,4}
    {"[ \t]+", "blank",34,14},
    {"1","interger::dec",34,26},
    {"[ \t]+", "blank",34,27},
    {"#", "comment",34,28},
    {"[ \t]+", "blank",34,29},
    {'# "b"', "comment",34,30}, 
    {"\n+","newline",34,33},

    {".line","dir::text",35,0},
    {"[ \t]+","blank",35,5},
    {"3","interger::dec",35,6},
    {"\n+","newline",35,7},

    {"[ \t]+", "blank",36,0},
    {"LOAD_NAME","insn::0::LOAD_NAME",36,4}
    {"[ \t]+", "blank",36,13},
    {"0","interger::dec",36,26},
    {"[ \t]+", "blank",36,27},
    {'# "a"', "comment",36,28},
    {"\n+","newline",36,33},
  
    {"[ \t]+", "blank",37,0},
    {"LOAD_NAME","insn::0::LOAD_NAME",37,4}
    {"[ \t]+", "blank",37,13},
    {"1","interger::dec",37,26},
    {"[ \t]+", "blank",37,27},
    {'# "b"', "comment",37,28},
    {"\n+","newline",37,33},

    {"[ \t]+", "blank",38,0},
    {"BINARY_ADD","insn::0::BINARY_ADD",38,4}
    {"[ \t]+", "blank",38,14},
    {"\n+","newline",38,26},

    {"[ \t]+", "blank",39,0},
    {"STORE_NAME","insn::0::STORE_NAME",39,4}
    {"[ \t]+", "blank",39,14},
    {"2","interger::dec",39,26},
    {"[ \t]+", "blank",39,27},
    {'# "c"', "comment",39,28},
    {"\n+","newline",39,33},

    {"[ \t]+", "blank",40,0},
    {"LOAD_CONST","insn::0::LOAD_CONST",40,4}
    {"[ \t]+", "blank",40,14},
    {"1","interger::dec",40,26},
    {"[ \t]+", "blank",40,27},
    {"# None", "comment",40,28},
    {"\n+","newline",40,34},

    {"[ \t]+", "blank",41,0},
    {"RETURN_VALUE","insn::0::RETURN_VALUE",41,4}
    {"[ \t]+", "blank",41,16},
    {"\n+","newline",41,26},

    {"\n+","newline",42,0},

    {"# Disassembled Mon Oct  9 15:06:09 2023", "comment", 43, 0},
    {"\n+","newline",43,39},

    {"\n+","newline",44,0},


};
  //Comparaison de la liste lex, lexème par lexème
  link_t *p=lex;
  int i=0;
  while (p!=NULL){
    test_assert (strcmp(p->content->value,lex_expected[0][i])==0, "Verification des valeurs de lex");
    test_assert (strcmp(p->content->value,lex_expected[1][i])==0, "Verification des types de lex");
    test_assert (strcmp(p->content->value,lex_expected[2][i])==0, "Verification des lignes de lex");
    test_assert (strcmp(p->content->value,lex_expected[3][i])==0, "Verification des colonnes de lex");
    i=i+1;
    p=p->next;
  }

}

void test_basic_lexem3(){

  lexem_type_t lex_defs = lex_read('test_lex_def.conf');
  list_t lex = lex(lex_defs, "python_test_folder/pys_folder/3.pys");
  test_assert(list_length(lex)==102, "Le nombre de lexèmes est de 102");
  //Créer un tableau de char de comparaison
  lexem_t lex_expected [] = {
    {"\n+", "newline", 1, 0},

    {"\n+", "newline", 2, 0},

    {"# Start pyc-objdump output", "comment", 3, 0},
    {"\n+", "newline", 3, 26},

    {"\n+", "newline", 4, 0},
    {".set", "dir::set", 5, 0},
    {"[ \t]+","blank",5,4},
    {"version_pyvm","version_pyvm",5,5},
    {"[ \t]+", "blank", 5, 17},
    {"62211", "interger::dec", 5, 21},
    {"\n+", "newline", 5, 26},

    {".set", "dir::set", 6, 0},
    {"[ \t]+","blank",6,4},
    {"flags","flags",6,5},
    {"[ \t]+", "blank", 6, 10},
    {"0x00000040", "integer::hex", 6, 17},
    {"\n+", "newline", 6, 27}, 

    {".set", "dir::set", 7, 0},
    {"[ \t]+","blank",7,4},
    {"filename","filename",7,5},
    {"[ \t]+", "blank", 7, 13},
    {'"3.py"', "str", 7, 21},
    {"\n+", "newline", 7, 27}, 

    {".set", "dir::set", 8, 0},
    {"[ \t]+","blank",8,4},
    {"name","names",8,5},
    {"[ \t]+", "blank", 8, 9},
    {'"<module>"', "str", 8, 17},
    {"\n+", "newline", 8, 28}, 

    {".set", "dir::set", 9, 0},
    {"[ \t]+","blank",9,4},
    {"stack_size","stack_size",9,5},
    {"[ \t]+", "blank", 9, 15},
    {"1", "integer::dec", 9, 21},
    {"\n+", "newline", 9, 23}, 

    {".set", "dir::set", 10, 0},
    {"[ \t]+","blank",10,4},
    {"arg_count","arg_count",10,5},
    {"[ \t]+", "blank", 10, 14},
    {"0", "integer::dec", 10, 21},
    {"\n+", "newline", 10, 22}, 

    {"\n+", "newline", 11, 0},

    {".interned","dir::interned",12,0},
    {"\n+", "newline", 12, 9},   

    {"[ \t]+","blank",13,0},
    {'"<module>"', "str", 13, 4},
    {"\n+", "newline", 13, 14},

    {"[ \t]+","blank",14,0},
    {'""', "str", 14, 4},
    {"\n+", "newline", 14, 6},  

    {"\n+", "newline", 15, 0},

    {".consts","dir::consts",16,0}, 
    {"\n+", "newline", 16, 7},

    {"[ \t]+","blank",17,0},
    {"13", "interger::dec", 17, 4},
    {"\n+", "newline", 17, 6},

    {"[ \t]+","blank",18,0},
    {"None", "identifier", 18, 4},
    {"\n+", "newline", 18, 8},

    {"\n+", "newline", 19, 0},

    {".text","dir::text",20,0},
    {"\n+","newline",20,5},

    {".line","dir::text",21,0},
    {"[ \t]+","blank",21,5},
    {"2","interger::dec",21,6},
    {"\n+","newline",21,7},

    {"[ \t]+", "blank",22,0},
    {"LOAD_CONST","insn::0::LOAD_CONST",22,4}
    {"[ \t]+", "blank",22,14},
    {"0","interger::dec",22,26},
    {"[ \t]+", "blank",22,27},
    {'# 13', "comment",22,28},
    {"\n+","newline",22,33},

    {"[ \t]+", "blank",23,0},
    {"PRINT_ITEM","insn::0::PRINT_ITEM",23,4}
    {"[ \t]+", "blank",23,14},
    {"\n+","newline",23,26},

    {"[ \t]+", "blank",24,0},
    {"PRINT_NEWLINE","insn::0::PRINT_NEWLINE",24,4}
    {"[ \t]+", "blank",24,17},
    {"\n+","newline",24,26},

    {"[ \t]+", "blank",25,0},
    {"LOAD_CONST","insn::0::LOAD_CONST",25,4}
    {"[ \t]+", "blank",25,14},
    {"1","interger::dec",25,26},
    {"[ \t]+", "blank",25,27},
    {'# None', "comment",25,28},
    {"\n+","newline",25,34},

    {"[ \t]+", "blank",26,0},
    {"RETURN_VALUE","insn::0::RETURN_VALUE",26,4}
    {"[ \t]+", "blank",26,16},
    {"\n+","newline",26,26},

    {"\n+","newline",27,0},

    {"# Disassembled Mon Oct  9 15:06:21 2023", "comment", 28, 0},
    {"\n+","newline",28,39},

    {"\n+","newline",29,0},

};
  //Comparaison de la liste lex, lexème par lexème
  link_t *p=lex;
  int i=0;
  while (p!=NULL){
    test_assert (strcmp(p->content->value,lex_expected[0][i])==0, "Verification des valeurs de lex");
    test_assert (strcmp(p->content->value,lex_expected[1][i])==0, "Verification des types de lex");
    test_assert (strcmp(p->content->value,lex_expected[2][i])==0, "Verification des lignes de lex");
    test_assert (strcmp(p->content->value,lex_expected[3][i])==0, "Verification des colonnes de lex");
    i=i+1;
    p=p->next;
  }

}

void test_comment(){
  
  lexem_type_t lex_defs = lex_read('test_lex_def.conf');
  list_t lex = lex(lex_defs, "python_test_folder/py_folder/4.pys");
  lexem_t lex_expected [] = {
    {"# Start pyc-objdump output", "comment", 3, 0},
    {'# 1', "comment", 28, 28},
    {'# "a"', "comment", 29, 28},
    {'# 2', "comment", 31, 28},
    {'# b', "comment", 32, 28},
    {'# "a"', "comment", 34, 28},
    {'# "b"', "comment", 35, 28},
    {'# ">"', "comment", 36, 28},
    {'# "a"', "comment", 39, 28},
    {'# "b"', "comment", 45, 28},
    {'# None', "comment", 49, 28},
    {"# Disassembled Mon Oct 16 15:33:12 2023", "comment", 52, 28},
  };
  //Comparaison des comments obtenues
  link_t *p=lex;
  int i=0;
  while (p!=NULL){
    if (p->content->type=="comment"){
   test_assert (strcmp(p->content->value,lex_expected[0][i])==0, "Verification des valeurs de lex");
    test_assert (strcmp(p->content->value,lex_expected[2][i])==0, "Verification des lignes de lex");
    test_assert (strcmp(p->content->value,lex_expected[3][i])==0, "Verification des colonnes de lex");
    i=i+1;
    }
  p=p->next;
  }
  }


void test_newline(){
  
  lexem_type_t lex_defs = lex_read('test_lex_def.conf');
  list_t lex = lex(lex_defs, "python_test_folder/py_folder/5.pys");
  lexem_t lex_expected [] = {
    {"\n+", "newline", 1, 0},
    {"\n+", "newline", 2, 0},
    {"\n+", "newline", 3, 26},
    {"\n+", "newline", 4, 0},
    {"\n+", "newline", 5, 26},
    {"\n+", "newline", 6, 27}, 
    {"\n+", "newline", 7, 27}, 
    {"\n+", "newline", 8, 27}, 
    {"\n+", "newline", 9, 23},
    {"\n+", "newline", 10, 22}, 
    {"\n+", "newline", 11, 0},
    {"\n+", "newline", 12, 9}, 
    {"\n+", "newline", 13, 7}, 
    {"\n+", "newline", 14, 11}, 
    {"\n+", "newline", 15, 7},
    {"\n+", "newline", 16, 14},  
    {"\n+", "newline", 17, 0},
    {"\n+", "newline", 18, 7},
    {"\n+", "newline", 19, 5},
    {"\n+", "newline", 20, 5},
    {"\n+", "newline", 21, 5},
    {"\n+", "newline", 22, 8},
    {"\n+", "newline", 23, 8},
    {"\n+", "newline", 24, 0},
    {"\n+", "newline", 25, 6},
    {"\n+", "newline", 26, 7}, 
    {"\n+", "newline", 27, 11}, 
    {"\n+", "newline", 28, 7},
    {"\n+","newline",29,0},
    {"\n+","newline",30,5},
    {"\n+","newline",31,7},
    {"\n+", "newline", 32, 31},
    {"\n+", "newline", 33, 33},
    {"\n+", "newline", 34, 7}, 
    {"\n+", "newline", 35, 33}, 
    {"\n+", "newline", 36, 37},
    {"\n+","newline",37,31},
    {"\n+","newline",38,27},
    {"\n+","newline",39,26},
    {"\n+", "newline", 40, 8},
    {"\n+", "newline", 41, 33},
    {"\n+", "newline", 42, 33}, 
    {"\n+", "newline", 43, 7}, 
    {"\n+", "newline", 44, 33},
    {"\n+","newline",45,33},
    {"\n+","newline",46,31},
    {"\n+","newline",47,26},
    {"\n+", "newline",48,26},
    {"\n+", "newline",49,33},
    {"\n+", "newline",50,33}, 
    {"\n+", "newline",51,8}, 
    {"\n+", "newline",52,26},
    {"\n+","newline",53,7},
    {"\n+","newline",54,8},
    {"\n+","newline",55,34},
    {"\n+", "newline",56,26},
    {"\n+", "newline",57,26}, 
    {"\n+", "newline",58,34}, 
    {"\n+", "newline",59,26},
    {"\n+","newline",60,0},
    {"\n+","newline",61,39},
    {"\n+","newline",62,0},
    {"\n+","newline",63,0},
  };
  //Comparaison des newlines obtenues
  link_t *p=lex;
  int i=0;
  while (p!=NULL){
    if (p->content->type=="newline"){
   test_assert (strcmp(p->content->value,lex_expected[0][i])==0, "Verification des valeurs de lex");
    test_assert (strcmp(p->content->value,lex_expected[2][i])==0, "Verification des lignes de lex");
    test_assert (strcmp(p->content->value,lex_expected[3][i])==0, "Verification des colonnes de lex");
    i=i+1;
    }
  p=p->next;
  }
  }

void test_blank(){
    lexem_type_t lex_defs = lex_read('test_lex_def.conf');
    list_t lex = lex(lex_defs, "python_test_folder/pys_folder/5.pys");
    lexem_t lex_expected[] = {
    {"[ \t]+", "blank", 5, 4},
    {"[ \t]+", "blank", 5, 17},
    {"[ \t]+", "blank", 7, 4},
    {"[ \t]+", "blank", 7, 10},
    {"[ \t]+", "blank", 9, 4},
    {"[ \t]+", "blank", 9, 13},
    {"[ \t]+", "blank", 10, 4},
    {"[ \t]+", "blank", 10, 9},
    {"[ \t]+", "blank", 11, 4},
    {"[ \t]+", "blank", 11, 15},
    {"[ \t]+", "blank", 12, 4},
    {"[ \t]+", "blank", 12, 14},
    {"[ \t]+", "blank", 15, 0},
    {"[ \t]+", "blank", 16, 0},
    {"[ \t]+", "blank", 17, 0},
    {"[ \t]+", "blank", 18, 0},
    {"[ \t]+", "blank", 21, 0},
    {"[ \t]+", "blank", 22, 0},
    {"[ \t]+", "blank", 23, 0},
    {"[ \t]+", "blank", 24, 0},
    {"[ \t]+", "blank", 25, 0},
    {"[ \t]+", "blank", 28, 5},
    {"[ \t]+", "blank", 29, 0},
    {"[ \t]+", "blank", 29, 14},
    {"[ \t]+", "blank", 29, 27},
    {"[ \t]+", "blank", 30, 0},
    {"[ \t]+", "blank", 30, 14},
    {"[ \t]+", "blank", 30, 27},
    {"[ \t]+", "blank", 31, 5},
    {"[ \t]+", "blank", 32, 0},
    {"[ \t]+", "blank", 32, 15},
    {"[ \t]+", "blank", 33, 0},
    {"[ \t]+", "blank", 33, 14},
    {"[ \t]+", "blank", 33, 27},
    {"[ \t]+", "blank", 34, 0},
    {"[ \t]+", "blank", 34, 14},
    {"[ \t]+", "blank", 34, 27},
    {"[ \t]+", "blank", 35, 0},
    {"[ \t]+", "blank", 35, 19},
    {"[ \t]+", "blank", 36, 0},
    {"[ \t]+", "blank", 39, 13},
    {"[ \t]+", "blank", 40, 0},
    {"[ \t]+", "blank", 40, 15},
    {"[ \t]+", "blank", 41, 0},
    {"[ \t]+", "blank", 41, 15},
    {"[ \t]+", "blank", 42, 0},
    {"[ \t]+", "blank", 42, 15},
    {"[ \t]+", "blank", 43, 0},
    {"[ \t]+", "blank", 44, 0},
    {"[ \t]+", "blank", 45, 0},
    {"[ \t]+", "blank", 45, 13},
    {"[ \t]+", "blank", 49, 5},
    {"[ \t]+", "blank", 51, 14},
    };
  link_t *p=lex;
  int i=0;
  while (p!=NULL){
    if (p->content->type=="blank"){
   test_assert (strcmp(p->content->value,lex_expected[0][i])==0, "Verification des valeurs de lex");
    test_assert (strcmp(p->content->value,lex_expected[2][i])==0, "Verification des lignes de lex");
    test_assert (strcmp(p->content->value,lex_expected[3][i])==0, "Verification des colonnes de lex");
    i=i+1;
    }
  p=p->next;
  }
  }


void test_str(){
  
  lexem_type_t lex_defs = lex_read('test_lex_def.conf');
  list_t lex = lex(lex_defs, "python_test_folder/py_folder/16.pys");
  lexem_t lex_expected [] = {
    {'"16.py"', "str", 7, 21},
    {'"<module>"', "str", 8, 17},
    {'"Bonjour, monde !"', "str", 19, 4},
    {'"La longueur de la chaîne de caractères est"', "str", 20, 4},
    {'"caractères."', "str", 21, 4},
    {'"texte"', "str", 25, 4},    
    {'"len"', "str", 26, 4},
    {'"longueur"', "str", 27, 4},       
  };
  link_t *p=lex;
  int i=0;
  while (p!=NULL){
    if (p->content->type=="str"){
   test_assert (strcmp(p->content->value,lex_expected[0][i])==0, "Verification des valeurs de lex");
    test_assert (strcmp(p->content->value,lex_expected[2][i])==0, "Verification des lignes de lex");
    test_assert (strcmp(p->content->value,lex_expected[3][i])==0, "Verification des colonnes de lex");
    i=i+1;
    }
  p=p->next;
  }
  }



void test_empty_lex(){
  
  lexem_type_t lex_defs = lex_read('test_lex_def.conf');
  list_t lex = lex(lex_defs, "python_test_folder/py_folder/22.pyc");
  test_assert (strcmp(lex==NULL=)==0, "Verifie si la liste lex est nulle");
}

void test_invalid_lex(){
  lexem_type_t lex_defs = lex_read('test_lex_def.conf');
  list_t lex1 = lex(lex_defs, "python_test_folder/py_folder/23.pyc");
  list_t lex2 = lex(lex_defs, "python_test_folder/py_folder/24.pyc");
  list_t lex3 = lex(lex_defs, "python_test_folder/py_folder/25.pyc");
  test_assert (strcmp(lex1==NULL=)==0, "Verifie si le 23.pys donne un lex nul");
  test_assert (strcmp(lex2==NULL=)==0, "Verifie si le 24.pys donne un lex nul");
  test_assert (strcmp(lex3==NULL=)==0, "Verifie si le 25.pys donne un lex nul");
}


void test_hard_lexem1(){

  lexem_type_t lex_defs = lex_read('test_lex_def.conf');
  list_t lex = lex(lex_defs, "python_test_folder/pys_folder/1.pys");
  test_assert(list_length(lex)==123, "Le nombre de lexèmes est de 123");
  //Créer un tableau de char de comparaison
  lexem_t lex_expected [] = {

};;
  // Comparaison de la liste lex, lexème par lexème
  link_t *p=lex;
  int i=0;
  while (p!=NULL){
    test_assert (strcmp(p->content->value,lex_expected[0][i])==0, "Verification des valeurs de lex");
    test_assert (strcmp(p->content->value,lex_expected[1][i])==0, "Verification des types de lex");
    test_assert (strcmp(p->content->value,lex_expected[2][i])==0, "Verification des lignes de lex");
    test_assert (strcmp(p->content->value,lex_expected[3][i])==0, "Verification des colonnes de lex");
    i=i+1;
    p=p->next;
  }

}


int main ( int argc, char *argv[] ) { 

    unit_test( argc, argv ); 
    
    // Tests sur des fichiers .pys simples
    test_suite( "test 1 - simple lexem" ); 
    test_basic_lexem1();
    test_suite( "test 2 - simple lexem" ); 
    test_basic_lexem2();
    test_suite( "test 3 - simple lexem" ); 
    test_basic_lexem3();
 
    // Test sur la détection de commentaires dans un fichier .pys
    test_suite( "test commentaires" ); 
    test_comment();
  
    // Test sur la détection de sauts de ligne dans un fichier .pys
    test_suite( "test newline" ); 
    test_newline();

    // Test sur la détection d'espaces ou/et de tabulations dans un fichier .pys
    test_suite( "test blank" ); 
    test_blank();

    // Test sur la détection de chaines de caractères (str) dans un fichier .pys
    test_suite( "test str" ); 
    test_str();

    // Test sur un fichier .pys vide
    test_suite( "test liste vide" ); 
    test_empty_lex();

    // Test sur un fichier .pys invalide (avec des lexèmes différents du .conf)
    test_suite( "test invalid lexem" ); 
    test_invalid_lex();

    // Tests sur des fichiers .pys complexes 
    test_suite( "test 1 - hard lexem" ); 
    test_hard_lexem1();
    test_suite( "test 2 - hard lexem" ); 
    test_hard_lexem2();
    test_suite( "test 3 - hard lexem" ); 
    test_hard_lexem3();
    test_suite( "test 4 - hard lexem" ); 
    test_hard_lexem4();


  exit( EXIT_SUCCESS ); 
}

