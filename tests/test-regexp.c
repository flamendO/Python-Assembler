/**
 * @file test-regexp.c
 * @author François Cayre <cayre@uvolante.org>
 * @date Sun Aug  7 21:22:53 2022
 * @brief Unit tests for regexps.
 *
 * Unit tests for regexps.
 */

#include <pyas/regexp.h>
#include <unitest/unitest.h>
#include <pyas/queue.h>
#include <pyas/chargroup.h>
#include <pyas/list.h>

/*

  The purpose of this file is to get you started for testing your regexp engine. 

  From a purely combinatorial perspective, designing an exhaustive set of tests 
  for regexp matching is impossible because (1) a regexp implements a 
  deterministic finite automaton and (2) the size of the set of C-strings is:
  $$\sum_{i=1}^{2^48} 256^i$$
  (on an amd64 machine, just like the one you are probably using right now). 

  That's the main reason why we shall focus on positive tests below. 

  Yet, your little regexp engine will be constructed by *incrementally* adding 
  support for various operators: we tell you how to match a constant regexp (one 
  that does not contain any regexp operator) and a regexp containing `.` and/or 
  `*` operators -- and you will add support for regexp operators `+` and `?`, 
  etc. 

  Also, remember that we are only supposed to match a regexp against the *start* 
  of `source`! 

  Now we need some systematic way of writing our tests for the operators. We 
  propose the following strategy:
  - First we ensure core positive/negative properties of an operator (e.g., `*` 
    operator must have a preceding char, etc.), 
  - Then we ensure its behaviour is correct whether it appears (1) at the 
    beginning, (2) in the middle, and (3) at the end of a regexp. 

  Then it remains to test the behaviour of the legal combinations that were not 
  covered by the above. In the present situation with the sole `.` and `*` 
  operators available, the only remaining, uncovered legal combination is `.*`. 
  
  That's because `*.` should have been covered in the tests above by "continuity 
  by concatenation" (between a regexp that ends in `*` and another that starts 
  in `.`), but `.*` was not tested already as the operators were tested 
  separately and `*` refers to its preceding character. 
  
  This gives us a blueprint for our testing strategy: 
  1. pre/post-conditions; 
  2. constant regexps; 
  3. regexps containing `.`; 
  4. regexps containing `*`; 
  5. regexps containing `.*`. 


  Obviously, any extension of these tests should be *justified* along the same 
  lines. Similarly, the logic of any new group of tests for any new module 
  should be *justified* in some way. 

*/

static void re_pre_post( void ) { 
  /* No relevant post-condition was identified, except return values. */

  char *end; 



  test_suite( "Interface robustness" ); 

  test_assert( !re_match( NULL, NULL, &end ), 
	       "Matching fails when source is NULL" ); 

  test_assert(  re_match( NULL, "a", &end ), 
		"The NULL regexp always matches" ); 

  //test_assert(  re_match( "", "a", &end ), 
	        //"The empty regexp always matches" ); 

  //test_assert(  re_match( "", "a", NULL ), 
		//"Parameter `end` is optional" ); 

}

static void re_constant(void) {
    char *end = NULL;

    fifo *char_fifo;
    list_t char_list;

    test_suite("Constant regexps");

    char_fifo = char_to_queue("abc");  
    char_list = fifo_to_list(char_fifo);

    test_assert(!re_match(char_list, "ab", &end), "The whole regexp must match");

    char_fifo = char_to_queue("a");  
    char_list = fifo_to_list(char_fifo);

    test_assert( re_match( char_list, "abc", &end ), "Can match a single char" );
    test_oracle(  printf( "%s", end ), "bc", NULL, "  And suffix is OK" ); 

    char_fifo = char_to_queue("ab");  
    char_list = fifo_to_list(char_fifo);

    test_assert(  re_match( char_list, "abc", &end ), "Can match prefix string" );
    test_oracle(  printf( "%s", end ), "c", NULL, "  And suffix is OK" ); 

    char_fifo = char_to_queue("abc");  
    char_list = fifo_to_list(char_fifo);


    test_assert(  re_match( char_list, "abc", &end ), "Can match last string" ); 
    test_oracle( !printf( "%s", end ), "", NULL, "  And suffix is empty" );

  
  fifo_delete(&char_fifo);

  
}

