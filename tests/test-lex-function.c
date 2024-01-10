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
#include <pyas/regexp.h>
#include <pyas/lexem.h>
#include <pyas/list.h>
#include <pyas/queue.h>
#include <pyas/lexem_type.h>
#include <pyas/lexer_code.h>
#include <unitest/unitest.h>



void test_basic_lexem1(){

  list_t lex_test = lex("tests/the.conf", "tests/python_test_folder/pys_folder/1.pys");
  int a = list_length(lex_test);
  test_assert(a==120, "Le nombre de lexèmes est de 120");
  //Créer un tableau de char de comparaison
  struct lexem lex_attendu[] = {
    {"newline", "\n", 1, 0},
    {"newline", "\n", 2, 0},
    {"comment", "# Start pyc-objdump output", 3, 0},
    {"newline", "\n", 3, 26},
    {"newline", "\n", 4, 0},
    {"dir::set", ".set", 5, 0},
    {"blank", " ", 5, 4},
    {"version_pyvm", "version_pyvm", 5, 5},
    {"blank", "	 ", 5, 17},
    {"integer::dec", "62211", 5, 19},
    {"newline", "\n", 5, 24},
    {"dir::set", ".set", 6, 0},
    {"blank", " ", 6, 4},
    {"flags", "flags", 6, 5},
    {"blank", "		 ", 6, 10},
    {"integer::hex", "0x00000040", 6, 13},
    {"newline", "\n", 6, 23},
    {"dir::set", ".set", 7, 0},
    {"blank", " ", 7, 4},
    {"filename", "filename", 7, 5},
    {"blank", "		 ", 7, 13},
    {"string", "\"1.py\"", 7, 16},
    {"newline", "\n", 7, 22},
    {"dir::set", ".set", 8, 0},
    {"blank", " ", 8, 4},
    {"name", "name", 8, 5},
    {"blank", "		 ", 8, 9},
    {"string", "\"<module>\"", 8, 12},
    {"newline", "\n", 8, 22},
    {"dir::set", ".set", 9, 0},
    {"blank", " ", 9, 4},
    {"stack_size", "stack_size", 9, 5},
    {"blank", "		 ", 9, 15},
    {"integer::dec", "1", 9, 18},
    {"newline", "\n", 9, 19},
    {"dir::set", ".set", 10, 0},
    {"blank", " ", 10, 4},
    {"arg_count", "arg_count", 10, 5},
    {"blank", "		 ", 10, 14},
    {"integer::dec", "0", 10, 17},
    {"newline", "\n", 10, 18},
    {"newline", "\n", 11, 0},
    {"dir::interned", ".interned", 12, 0},
    {"newline", "\n", 12, 9},
    {"blank", "	", 13, 0},
    {"string", "\"a\"", 13, 1},
    {"newline", "\n", 13, 4},
    {"blank", "	", 14, 0},
    {"string", "\"<module>\"", 14, 1},
    {"newline", "\n", 14, 11},
    {"newline", "\n", 15, 0},
    {"dir::consts", ".consts", 16, 0},
    {"newline", "\n", 16, 7},
    {"blank", "	", 17, 0},
    {"integer::dec", "1", 17, 1},
    {"newline", "\n", 17, 2},
    {"blank", "	", 18, 0},
    {"pycst::None", "None", 18, 1},
    {"newline", "\n", 18, 5},
    {"newline", "\n", 19, 0},
    {"dir::names", ".names", 20, 0},
    {"newline", "\n", 20, 6},
    {"blank", "	", 21, 0},
    {"string", "\"a\"", 21, 1},
    {"newline", "\n", 21, 4},
    {"newline", "\n", 22, 0},
    {"dir::text", ".text", 23, 0},
    {"newline", "\n", 23, 5},
    {"dir::line", ".line", 24, 0},
    {"blank", " ", 24, 5},
    {"integer::dec", "3", 24, 6},
    {"newline", "\n", 24, 7},
    {"blank", "	", 25, 0},
    {"insn::0::LOAD_CONST", "LOAD_CONST", 25, 1},
    {"blank", "            ", 25, 11},
    {"integer::dec", "0", 25, 23},
    {"blank", "	", 25, 24},
    {"comment", "# 1", 25, 25},
    {"newline", "\n", 25, 28},
    {"blank", "	", 26, 0},
    {"insn::0::STORE_NAME", "STORE_NAME", 26, 1},
    {"blank", "            ", 26, 11},
    {"integer::dec", "0", 26, 23},
    {"blank", "	", 26, 24},
    {"comment", "# \"a\"", 26, 25},
    {"newline", "\n", 26, 30},
    {"dir::line", ".line", 27, 0},
    {"blank", " ", 27, 5},
    {"integer::dec", "4", 27, 6},
    {"newline", "\n", 27, 7},
    {"blank", "	", 28, 0},
    {"insn::0::LOAD_NAME", "LOAD_NAME", 28, 1},
    {"blank", "             ", 28, 10},
    {"integer::dec", "0", 28, 23},
    {"blank", "	", 28, 24},
    {"comment", "# \"a\"", 28, 25},
    {"newline", "\n", 28, 30},
    {"blank", "	", 29, 0},
    {"insn::0::PRINT_ITEM", "PRINT_ITEM", 29, 1},
    {"blank", "            ", 29, 11},
    {"newline", "\n", 29, 23},
    {"blank", "	", 30, 0},
    {"insn::0::PRINT_NEWLINE", "PRINT_NEWLINE", 30, 1},
    {"blank", "         ", 30, 14},
    {"newline", "\n", 30, 23},
    {"blank", "	", 31, 0},
    {"insn::0::LOAD_CONST", "LOAD_CONST", 31, 1},
    {"blank", "            ", 31, 11},
    {"integer::dec", "1", 31, 23},
    {"blank", "	", 31, 24},
    {"comment", "# None", 31, 25},
    {"newline", "\n", 31, 31},
    {"blank", "	", 32, 0},
    {"insn::0::RETURN_VALUE", "RETURN_VALUE", 32, 1},
    {"blank", "          ", 32, 13},
    {"newline","\n",32,23},
    {"newline", "\n", 33, 0},
    {"comment", "# Disassembled Mon Oct  9 14:39:57 2023", 34, 0},
    {"newline", "\n", 34, 39},
    {"newline", "\n", 35, 0},
};

  //Comparaison de la liste lex, lexème par lexème
  list_t p=lex_test;
  int i=0;
 
  while (p!=NULL){
    lexem_t lexem = (lexem_t)(p->content);
    // printf("line_column_test (%d,%d), line_column_excepted (%d,%d) \n",lexem->line,lexem->column,lex_attendu[i].line,lex_attendu[i].column);
    // printf("type_value_test (%s,%s), type_value_excepted (%s,%s) \n",lexem->type,lexem->value,lex_attendu[i].type,lex_attendu[i].value);
    test_assert (!strcmp(lexem->value,lex_attendu[i].value), "Verification des valeurs - itération n°%d",i+1);
    test_assert (!strcmp(lexem->type,lex_attendu[i].type), "Verification des types - itération n°%d",i+1);
    test_assert (lexem->line==lex_attendu[i].line, "Verification des lignes - itération n°%d",i+1);
    test_assert (lexem->column==lex_attendu[i].column, "Verification des colonnes - itération n°%d",i+1);
    i=i+1;
    p=p->next;
  }
  test_assert (p==NULL, "Vérifie si la liste est bien nulle");
  //  Les frees me donnent malheureusement des segmentations fault,
  //   int j = 0;
  // for (j=0;j<i;j++){
  //   free(lex_attendu[j].type);
  //   free(lex_attendu[j].value);
  // }
  // free(lex_test);
}



