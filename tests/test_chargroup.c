#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pyas/chargroup.h>
#include <unitest/unitest.h>

void test_creation_ok(void) {
  char_group* char_new=new_char_group();
  char_group group; copy_char_group(&group, *char_new);
  //free(char_new);
  printf("%zu\n",sizeof(group.characters));
  test_assert(sizeof(group.characters)/4==256,"Verification de la taille du tableau de\n presence de caratères"); //taille du tableau indicateur de presences OK
  int i;
  int verif=1; // vaut zero si l'un des element du tableau indicateur de presences ne vaut pas zero
  for(i=0;i<256;i++){
    if(group.characters[i]!=0){
      verif=0;
    }
  }
  test_assert(verif==1,"group.characters contient initialement que des zeros");
  test_assert(group.complement==0,"Complement est bien initialise");
  test_assert(group.op==ONE_TIME,"Op est est bien initialise");
}

void test_modif_ok(void) {
  char_group* char_new=new_char_group();
  char_group group; copy_char_group(&group, *char_new);
  //free(char_new);
  //Modifions
  group.characters['a']=1;
  group.characters['b']=1;
  group.characters['c']=1;
  group.complement=1;
  group.op=ONE_OR_MORE;

   test_assert(group.characters[97]==1 && group.characters[98]==1 && group.characters[99]==1,"Ajout de a, b et c");
   test_assert(group.complement==1,"Verifer que le complement a bien ete change et vaut maintenat 1");
   test_assert(group.op==ONE_OR_MORE,"Verifictions du changement effectif de l'operateur");
}

int main(int argc, char *argv[]) {
    unit_test(argc, argv);
    test_suite("bonne création d'une variable de type char_group");
    test_creation_ok();
    test_suite("les modifications sont prises en compte");
    test_modif_ok();
}