static void re_dot( void ) { 
  char*end = NULL; 
  
  fifo *char_fifo;
  list_t char_list;

  test_suite( "`.` core properties" ); 

  char_fifo = char_to_queue(".");  
  char_list = fifo_to_list(char_fifo);

  test_assert( !re_match( char_list, "", NULL ), "The empty source does *not* match `.`" ); 

  test_assert(  re_match( char_list, "z", NULL ) && re_match( char_list, "abc", &end ), "Any character matches `.`" ); 
  test_oracle(  printf( "%s", end ), "bc", NULL, "  And suffix is OK" ); 


  test_suite( "`.` continuity" ); 

  char_fifo = char_to_queue(".ip");  
  char_list = fifo_to_list(char_fifo);

  test_assert(  re_match( char_list, "zipend", &end ), "Can match `.` at start of regexp" ); 
  test_oracle(  printf( "%s", end ), "end", NULL, "  And suffix is OK" ); 

  char_fifo = char_to_queue("z.p");  
  char_list = fifo_to_list(char_fifo);

  test_assert(  re_match( char_list, "zipend", &end ), "Can match `.` inside regexp" ); 
  test_oracle(  printf( "%s", end ), "end", NULL, "  And suffix is OK" ); 

  char_fifo = char_to_queue("zi.");  
  char_list = fifo_to_list(char_fifo);

  test_assert(  re_match( char_list, "zipend", &end ), "Can match `.` at end of regexp" ); 
  test_oracle(  printf( "%s", end ), "end", NULL, "  And suffix is OK" ); 

  
  fifo_delete(&char_fifo);
  
  return;   
}


static void re_star( void ) { 
  char*end = NULL; 
  
  fifo *char_fifo;
  list_t char_list; 

  test_suite( "`*` core properties" ); 

  char_fifo = char_to_queue("*");  
  char_list = fifo_to_list(char_fifo);


  test_assert( !re_match( char_list, "aaaa", &end ), "Cannot match `*` at start of regexp" );
  test_oracle(  printf( "%s", end ), "aaaa", NULL, "  And end == source" ); 

  char_fifo = char_to_queue("a**");  
  char_list = fifo_to_list(char_fifo);

  test_assert( !re_match( char_list, "aaaabb", &end ), "Cannot match `*` without preceding char" );
  test_oracle(  printf( "%s", end ), "aaaabb", NULL, "  And end == source" );


  char_fifo = char_to_queue("a*");  
  char_list = fifo_to_list(char_fifo);

  test_assert(  re_match( char_list, "", NULL ), "Can match the empty source" ); 

  
  test_assert(  re_match( char_list, "baaaaa", &end ), "Can match zero character" ); 
  test_oracle(  printf( "%s", end ), "baaaaa", NULL, "  And end == source" ); 

  test_assert(  re_match( char_list, "abb", &end ), "Can match one character" );
  test_oracle(  printf( "%s", end ), "bb", NULL, "  And suffix is OK" ); 

  test_assert(  re_match( char_list, "aaaaaaabb", &end ), "Can match several characters" ); 
  test_oracle(  printf( "%s", end ), "bb", NULL, "  And suffix is OK" ); 
  
  test_suite( "`*` continuity" ); 

  char_fifo = char_to_queue("z*ip*");  
  char_list = fifo_to_list(char_fifo);

  test_assert(  re_match( char_list, "zipend", &end ), "Can match `*` at start of regexp" ); 
  test_oracle(  printf( "%s", end ), "end", NULL, "  And suffix is OK" ); 

  test_assert(  re_match( char_list, "zipend", &end ), "Can match `*` inside regexp" ); 
  test_oracle(  printf( "%s", end ), "end", NULL, "  And suffix is OK" ); 


  char_fifo = char_to_queue("zip*");  
  char_list = fifo_to_list(char_fifo);

  test_assert(  re_match( char_list, "zipend", &end ), "Can match `*` at end of regexp" ); 
  test_oracle(  printf( "%s", end ), "end", NULL, "  And suffix is OK" ); 

  
  fifo_delete(&char_fifo);
  
  return; 
}