void test_basic_lexem2(){

  list_t lex_test = lex("tests/the.conf", "tests/python_test_folder/pys_folder/2.pys");
  int a = list_length(lex_test);
  test_assert(a==163, "Le nombre de lexèmes est de 163");
  //Créer un tableau de char de comparaison
  struct lexem lex_attendu[] = {
    {"newline", "\n", 1, 0},
    {"newline", "\n", 2, 0},
    {"comment", "# Start pyc-objdump output", 3, 0},
    {"newline", "\n", 3, 26},
    {"newline","\n", 4, 0},
    {"dir::set", ".set", 5, 0},
    {"blank", " ", 5, 4},
    {"version_pyvm", "version_pyvm", 5, 5},
    {"blank", "	 ", 5, 17},
    {"integer::dec", "62211", 5, 19},
    {"newline", "\n", 5, 24},
    {"dir::set", ".set", 6, 0},
    {"blank", " ", 6, 4},
    {"flags", "flags", 6, 5},
    {"blank", "		 ", 6, 10},
    {"integer::hex", "0x00000040", 6, 13},
    {"newline", "\n", 6, 23},
    {"dir::set", ".set", 7, 0},
    {"blank", " ", 7, 4},
    {"filename", "filename", 7, 5},
    {"blank", "		 ", 7, 13},
    {"string", "\"2.py\"", 7, 16},
    {"newline", "\n", 7, 22},
    {"dir::set", ".set", 8, 0},
    {"blank", " ", 8, 4},
    {"name", "name", 8, 5},
    {"blank", "		 ", 8, 9},
    {"string", "\"<module>\"", 8, 12},
    {"newline", "\n", 8, 22},
    {"dir::set", ".set", 9, 0},
    {"blank", " ", 9, 4},
    {"stack_size", "stack_size", 9, 5},
    {"blank", "		 ", 9, 15},
    {"integer::dec", "2", 9, 18},
    {"newline", "\n", 9, 19},
    {"dir::set", ".set", 10, 0},
    {"blank", " ", 10, 4},
    {"arg_count", "arg_count", 10, 5},
    {"blank", "		 ", 10, 14},
    {"integer::dec", "0", 10, 17},
    {"newline", "\n", 10, 18},
    {"newline", "\n", 11, 0},
    {"dir::interned", ".interned", 12, 0},
    {"newline", "\n", 12, 9},
    {"blank", "\t", 13, 0},
    {"string", "\"a\"", 13, 1},
    {"newline", "\n", 13, 4},
    {"blank", "\t", 14, 0},
    {"string", "\"b\"", 14, 1},
    {"newline", "\n", 14, 4},
    {"blank", "\t", 15, 0},
    {"string", "\"c\"", 15, 1},
    {"newline", "\n", 15, 4},
    {"blank", "\t", 16, 0},
    {"string", "\"<module>\"", 16, 1},
    {"newline", "\n", 16, 11},
    {"newline","\n", 17, 0},
    {"dir::consts", ".consts", 18, 0},
    {"newline", "\n", 18, 7},
    {"blank", "\t", 19, 0},
    {"integer::dec", "3", 19, 1},
    {"newline", "\n", 19, 2},
    {"blank", "\t", 20, 0},
    {"integer::dec", "4", 20, 1},
    {"newline", "\n", 20, 2},
    {"blank", "\t", 21, 0},
    {"pycst::None", "None", 21, 1},
    {"newline", "\n", 21, 5},
    {"newline","\n",22,0},
    {"dir::names", ".names", 23, 0},
    {"newline", "\n", 23, 6},
    {"blank", "\t", 24, 0},
    {"string", "\"a\"", 24, 1},
    {"newline", "\n", 24, 4},
    {"blank", "\t", 25, 0},
    {"string", "\"b\"", 25, 1},
    {"newline", "\n", 25, 4},
    {"blank", "\t", 26, 0},
    {"string", "\"c\"", 26, 1},
    {"newline", "\n", 26, 4},
    {"newline","\n",27,0},
    {"dir::text", ".text", 28, 0},
    {"newline", "\n", 28, 5},
    {"dir::line", ".line", 29, 0},
    {"blank", " ", 29, 5},
    {"integer::dec", "1", 29, 6},
    {"newline", "\n", 29, 7},
    {"blank", "\t", 30, 0},
    {"insn::0::LOAD_CONST", "LOAD_CONST", 30, 1},
    {"blank", "            ", 30, 11},
    {"integer::dec", "0", 30, 23},
    {"blank", "\t", 30, 24},
    {"comment", "# 3", 30, 25},
    {"newline", "\n", 30, 28},
    {"blank", "\t", 31, 0},
    {"insn::0::STORE_NAME", "STORE_NAME", 31, 1},
    {"blank", "            ", 31, 11},
    {"integer::dec", "0", 31, 23},
    {"blank", "\t", 31, 24},
    {"comment", "# \"a\"", 31, 25},
    {"newline", "\n", 31, 30},
    {"dir::line", ".line", 32, 0},
    {"blank", " ", 32, 5},
    {"integer::dec", "2", 32, 6},
    {"newline", "\n", 32, 7},
    {"blank", "\t", 33, 0},
    {"insn::0::LOAD_CONST", "LOAD_CONST", 33, 1},
    {"blank", "            ", 33, 11},
    {"integer::dec", "1", 33, 23},
    {"blank", "\t", 33, 24},
    {"comment", "# 4", 33, 25},
    {"newline", "\n", 33, 28},
    {"blank", "\t", 34, 0},
    {"insn::0::STORE_NAME", "STORE_NAME", 34, 1},
    {"blank", "            ", 34, 11},
    {"integer::dec", "1", 34, 23},
    {"blank", "\t", 34, 24},
    {"comment", "# \"b\"", 34, 25},
    {"newline", "\n", 34, 30},
    {"dir::line", ".line", 35, 0},
    {"blank", " ", 35, 5},
    {"integer::dec", "3", 35, 6},
    {"newline","\n",35,7},
    {"blank", "\t", 36, 0},
    {"insn::0::LOAD_NAME", "LOAD_NAME", 36, 1},
    {"blank", "             ", 36, 10},
    {"integer::dec", "0", 36, 23},
    {"blank", "\t", 36, 24},
    {"comment", "# \"a\"", 36, 25},
    {"newline", "\n", 36, 30},
    {"blank", "\t", 37, 0},
    {"insn::0::LOAD_NAME", "LOAD_NAME", 37, 1},
    {"blank", "             ", 37, 10},
    {"integer::dec", "1", 37, 23},
    {"blank", "\t", 37, 24},
    {"comment", "# \"b\"", 37, 25},
    {"newline", "\n", 37, 30},
    {"blank", "\t", 38, 0},
    {"insn::0::BINARY_ADD", "BINARY_ADD", 38, 1},
    {"blank", "            ", 38, 11},
    {"newline","\n",38,23},
    {"blank","	",39,0},
    {"insn::0::STORE_NAME", "STORE_NAME", 39, 1},
    {"blank", "            ", 39, 11},
    {"integer::dec", "2", 39, 23},
    {"blank", "\t", 39, 24},
    {"comment", "# \"c\"", 39, 25},
    {"newline", "\n", 39, 30},
    {"blank", "\t", 40, 0},
    {"insn::0::LOAD_CONST", "LOAD_CONST", 40, 1},
    {"blank", "            ", 40, 11},
    {"integer::dec", "2", 40, 23},
    {"blank", "\t", 40, 24},
    {"comment", "# None", 40, 25},
    {"newline", "\n", 40, 31},
    {"blank", "\t", 41, 0},
    {"insn::0::RETURN_VALUE", "RETURN_VALUE", 41, 1},
    {"blank", "          ", 41, 13},
    {"newline", "\n", 41, 23},
    {"newline","\n", 42,0},
    {"comment", "# Disassembled Mon Oct  9 15:06:09 2023", 43, 0},
    {"newline", "\n", 43, 39},
    {"newline", "\n", 44, 0},
    {"newline", "\n", 45, 0},
};


  //Comparaison de la liste lex, lexème par lexème
  link_t *p=lex_test;
  int i=0;
  while (p!=NULL){
    lexem_t lexem = (lexem_t)(p->content);
    // printf("line_column_test (%d,%d), line_column_excepted (%d,%d) \n",lexem->line,lexem->column,lex_attendu[i].line,lex_attendu[i].column);
    // printf("type_value_test (%s,%s), type_value_excepted (%s,%s) \n",lexem->type,lexem->value,lex_attendu[i].type,lex_attendu[i].value);
    test_assert (!strcmp(lexem->value,lex_attendu[i].value), "Verification des valeurs - itération n°%d",i+1);
    test_assert (!strcmp(lexem->type,lex_attendu[i].type), "Verification des types - itération n°%d",i+1);
    test_assert (lexem->line==lex_attendu[i].line, "Verification des lignes - itération n°%d",i+1);
    test_assert (lexem->column==lex_attendu[i].column, "Verification des colonnes - itération n°%d",i+1);
    i=i+1;
    p=p->next;
  }
  test_assert (p==NULL, "Vérifie si la liste est bien nulle");
  //   int j = 0;
  // for (j=0;j<i;j++){
  //   free(lex_attendu[j].type);
  //   free(lex_attendu[j].value);
  // }
  // free(lex_test);
}

