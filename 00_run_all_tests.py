#! /usr/bin/env python3
# coding: utf-8

import os,sys
# import requests,subprocess
import json
import csv
import argparse
import time
from datetime import datetime
import tarfile
import pathlib


def getTestCommands_L(argv, test_suit_path, test_suite_mode):
    ## A EDITER POUR PRECISER LES TESTS A AMELIORER DURANT L'EXAM
    selected_tests_commands_L = (
    # REGEXP
        "./01_test_regexp.py PARSE " + test_suit_path + "/01_test_regexp/01_expreg_parse/*.test",
        "./01_test_regexp.py MATCH " + test_suit_path + "/01_test_regexp/02_expreg_match/*.test",

    # LEXER
        "./02_test_lexer_and_parser.py LEXER " + test_suit_path + "/02_test_lexer_and_parser/01_lex_OK/*.pys",
        "./02_test_lexer_and_parser.py LEXER " + test_suit_path + "/02_test_lexer_and_parser/02_lex_KO/*.pys",

    # PARSER
        "./02_test_lexer_and_parser.py LEXER_AND_PARSER " + test_suit_path + "/02_test_lexer_and_parser/03_parse_OK/*.pys",
        "./02_test_lexer_and_parser.py LEXER_AND_PARSER " + test_suit_path + "/02_test_lexer_and_parser/04_parse_KO/*.pys",

    # PYAS
        "./03_test_pyas.py " + test_suit_path + "/03_test_pyas/*/*/01_nolabel_details/*.pys",
        "./03_test_pyas.py " + test_suit_path + "/03_test_pyas/*/*/02_label_details/*.pys",
        "./03_test_pyas.py " + test_suit_path + "/03_test_pyas/03_PYS_KO/*/*.pys"
    )

    try_tests_commands_L = (
        "./01_test_regexp.py PARSE " + test_suit_path + "/00_try/01_test_regexp/01_expreg_parse/00_try.test",
        "./01_test_regexp.py MATCH " + test_suit_path + "/00_try/01_test_regexp/02_expreg_match/00_try.test",
        "./02_test_lexer_and_parser.py LEXER_AND_PARSER " + test_suit_path + "/00_try/02_test_lexer_and_parser/00_try/00_try.pys",
        "./03_test_pyas.py " + test_suit_path + "/00_try/03_test_pyas/00_try/*/*.pys"
    )

    all_tests_commands_L = (
        "./01_test_regexp.py PARSE " + test_suit_path + "/01_test_regexp/01_expreg_parse/*.test",
        "./01_test_regexp.py MATCH " + test_suit_path + "/01_test_regexp/02_expreg_match/*.test",
        "./02_test_lexer_and_parser.py LEXER " + test_suit_path + "/02_test_lexer_and_parser/01_lex_OK/*.pys",
        "./02_test_lexer_and_parser.py LEXER " + test_suit_path + "/02_test_lexer_and_parser/02_lex_KO/*.pys",
        "./02_test_lexer_and_parser.py LEXER_AND_PARSER " + test_suit_path + "/02_test_lexer_and_parser/03_parse_OK/*.pys",
        "./02_test_lexer_and_parser.py LEXER_AND_PARSER " + test_suit_path + "/02_test_lexer_and_parser/04_parse_KO/*.pys",
        "./03_test_pyas.py " + test_suit_path + "/03_test_pyas/*/*/01_nolabel_details/*.pys",
        "./03_test_pyas.py " + test_suit_path + "/03_test_pyas/*/*/02_label_details/*.pys",
        "./03_test_pyas.py " + test_suit_path + "/03_test_pyas/03_PYS_KO/*/*.pys"
    )

    if test_suite_mode == "test_suite_mode_selected":
        return selected_tests_commands_L
    elif test_suite_mode == "test_suite_mode_try":
        return try_tests_commands_L
    elif test_suite_mode == "test_suite_mode_all" or test_suite == None:
        return all_tests_commands_L
    else:
        print("### Error : unknown test_suite_mode : " + str(test_suite_mode))
        printUsage(argv)
        printf("### Aborts")
        sys.exit(1)


def printUsage(argv):
    print("Usage  : ")
    print("   " + argv[0] + " (-h | directory_to_test_suit   (-d | --dry-run) ((-a | --all) (-t | --try) (-s | --selected)) ) ")
    print("Par exemple :")
    print("   " + argv[0] + " ../tests_debut_exam ")
    print("   ou ")
    print("   " + argv[0] + " ../tests_fin_exam ")
    print("   ou ")
    print("   " + argv[0] + " ../tests_debut_exam -d")
    print("Nécessite que le fichier 00_test_command_line.conf soit configuré a la racine du dépot du groupe.")
    print("Options : \n")
    print("  -t ou --try          : pour tester la config - seulement 4 tests.\n")
    print("  -a ou --all (default): tous les tests de l'examen\n")
    print("  -s ou --selected     : testés sélectionnés.\n")
    print("\n")
    print("  -d ou --dry-run      : affiche les tests à exécuter, sans les exécuter.\n")


this_script_path = os.path.dirname(os.path.realpath(__file__))