static void re_dot_star( void ) { 
  fifo *char_fifo;
  list_t char_list; 
  char *end = NULL; 

  test_suite( "`.*` properties" );
  
  char_fifo = char_to_queue(".*");  
  char_list = fifo_to_list(char_fifo);


  test_assert(  re_match( char_list, "", &end ) && !*end, "`.*` matches the empty string" );   

  test_assert(  re_match( char_list, "any string ;-)", &end ) && !*end, "[Theorem] `.*` is the set of finite strings" ); 

  char_fifo = char_to_queue("abc.*");  
  char_list = fifo_to_list(char_fifo);

  test_assert(  re_match( char_list, "abcdef", &end ) && !*end, "`prefix.*` can match any prefix" ); 

  char_fifo = char_to_queue(".*def");  
  char_list = fifo_to_list(char_fifo);

  test_assert(  re_match( char_list, "abcdef", &end ) && !*end, "`.*suffix` can match any suffix" ); 

  char_fifo = char_to_queue("abc.*def");  
  char_list = fifo_to_list(char_fifo);

  test_assert(  re_match( char_list, "abcABSORBMEdefend", &end ), "[Corollary] `.*` is absorbant" ); 
  test_oracle(  printf( "%s", end ), "end", NULL, "  And suffix is OK" ); 

  fifo_delete(&char_fifo);
  
  
}

static void re_plus(void){
  fifo *char_fifo;
  list_t char_list; 
  char *end = NULL; 


  test_suite( "`+` core properties" );

  char_fifo = char_to_queue("+");  
  char_list = fifo_to_list(char_fifo);

  test_assert( !re_match( char_list, "aaaa", &end ), "Cannot match `+` at start of regexp" );
  test_oracle(  printf( "%s", end ), "aaaa", NULL, "  And end == source" );

  char_fifo = char_to_queue("a++");  
  char_list = fifo_to_list(char_fifo);

  test_assert( !re_match( char_list, "aaaabb", &end ), "Cannot match `*` without preceding char" );
  test_oracle(  printf( "%s", end ), "aaaabb", NULL, "  And end == source" );

  char_fifo = char_to_queue("a+");  
  char_list = fifo_to_list(char_fifo);

  test_assert(  !re_match( char_list, "", NULL ), "Can't match the empty source" );


  test_assert(  !re_match( char_list, "baaaaa", &end ), "Can't match zero character" ); 
  test_oracle(  printf( "%s", end ), "baaaaa", NULL, "  And end == source" );

  test_assert(  re_match( char_list, "abb", &end ), "Can match one character" );
  test_oracle(  printf( "%s", end ), "bb", NULL, "  And suffix is OK" ); 

  test_assert(  re_match( char_list, "aaaaaaabb", &end ), "Can match several characters" ); 
  test_oracle(  printf( "%s", end ), "bb", NULL, "  And suffix is OK" ); 

  test_suite( "`+` continuity" );

  char_fifo = char_to_queue("o+range*");  
  char_list = fifo_to_list(char_fifo);

  test_assert(  re_match( char_list, "ooooooorangrouge", &end ), "Can match `+` at start of regexp" ); 
  test_oracle(  printf( "%s", end ), "rouge", NULL, "  And suffix is OK" ); 

  char_fifo = char_to_queue("ora+nge*");  
  char_list = fifo_to_list(char_fifo);

  test_assert(  re_match( char_list, "oraaaaaaangeeeeeepatate", &end ), "Can match `+` inside regexp" ); 
  test_oracle(  printf( "%s", end ), "patate", NULL, "  And suffix is OK" ); 


  char_fifo = char_to_queue("orange+");  
  char_list = fifo_to_list(char_fifo);

  test_assert(  re_match( char_list, "orangeeeeeekarambit", &end ), "Can match `+` at end of regexp" ); 
  test_oracle(  printf( "%s", end ), "karambit", NULL, "  And suffix is OK" ); 

  char_fifo = char_to_queue("[0-9]+ouf");  
  char_list = fifo_to_list(char_fifo);

  test_assert(  re_match( char_list, "666oufj'ai eu chaud", &end ), "Can match `+` with a group of characters" ); 
  test_oracle(  printf( "%s", end ), "j'ai eu chaud", NULL, "  And suffix is OK" );

  char_fifo = char_to_queue("[0-9]+a*b+ZywOO");  
  char_list = fifo_to_list(char_fifo);

  test_assert(  re_match( char_list, "1999bbZywOOmeilleurjoeur", &end ), "Can match `+` with a group of characters" ); 
  test_oracle(  printf( "%s", end ), "meilleurjoeur", NULL, "  And suffix is OK" );

  
  fifo_delete(&char_fifo);
  
  return;
}