void test_hard_lexem(){

  list_t lex_test = lex("tests/the.conf", "tests/python_test_folder/pys_folder/hard1.pys");
  int a = list_length(lex_test);
  test_assert(a==157, "Le nombre de lexèmes est de 157");
  //Créer un tableau de char de comparaison
  struct lexem lex_attendu[] = {
    {"dir::set", ".set", 1, 0},
    {"blank"," ",1,4},
    {"dir::set", ".set", 1, 5},
    {"blank"," ",1,9},
    {"dir::set", ".set", 1, 10},
    {"blank"," ",1,14},
    {"dir::set", ".set", 1, 15},
    {"blank"," ",1,19},
    {"dir::set", ".set", 1, 20},
    {"blank"," ",1,24},
    {"flags", "flags", 1, 25},
    {"blank"," ",1,30},
    {"integer::dec","48",1,31},
    {"identifier","R883R8748394",1,33},
    {"newline","\n",1,45},

    {"newline","\n",2,0},

    {"dir::consts", ".consts", 3, 0},
    {"blank"," ",3,7},
    {"dir::set", ".set", 3, 8},
    {"blank"," ",3,12},
    {"integer::dec","1234943949",3,13},
    {"blank"," ",3,23},
    {"dir::set", ".set", 3, 24},
    {"blank"," ",3,28},
    {"integer::dec","7777",3,29},
    {"blank"," ",3,33},
    {"integer::hex","0x029893028309",3,34},
    {"blank"," ",3,48},
    {"dir::set", ".set", 3, 49},
    {"newline","\n",3,53},

    {"insn::0::LOAD_CONST", "LOAD_CONST", 4, 0},
    {"blank","            ",4,10},
    {"integer::dec","0",4,22},
    {"blank","	",4,23},
    {"comment", "# 1 ", 4, 24},
    {"newline","\n",4,28},

    {"insn::0::LOAD_CONST", "LOAD_CONST", 5, 0},
    {"blank"," ",5,10},
    {"integer::dec","0",5,11},
    {"blank","	",5,12},
    {"comment", "# 1232030", 5, 13},
    {"newline","\n",5,22},

    {"blank","	",6,0},
    {"insn::0::STORE_NAME", "STORE_NAME", 6, 1}, 
    {"blank","    ",6,11},
    {"integer::dec","0",6,15},
    {"blank","	",6,16},
    {"comment", "# \"a\"", 6, 17},
    {"newline","\n",6,22},

    {"blank","	",7,0},
    {"insn::0::STORE_NAME", "STORE_NAME",7, 1},
    {"blank","            ",7,11},
    {"integer::dec","0",7,23},
    {"blank","	",7,24},
    {"comment", "# \"a\"", 7, 25},
    {"newline","\n",7,30},

    {"newline","\n",8,0},

    {"comment", "# Test commentaire .pys", 9, 0},
    {"newline","\n",9,23},

    {"insn::0::INPLACE_LSHIFT", "INPLACE_LSHIFT", 10, 0},
    {"blank"," ",10,14},
    {"insn::0::INPLACE_LSHIFT", "INPLACE_LSHIFT", 10, 15},
    {"blank","  ",10,29},
    {"insn::0::WITH_CLEANUP_START", "WITH_CLEANUP_START", 10, 31},
    {"blank"," ",10,49},
    {"insn::0::EXEC_STMT", "EXEC_STMT", 10, 50},
    {"blank"," ",10,59},
    {"dir::set", ".set", 10, 60},
    {"blank"," ",10,64},
    {"dir::varnames", ".varnames", 10, 65},
    {"newline","\n",10,74},

    {"dir::set", ".set", 11, 0},
    {"blank", " ",11,4},
    {"integer::dec","2",11,5},
    {"newline","\n",11,6},

    {"dir::line", ".line", 12, 0},
    {"blank", " ",12,5},
    {"integer::dec", "1", 12, 6},
    {"newline", "\n", 12, 7},

    {"blank", "	", 13, 0},
    {"insn::0::LOAD_CONST", "LOAD_CONST", 13, 1},
    {"blank", "    ", 13, 11},
    {"dir::set", ".set", 13, 15},
    {"blank", "        ", 13, 19},
    {"integer::dec","0",13,27},
    {"blank", "	", 13, 28},
    {"comment", "# 12345", 13, 29},
    {"newline", "\n", 13, 36},

    {"blank", "	", 14, 0},
    {"insn::0::STORE_NAME", "STORE_NAME", 14, 1},
    {"blank", "     ", 14, 11},
    {"dir::code_start", ".code_start", 14, 16},
    {"blank", "      ", 14, 27},
    {"integer::dec","0",14,33},
    {"blank", "	", 14, 34},
    {"comment", "# \"nombre\"", 14, 35},
    {"newline", "\n", 14, 45},

    {"dir::line", ".line", 15, 0},
    {"blank", " ",15,5},
    {"integer::dec", "2", 15, 6},
    {"newline", "\n", 15, 7},


    {"blank", "	", 16, 0},
    {"insn::0::LOAD_CONST", "LOAD_CONST", 16, 1},
    {"blank", "            ", 16, 11},
    {"integer::dec","1",16,23},
    {"blank", "	", 16, 24},
    {"comment", "# 0", 16, 25},
    {"newline", "\n", 16, 28},

    {"blank", "	", 17, 0},
    {"insn::0::STORE_NAME", "STORE_NAME", 17, 1},
    {"blank", "            ", 17, 11},
    {"integer::dec","1",17,23},
    {"blank", "	", 17, 24},
    {"comment", "# \"somme\"", 17, 25},
    {"newline", "\n", 17, 34},

    {"dir::line", ".line", 18, 0},
    {"blank", " ",18,5},
    {"integer::dec", "3", 18, 6},
    {"newline", "\n", 18, 7},

    {"blank", "	", 19, 0},
    {"insn::1::SETUP_LOOP", "SETUP_LOOP", 19, 1},
    {"newline", "\n", 19, 11},

    {"newline", "\n", 20, 0},
  
    {"blank", "	", 21, 0},
    {"insn::0::LOAD_CONST", "LOAD_CONST", 21, 1},
    {"blank", "            ", 21, 11},
    {"integer::dec","1",21,23},
    {"blank", "	", 21, 24},
    {"comment", "# 0", 21, 25},
    {"newline", "\n", 21, 28},

    {"dir::line", ".line", 22, 0},
    {"blank", " ",22,5},
    {"integer::dec", "4", 22, 6},
    {"blank", " ", 22, 7},
    {"pycst::None","None",22,8},
    {"blank", " ", 22, 12},
    {"pycst::True","True",22,13},
    {"blank", " ", 22,17 },
    {"pycst::False","False",22,18},
    {"blank", " ", 22,23 },
    {"newline", "\n", 22, 24},

    {"identifier", "Identifiertest",23,0},
    {"blank", " ", 23, 14},
    {"insn::1::FORMAT_VALUE", "FORMAT_VALUE", 23, 15},
    {"newline", "\n", 23, 27},

    {"blank", "        ",24,0},
    {"integer::dec","2",24,8},
    {"blank", "	", 24, 9},
    {"comment", "# 10", 24, 10},
    {"newline", "\n", 24, 14},

    {"blank", "	",25,0},
    {"insn::0::BINARY_MODULO", "BINARY_MODULO", 25, 1},
    {"newline", "\n", 25, 14},

    {"blank", "	",26,0},
    {"insn::0::LOAD_NAME", "LOAD_NAME", 26, 1},
    {"newline", "\n", 26, 10},
    
    {"newline", "\n", 27, 0},

  };
  //Comparaison de la liste lex, lexème par lexème
  list_t p=lex_test;
  int i=0;
 
  while (p!=NULL){
    lexem_t lexem = (lexem_t)(p->content);
    // printf("line_column_test (%d,%d), line_column_excepted (%d,%d) \n",lexem->line,lexem->column,lex_attendu[i].line,lex_attendu[i].column);
    // printf("type_value_test (%s,%s), type_value_excepted (%s,%s) \n",lexem->type,lexem->value,lex_attendu[i].type,lex_attendu[i].value);
    test_assert (!strcmp(lexem->value,lex_attendu[i].value), "Verification des valeurs - itération n°%d",i+1);
    test_assert (!strcmp(lexem->type,lex_attendu[i].type), "Verification des types - itération n°%d",i+1);
    test_assert (lexem->line==lex_attendu[i].line, "Verification des lignes - itération n°%d",i+1);
    test_assert (lexem->column==lex_attendu[i].column, "Verification des colonnes - itération n°%d",i+1);
    i=i+1;
    p=p->next;
  }
  test_assert (p==NULL, "Vérifie si la liste est bien nulle");
  //   int j = 0;
  // for (j=0;j<i;j++){
  //   free(lex_attendu[j].type);
  //   free(lex_attendu[j].value);
  // }
  // free(lex_test);
}


