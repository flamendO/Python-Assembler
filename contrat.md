1. rajouter [\+\-] pour les nombres signés ; 
2. régler les accès mémoire erronés rapportés par Valgrind ;

==21915== Conditional jump or move depends on uninitialised value(s)
==21915==    at 0x110D32: issFull (regexp.c:63)
==21915==    by 0x110F0C: re_match_one_or_more (regexp.c:110)
==21915==    by 0x1112AE: re_match (regexp.c:220)
==21915==    by 0x10F5B7: lex (lexer_code.c:36)
==21915==    by 0x11602A: main (lexer.c:18)


3. regarder les chaînes contenant un \"