static void re_dot_plus( void ) { 
  fifo *char_fifo;
  list_t char_list; 
  char *end = NULL; 

  test_suite( "`.+` properties" );
  
  char_fifo = char_to_queue(".+");  
  char_list = fifo_to_list(char_fifo);


  test_assert(  !re_match( char_list, "", &end ) && !*end, "`.+` can't matches the empty string" );   

  test_assert(  re_match( char_list, "any string ;-)", &end ) && !*end, "[Theorem] `.+` is the set of finite strings" ); 

  char_fifo = char_to_queue("abc.+");  
  char_list = fifo_to_list(char_fifo);

  test_assert(  re_match( char_list, "abcdef", &end ) && !*end, "`prefix.+` can match any prefix" ); 

  char_fifo = char_to_queue(".+def");  
  char_list = fifo_to_list(char_fifo);

  test_assert(  re_match( char_list, "abcdef", &end ) && !*end, "`.*suffix` can match any suffix" ); 

  char_fifo = char_to_queue("abc.+def");  
  char_list = fifo_to_list(char_fifo);

  test_assert(  re_match( char_list, "abcABSORBMEdefend", &end ), "[Corollary] `.+` is absorbant" ); 
  test_oracle(  printf( "%s", end ), "end", NULL, "  And suffix is OK" ); 

  
  fifo_delete(&char_fifo);
  
  return;
}


static void re_zero_one( void ) { 
  fifo *char_fifo;
  list_t char_list; 
  char *end = NULL; 

  test_suite( "`?` properties" );

  
  
  char_fifo = char_to_queue("?");  
  char_list = fifo_to_list(char_fifo);

  test_assert(  !re_match( char_list, "", &end ) && !*end, "`?` can't be alone in a string" );   

  char_fifo = char_to_queue("a??");  
  char_list = fifo_to_list(char_fifo);

  test_assert(  !re_match( char_list, "aa", &end ), "cannot be multiple times '?' next to" );  

  char_fifo = char_to_queue("a?");  
  char_list = fifo_to_list(char_fifo);

  test_assert(  re_match( char_list, "lasuite", &end ), "'?' can matches with zero characters" ); 
  test_oracle(  printf( "%s", end ), "lasuite", NULL, "  And suffix is OK" ); 
  

  char_fifo = char_to_queue("bam?boum");  
  char_list = fifo_to_list(char_fifo);

  test_assert( re_match( char_list, "bamboumbadaboum", &end ) , " can be placed inside the string, not at the start" ); 
  test_oracle(  printf( "%s", end ), "badaboum", NULL, "  And suffix is OK" ); 

  char_fifo = char_to_queue(".?");  
  char_list = fifo_to_list(char_fifo);

  test_assert(  re_match( char_list, "Petit poids", &end ) , "'?' can be mixed with '.' " ); 
  test_oracle(  printf( "%s", end ), "etit poids", NULL, "  And suffix is OK" );

  
  fifo_delete(&char_fifo);

  return;
}

static void re_group( void ) { 
  fifo *char_fifo;
  list_t char_list; 
  char *end = NULL; 

  test_suite( "[ ] properties" );

  
  
  char_fifo = char_to_queue("[]");  
  char_list = fifo_to_list(char_fifo);

  test_assert(  !re_match( char_list, "", &end ), "Group can't be empty" );   

  //char_fifo = char_to_queue("[*]");  
  //char_list = fifo_to_list(char_fifo);

  //test_assert(  !re_match( char_list, "aaa", &end ), "Group with invalid content can't matches" ); 
  //test_oracle(  printf( "%s", end ), "aaa", NULL, "  And suffix is OK" ); 

  char_fifo = char_to_queue("[ ]");  
  char_list = fifo_to_list(char_fifo);

  test_assert(  re_match( char_list, " oula", &end ), "Group can have space character" ); 
  test_oracle(  printf( "%s", end ), "oula", NULL, "  And suffix is OK" ); 

  char_fifo = char_to_queue("[a-z][0-9]");  
  char_list = fifo_to_list(char_fifo);

  test_assert(  re_match( char_list, "g2", &end ) && !*end, "Group contains intervals of characters or numbers" ); 

  

  char_fifo = char_to_queue("99[f-y]66");  
  char_list = fifo_to_list(char_fifo);
  printf("%d", re_match( char_list, "99g66azerty", &end ) );
  test_assert( re_match( char_list, "99g66azerty", &end ) , " can be placed inside the string, not at the start" ); 
  test_oracle(  printf( "%s", end ), "azerty", NULL, "  And suffix is OK" ); 

  char_fifo = char_to_queue("[\\+\\-]");  
  char_list = fifo_to_list(char_fifo);

  test_assert( re_match( char_list, "+", &end ) && !*end, " can contains escape characters" ); 




  test_suite( "[ ] / operators properties" );

  char_fifo = char_to_queue("[\\+\\-]?[0-9]+");  
  char_list = fifo_to_list(char_fifo);

  test_assert( re_match( char_list, "1234", &end ) && !*end, " Can mix ? and +" ); 

  char_fifo = char_to_queue("[\\-\\+]?[0-9]+\\.?[0-9]*");  
  char_list = fifo_to_list(char_fifo);

  test_assert( re_match( char_list, "-1234.321", &end ) && !*end, " Can mix with regular operators" ); 

  
  fifo_delete(&char_fifo);

  

  return;
}