void test_comment(){

  list_t lex_test = lex("tests/the.conf", "tests/python_test_folder/pys_folder/4.pys");
  struct lexem lex_attendu[] = {
    {"comment", "# Start pyc-objdump output", 3, 0},
    {"comment", "# 1", 28, 25},
    {"comment", "# \"a\"", 29, 25},
    {"comment", "# 2", 31, 25},
    {"comment", "# \"b\"", 32, 25},
    {"comment", "# \"a\"", 34, 25},
    {"comment", "# \"b\"", 35, 25},
    {"comment", "# \">\"", 36, 25},
    {"comment", "# \"a\"", 39, 25},
    {"comment", "# \"b\"", 45, 25},
    {"comment", "# None", 49, 25},
    {"comment", "# Disassembled Mon Oct 16 15:33:12 2023", 52, 0},
};
  //Comparaison des comments obtenues
  link_t *p=lex_test;
  int i=0;

  char * comment="comment";
  while (p!=NULL){
    lexem_t lexem = (lexem_t)(p->content);
    if (!strcmp(lexem->type,comment)){
    // printf("line_column_test (%d,%d), line_column_excepted (%d,%d) \n",lexem->line,lexem->column,lex_attendu[i].line,lex_attendu[i].column);
    // printf("type_value_test (%s,%s), type_value_excepted (%s,%s) \n",lexem->type,lexem->value,lex_attendu[i].type,lex_attendu[i].value);
    test_assert (!strcmp(lexem->value,lex_attendu[i].value), "Verification des valeurs - itération n°%d",i+1);
    test_assert (lexem->line==lex_attendu[i].line, "Verification des lignes - itération n°%d",i+1);
    test_assert (lexem->column==lex_attendu[i].column, "Verification des colonnes - itération n°%d",i+1);
    i=i+1;
    }
    p=p->next;
  }
  test_assert (p==NULL, "Vérifie si la liste est bien nulle");
 //   int j = 0;
  // for (j=0;j<i;j++){
  //   free(lex_attendu[j].type);
  //   free(lex_attendu[j].value);
  // }
  // free(lex_test);
}

