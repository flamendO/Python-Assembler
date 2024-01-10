
#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include <pyas/regexp.h>
#include <unitest/unitest.h>
#include <pyas/queue.h>
#include <pyas/chargroup.h>
#include <pyas/list.h>
#include <pyas/lexem.h>
#include <pyas/lexem_type.h>
#include <pyas/lexer_code.h>

/*DEFINITION DU CHEMIN AU FICHIER CONFIGURATION POUR LES TESTS*/

char * conf_file = "tests/the.conf";

static void parse_pys_file(void){
    
    test_suite( "Simple pys test" );
    list_t lexem_list = list_new();
    lexem_list = lex(conf_file, "tests/python_test_folder/pys_folder/1.pys");
    int result = is_parse(&lexem_list);

    test_assert(result, "1.pys file test\n"); 

    lexem_list = lex(conf_file, "tests/python_test_folder/pys_folder/2.pys");
    result = is_parse(&lexem_list);
    test_assert(result, "2.pys file test\n");

    lexem_list = lex(conf_file, "tests/python_test_folder/pys_folder/4.pys");
    result = is_parse(&lexem_list);
    test_assert(result, "4.pys file test\n");

    lexem_list = lex(conf_file, "tests/python_test_folder/pys_folder/5.pys");
    result = is_parse(&lexem_list);
    test_assert(result, "5.pys file test\n");

    lexem_list = lex(conf_file, "tests/python_test_folder/pys_folder/6.pys");
    result = is_parse(&lexem_list);
    test_assert(result, "6.pys file test\n");

    lexem_list = lex(conf_file, "tests/python_test_folder/pys_folder/7.pys");
    result = is_parse(&lexem_list);
    test_assert(result, "7.pys file test\n");

    lexem_list = lex(conf_file, "tests/python_test_folder/pys_folder/9.pys");
    result = is_parse(&lexem_list);
    test_assert(result, "9.pys file test\n");

    lexem_list = lex(conf_file, "tests/python_test_folder/pys_folder/10.pys");
    result = is_parse(&lexem_list);
    test_assert(result, "10.pys file test\n");

    lexem_list = lex(conf_file, "tests/python_test_folder/pys_folder/11.pys");
    result = is_parse(&lexem_list);
    test_assert(result, "11.pys file test\n");

    lexem_list = lex(conf_file, "tests/python_test_folder/pys_folder/12.pys");
    result = is_parse(&lexem_list);
    test_assert(result, "12.pys file test\n");

    lexem_list = lex(conf_file, "tests/python_test_folder/pys_folder/13.pys");
    result = is_parse(&lexem_list);
    test_assert(result, "13.pys file test\n");

    lexem_list = lex(conf_file, "tests/python_test_folder/pys_folder/14.pys");
    result = is_parse(&lexem_list);
    test_assert(result, "14.pys file test\n");

    
    list_t lexem_list3 = list_new();
    lexem_list3 = lex(conf_file, "tests/python_test_folder/pys_folder/16.pys");
    int result3 = is_parse(&lexem_list3);
    test_assert(result3, "16.pys file test\n"); 

    lexem_list = lex(conf_file, "tests/python_test_folder/pys_folder/17.pys");
    result = is_parse(&lexem_list);
    test_assert(result, "17.pys file test\n");

    list_t lexem_list2 = list_new();
    lexem_list2 = lex(conf_file, "tests/python_test_folder/pys_folder/1.pys");
    lexem_list2 = lex(conf_file, "tests/python_test_folder/pys_folder/18.pys");
    int result2 = is_parse(&lexem_list2);
    printf("ATTENTION : %d", result2);
    test_assert(result, "18.pys file test\n");
    //list_free(&lexem_list2);

    lexem_list = lex(conf_file, "tests/python_test_folder/pys_folder/19.pys");
    result = is_parse(&lexem_list);
    test_assert(result, "19.pys file test\n");

    

    lexem_list = lex(conf_file, "tests/python_test_folder/pys_folder/21.pys");
    result = is_parse(&lexem_list);
    test_assert(result, "21.pys file test\n");


    list_free(&lexem_list);

}

static void parse_pys_file_not_working(void){
    
    test_suite( "NOT parsing pys test" );
    list_t lexem_list = list_new();
    lexem_list = lex(conf_file, "tests/python_test_folder/pys_false_folder/1.pys");
    int result = is_parse(&lexem_list);
    test_assert(!result, "1.pys false file test : character missing\n"); 

    lexem_list = lex(conf_file, "tests/python_test_folder/pys_false_folder/2.pys");
    result = is_parse(&lexem_list);
    test_assert(!result, "2.pys false file test : \" missing \n"); 

    lexem_list = lex(conf_file, "tests/python_test_folder/pys_false_folder/3.pys");
    result = is_parse(&lexem_list);
    test_assert(!result, "3.pys false file test : .names missing \n"); 

    lexem_list = lex(conf_file, "tests/python_test_folder/pys_false_folder/4.pys");
    result = is_parse(&lexem_list);
    test_assert(!result, "4.pys false file test : _ missing \n"); 

    lexem_list = lex(conf_file, "tests/python_test_folder/pys_false_folder/5.pys");
    result = is_parse(&lexem_list);
    test_assert(!result, "5.pys false file test : version_pyvm missing \n"); 

    lexem_list = lex(conf_file, "tests/python_test_folder/pys_false_folder/6.pys");
    result = is_parse(&lexem_list);
    test_assert(!result, "6.pys false file test : flags missing \n"); 

    lexem_list = lex(conf_file, "tests/python_test_folder/pys_false_folder/7.pys");
    result = is_parse(&lexem_list);
    test_assert(!result, "7.pys false file test : filename missing \n"); 

    lexem_list = lex(conf_file, "tests/python_test_folder/pys_false_folder/8.pys");
    result = is_parse(&lexem_list);
    test_assert(!result, "8.pys false file test : name missing \n"); 

    lexem_list = lex(conf_file, "tests/python_test_folder/pys_false_folder/9.pys");
    result = is_parse(&lexem_list);
    test_assert(!result, "9.pys false file test : stack size missing \n");

    lexem_list = lex(conf_file, "tests/python_test_folder/pys_folder/15.pys");
    result = is_parse(&lexem_list);
    test_assert(!result, "15.pys file test when there are functions\n");

    lexem_list = lex(conf_file, "tests/python_test_folder/pys_folder/20.pys");
    result = is_parse(&lexem_list);
    test_assert(!result, "20.pys file test when there are functions\n"); 

    lexem_list = lex(conf_file, "tests/python_test_folder/pys_folder/22.pys");
    result = is_parse(&lexem_list);
    test_assert(!result, "22.pys file test when there are functions\n");
    

    list_free(&lexem_list);
}


int main(int argc, char *argv[]){
    
    unit_test( argc, argv );
    parse_pys_file();
    
    parse_pys_file_not_working();



    return EXIT_SUCCESS;
}