static void re_negation( void ) { 
  fifo *char_fifo;
  list_t char_list; 
  char *end = NULL; 

  test_suite( "^ properties" );

  
  
  char_fifo = char_to_queue("^");  
  char_list = fifo_to_list(char_fifo);

  test_assert(  !re_match( char_list, "aaa", &end ), "^ must be followed by a character" ); 
  test_oracle(  printf( "%s", end ), "aaa", NULL, "  And suffix is OK" ); 
  

  char_fifo = char_to_queue("^ ");  
  char_list = fifo_to_list(char_fifo);

  test_assert(  re_match( char_list, "adrole", &end ), "a space can be negationed ^" ); 
  test_oracle(  printf( "%s", end ), "drole", NULL, "  And suffix is OK" ); 

  char_fifo = char_to_queue("^a");  
  char_list = fifo_to_list(char_fifo);

  test_assert(  re_match( char_list, "bdrole", &end ), "^ is working Pt1" ); 
  test_oracle(  printf( "%s", end ), "drole", NULL, "  And suffix is OK" ); 

  char_fifo = char_to_queue("^a");  
  char_list = fifo_to_list(char_fifo);

  test_assert(  !re_match( char_list, "adrole", &end ), "^ is working Pt2" ); 
  test_oracle(  printf( "%s", end ), "adrole", NULL, "  And suffix is OK" ); 

  test_suite( "^ / operations properties" );

  char_fifo = char_to_queue("^a*");  
  char_list = fifo_to_list(char_fifo);

  test_assert(  re_match( char_list, "bbbbb et puis n'importe quoi finelement", &end ) && !*end, "^ With * can generate every text or nothing " ); 

  char_fifo = char_to_queue("^a+");  
  char_list = fifo_to_list(char_fifo);

  test_assert(  !re_match( char_list, "", &end ) && !*end, "^ With + can't generate nothing " ); 

  char_fifo = char_to_queue("^a?");  
  char_list = fifo_to_list(char_fifo);

  test_assert(  re_match( char_list, "", &end ) && !*end, "^ With ? can generate nothing " ); 
  test_assert(  re_match( char_list, "doppler", &end ) , "^ But also something" );
  test_oracle(  printf( "%s", end ), "oppler", NULL, "  And suffix is OK" );

  char_fifo = char_to_queue("a*^bc?^d+");  
  char_list = fifo_to_list(char_fifo);

  test_assert(  re_match( char_list, "accdefg", &end ), "^ Can be mix with different operations " ); 
  test_oracle(  printf( "%s", end ), "defg", NULL, "  And suffix is OK" );

  char_fifo = char_to_queue("^[a-k]47[a-z]");  
  char_list = fifo_to_list(char_fifo);

  test_assert(  re_match( char_list, "p47a", &end ) && !*end, "^ Can be placed before a group " ); 
  

  
  fifo_delete(&char_fifo);

  return;
}









  
  

int main ( int argc, char *argv[] ) { 

  unit_test( argc, argv );

  re_pre_post();
  re_constant();
  re_dot();
  re_star();
  re_dot_star();
  re_plus();
  re_dot_plus();
  re_zero_one();
  re_group();
  re_negation();
   
  
  exit( EXIT_SUCCESS ); 
}