void test_newline(){
  
  list_t lex_test = lex("tests/the.conf", "tests/python_test_folder/pys_folder/7.pys");
  struct lexem lex_attendu[] = {
    {"newline", "\n", 1, 0},
    {"newline", "\n", 2, 0},
    {"newline", "\n", 3, 26},
    {"newline", "\n", 4, 0},
    {"newline", "\n", 5, 24},
    {"newline", "\n", 6, 23},
    {"newline", "\n", 7, 22},
    {"newline", "\n", 8, 22},
    {"newline", "\n", 9, 19},
    {"newline", "\n", 10, 18},
    {"newline", "\n", 11, 0},
    {"newline", "\n", 12, 9},
    {"newline", "\n", 13, 6},
    {"newline", "\n", 14, 6},
    {"newline", "\n", 15, 4},
    {"newline", "\n", 16, 4},
    {"newline", "\n", 17, 4},
    {"newline", "\n", 18, 11},
    {"newline", "\n", 19, 0},
    {"newline", "\n", 20, 7},
    {"newline", "\n", 21, 2},
    {"newline", "\n", 22, 2},
    {"newline", "\n", 23, 3},
    {"newline", "\n", 24, 6},
    {"newline", "\n", 25, 6},
    {"newline", "\n", 26, 5},
    {"newline", "\n", 27, 0},
    {"newline", "\n", 28, 6},
    {"newline", "\n", 29, 4},
    {"newline", "\n", 30, 4},
    {"newline", "\n", 31, 4},
    {"newline", "\n", 32, 0},
    {"newline", "\n", 33, 5},
    {"newline", "\n", 34, 7},
    {"newline", "\n", 35, 28},
    {"newline", "\n", 36, 30},
    {"newline", "\n", 37, 7},
    {"newline", "\n", 38, 28},
    {"newline", "\n", 39, 30},
    {"newline", "\n", 40, 7},
    {"newline", "\n", 41, 29},
    {"newline", "\n", 42, 30},
    {"newline", "\n", 43, 7},
    {"newline", "\n", 44, 30},
    {"newline", "\n", 45, 30},
    {"newline", "\n", 46, 30},
    {"newline", "\n", 47, 30},
    {"newline", "\n", 48, 30},
    {"newline", "\n", 49, 30},
    {"newline", "\n", 50, 30},
    {"newline", "\n", 51, 30},
    {"newline", "\n", 52, 7},
    {"newline", "\n", 53, 32},
    {"newline", "\n", 54, 23},
    {"newline", "\n", 55, 23},
    {"newline", "\n", 56, 30},
    {"newline", "\n", 57, 7},
    {"newline", "\n", 58, 8},
    {"newline", "\n", 59, 32},
    {"newline", "\n", 60, 23},
    {"newline", "\n", 61, 23},
    {"newline", "\n", 62, 31},
    {"newline","\n",63,23},
    {"newline", "\n", 64, 0},
    {"newline", "\n", 65, 39},
    {"newline", "\n", 66, 0},
};
  //Comparaison des newlines obtenues
  link_t *p=lex_test;
  char * newline="newline";
  int i=0;
  while (p!=NULL){
    lexem_t lexem = (lexem_t)(p->content);
    if (!strcmp(lexem->type,newline)){
    // printf("line_column_test (%d,%d), line_column_excepted (%d,%d) \n",lexem->line,lexem->column,lex_attendu[i].line,lex_attendu[i].column);
    // printf("type_value_test (%s,%s), type_value_excepted (%s,%s) \n",lexem->type,lexem->value,lex_attendu[i].type,lex_attendu[i].value);
    test_assert (!strcmp(lexem->value,lex_attendu[i].value), "Verification des valeurs - itération n°%d",i+1);
    test_assert (lexem->line==lex_attendu[i].line, "Verification des lignes - itération n°%d",i+1);
    test_assert (lexem->column==lex_attendu[i].column, "Verification des colonnes - itération n°%d",i+1);
    i=i+1;
    }
    p=p->next;
  }
  test_assert (p==NULL, "Vérifie si la liste est bien nulle");
  //   int j = 0;
  // for (j=0;j<i;j++){
  //   free(lex_attendu[j].type);
  //   free(lex_attendu[j].value);
  // }
  // free(lex_test);
}