if '-h' in sys.argv or "-help" in sys.argv or "--help" in sys.argv :
    printUsage(sys.argv)
    sys.exit(0)

if len(sys.argv) < 2 or len(sys.argv) > 4:
    print("### Error number of arguments")
    printUsage(sys.argv)
    sys.exit(1)

test_suit_dir_args = sys.argv[1]
test_suit_path = test_suit_dir_args
#est_suit_dir_fullpath = os.path.abspath(test_suit_dir_args)


if len(sys.argv) > 2 :
    for arg in sys.argv[2:]:
        if arg != "-d" and arg != "--dry-run" and arg != "-a" and arg != "--all" and arg != "-t" and arg != "--try" and arg != "-s" and arg != "--selected":
            print("### Error arguments : invalid argument : " + arg )
            printUsage(sys.argv)
            sys.exit(1)

test_suite_mode = "test_suite_mode_all" #  test_suite_mode_selected test_suite_mode_try
if  "-t" in sys.argv or "--try" in sys.argv:
    test_suite_mode = "test_suite_mode_try"
elif  "-s" in sys.argv or "--selected" in sys.argv:
    test_suite_mode = "test_suite_mode_selected"

if not os.path.isdir(test_suit_path) :
    print("### Error : arg 1 : '" + test_suit_dir_args + "' is not a directory")
    print("### Aborts.")
    sys.exit(1)

if not os.path.isdir(test_suit_path + "/01_test_regexp") :
    print("### Error : arg 1 : " + test_suit_dir_args + " apparently does not contain the exam's tests (should contain 01_test_regexp)")
    print("### Aborts.")
    sys.exit(1)

if not os.path.isdir(test_suit_path + "/02_test_lexer_and_parser") :
    print("### Error : arg 1 : " + test_suit_dir_args + " apparently does not contain the exam's tests (should contain 02_test_lexer_and_parser)")
    print("### Aborts.")
    sys.exit(1)

if not os.path.isdir(test_suit_path + "/03_test_pyas") :
    print("### Error : arg 1 : " + test_suit_dir_args + " apparently does not contain the exam's tests (should contain 03_test_pyas)")
    print("### Aborts.")
    sys.exit(1)


if( "-d" in sys.argv or "--dry-run" in sys.argv):
    print("### dry-run. Les tests exécutés sont :")
    print("  " + "\n  ".join(getTestCommands_L(sys.argv, test_suit_path, test_suite_mode)))
    sys.exit(0)

if not os.path.isfile(this_script_path + "/00_test_command_line.conf") :
    print("### Error : cannot find 00_test_command_line.conf in " + this_script_path)
    print("### Aborts.")
    sys.exit(1)

if not os.path.isfile(this_script_path + "/01_test_regexp.py") :
    print("### Error : cannot find 01_test_regexp.py in " + this_script_path)
    print("### Aborts.")
    sys.exit(1)


if not os.path.isfile(this_script_path + "/02_test_lexer_and_parser.py") :
    print("### Error : cannot find 02_test_lexer_and_parser.py in " + this_script_path)
    print("### Aborts.")
    sys.exit(1)

if not os.path.isfile(this_script_path + "/03_test_pyas.py") :
    print("### Error : cannot find 03_test_pyas.py in " + this_script_path)
    print("### Aborts.")
    sys.exit(1)


print("### clear test results in " + test_suit_path)
os.system(this_script_path + "/09_clear_tests_outputs.py" + "  " + test_suit_path)


for command in getTestCommands_L(sys.argv, test_suit_path, test_suite_mode):
    print("### executing :")
    print(command)
    retcode = os.system(command)
    assert retcode == 0

tests_aborted_file_path = test_suit_path + "/ZZ_tests_aborted.report"
print("### generating aborted test report in file " + tests_aborted_file_path)
os.system("echo '### All tests terminated with a signal : ###' >" + tests_aborted_file_path)
os.system("grep 'TEST RETURN CODE     : SIGNAL' -R " + test_suit_path + " >> " + tests_aborted_file_path)
os.system("echo  ' ' >>" + tests_aborted_file_path)
os.system("echo  ' ' >>" + tests_aborted_file_path)
os.system("echo '### Commands terminated with SIGABRT : ###' >>" + tests_aborted_file_path)
os.system("grep '6 - SIGABRT' -R " + test_suit_path + " >> " + tests_aborted_file_path)
os.system("echo  ' ' >>" + tests_aborted_file_path)
os.system("echo '### Commands terminated with SIGSEG : ###' >>" + tests_aborted_file_path)
os.system("grep '11 - SIGSEGV' -R " + test_suit_path + " >> " + tests_aborted_file_path)
os.system("echo  ' ' >>" + tests_aborted_file_path)
os.system("echo '### Commands terminated with SIGTERM : ###' >>" + tests_aborted_file_path)
os.system("grep '15 - SIGTERM' -R " + test_suit_path + " >> " + tests_aborted_file_path)
os.system("echo  ' ' >>" + tests_aborted_file_path)
os.system("echo '### Commands terminated with SIGKILL : ###' >>" + tests_aborted_file_path)
os.system("grep '9 - SIGKILL' -R " + test_suit_path + " >> " + tests_aborted_file_path)


print("### All test executed")