void test_blank(){
    
  list_t lex_test = lex("tests/the.conf", "tests/python_test_folder/pys_folder/5.pys");
  struct lexem lex_attendu[] = {
    {"blank", " ", 5, 4},
    {"blank", "	 ", 5, 17},
    {"blank", " ", 6, 4},
    {"blank", "		 ", 6, 10},

    {"blank", " ", 7, 4},
    {"blank", "		 ", 7, 13},

    {"blank", " ", 8, 4},
    {"blank", "		 ", 8, 9},


    {"blank", " ", 9, 4},
    {"blank", "		 ", 9, 15},

    {"blank", " ", 10, 4},
    {"blank", "		 ", 10, 14},
    
    {"blank","	",13,0},
    {"blank","	",14,0},
    {"blank","	",15,0},
    {"blank","	",16,0},

    {"blank","	",19,0},
    {"blank","	",20,0},
    {"blank","	",21,0},
    {"blank","	",22,0},
    {"blank","	",23,0},

    {"blank","	",26,0},
    {"blank","	",27,0},
    {"blank","	",28,0},

    {"blank"," ",31,5},
    {"blank","	",32,0},
    {"blank","            ",32,11},
    {"blank","	",32,24},

    {"blank","	",33,0},
    {"blank","            ",33,11},
    {"blank","	",33,24},

    {"blank"," ",34,5},
    {"blank","	",35,0},
    {"blank","            ",35,11},

    {"blank","	",36,0},
    {"blank","             ",36,10},
    {"blank","	",36,24},


    {"blank","	",37,0},
    {"blank","            ",37,11},
    {"blank","	",37,24},

    {"blank","	",38,0},
    {"blank","         ",38,14},
    
    {"blank","	",39,0},
    {"blank","              ",39,9},

    {"blank","	",41,0},
    {"blank","              ",41,9},

    {"blank","	",42,0},
    {"blank","            ",42,11},
    {"blank","	",42,24},

    {"blank"," ",43,5},

    {"blank","	",44,0},
    {"blank","             ",44,10},
    {"blank","	",44,24},

    {"blank","	",45,0},
    {"blank","             ",45,10},
    {"blank","	",45,24},

    {"blank","	",46,0},
    {"blank","            ",46,11},
    {"blank","	",46,24},

    {"blank","	",47,0},
    {"blank","            ",47,11},
  
    {"blank","	",48,0},
    {"blank","           ",48,12},

    {"blank","	",49,0},
    {"blank","            ",49,11},
    {"blank","	",49,24},

    {"blank","	",50,0},
    {"blank","         ",50,14},

    {"blank","	",52,0},
    {"blank","             ",52,10},
    {"blank"," ",53,5},
  
    {"blank","	",55,0},
    {"blank","            ",55,11},
    {"blank","	",55,24},
  
    {"blank","	",56,0},
    {"blank","            ",56,11},

    {"blank","	",57,0},
    {"blank","         ",57,14},

    {"blank","	",58,0},
    {"blank","            ",58,11},
    {"blank","	",58,24},

    {"blank","	",59,0},
    {"blank","          ",59,13},


};

  link_t *p=lex_test;
  char * blank="blank";
  int i=0;
  while (p!=NULL){
    lexem_t lexem = (lexem_t)(p->content);
    if (!strcmp(lexem->type,blank)){
    // printf("line_column_test (%d,%d), line_column_excepted (%d,%d) \n",lexem->line,lexem->column,lex_attendu[i].line,lex_attendu[i].column);
    // printf("type_value_test (%s,%s), type_value_excepted (%s,%s) \n",lexem->type,lexem->value,lex_attendu[i].type,lex_attendu[i].value);
    test_assert (!strcmp(lexem->value,lex_attendu[i].value), "Verification des valeurs - itération n°%d",i+1);
    test_assert (lexem->line==lex_attendu[i].line, "Verification des lignes - itération n°%d",i+1);
    test_assert (lexem->column==lex_attendu[i].column, "Verification des colonnes - itération n°%d",i+1);
    i=i+1;
    }
    p=p->next;
  }
  test_assert (p==NULL, "Vérifie si la liste est bien nulle");
  //   int j = 0;
  // for (j=0;j<i;j++){
  //   free(lex_attendu[j].type);
  //   free(lex_attendu[j].value);
  // }
  // free(lex_test);
}


void test_string(){
  
  list_t lex_test = lex("tests/the.conf", "tests/python_test_folder/pys_folder/16.pys");
  struct lexem lex_attendu[] = {
    {"string", "\"16.py\"", 7, 16},
    {"string", "\"<module>\"", 8, 12},
    {"string","\"texte\"",13,1},
    {"string","\"len\"",14,1},
    {"string","\"longueur\"",15,1},
    {"string","\"<module>\"",16,1},
    {"string", "\"Bonjour, monde !\"", 19, 1},
    {"string", "\"La longueur de la chaîne de caractères est\"", 20, 1},
    {"string", "\"caractères.\"", 21, 1},
    {"string", "\"texte\"", 25, 1},    
    {"string", "\"len\"", 26, 1},
    {"string", "\"longueur\"", 27, 1},
};

  link_t *p=lex_test;
  char * string="string";
  int i=0;
  while (p!=NULL){
    lexem_t lexem = (lexem_t)(p->content);
    if (!strcmp(lexem->type,string)){
    // printf("line_column_test (%d,%d), line_column_excepted (%d,%d) \n",lexem->line,lexem->column,lex_attendu[i].line,lex_attendu[i].column);
    // printf("type_value_test (%s,%s), type_value_excepted (%s,%s) \n",lexem->type,lexem->value,lex_attendu[i].type,lex_attendu[i].value);
    test_assert (!strcmp(lexem->value,lex_attendu[i].value), "Verification des valeurs - itération n°%d",i+1);
    test_assert (lexem->line==lex_attendu[i].line, "Verification des lignes - itération n°%d",i+1);
    test_assert (lexem->column==lex_attendu[i].column, "Verification des colonnes - itération n°%d",i+1);
    i=i+1;
    }
    p=p->next;
  }
  test_assert (p==NULL, "Vérifie si la liste est bien nulle");
  //   int j = 0;
  // for (j=0;j<i;j++){
  //   free(lex_attendu[j].type);
  //   free(lex_attendu[j].value);
  // }
  // free(lex_test);
}



void test_empty_lex(){

  list_t lex_test = lex("tests/the.conf", "tests/python_test_folder/pys_folder/empty.pys");
  test_assert (lex_test==NULL, "Verifie si la liste lex est nulle");
}

void test_invalid_lex(){
  
  list_t lex_test1 = lex("tests/the.conf", "tests/python_test_folder/pys_folder/invalid1.pys");
  list_t lex_test2 = lex("tests/the.conf", "tests/python_test_folder/pys_folder/invalid2.pys");
  test_assert (lex_test1==NULL, "Verifie si le invalid1.pys donne un lex nul");
  test_assert (lex_test2==NULL, "Verifie si le invalid2.pys donne un lex nul");

}




int main ( int argc, char *argv[] ) { 

    unit_test( argc, argv ); 
    
    // Tests sur des fichiers .pys simples
    test_suite( "test 1.pys - simple fichier .pys" ); 
    test_basic_lexem1();
    test_suite( "test 2.pys - simple fichier .pys" ); 
    test_basic_lexem2();

    // Tests sur un fichiers .pys complexe 
    test_suite( "test 1 - fichier .pys complexe" ); 
    test_hard_lexem();
 
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
    test_suite( "test string" ); 
    test_string();

    // Test sur un fichier .pys vide
    test_suite( "test fichier .pys vide" ); 
    test_empty_lex();

    // Test sur un fichier .pys invalide (avec des lexèmes différents du .conf)
    test_suite( "test fichiers .pys invalides" ); 
    test_invalid_lex();

  exit( EXIT_SUCCESS ); 
}

