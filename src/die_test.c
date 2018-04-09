#include <stdio.h>
#include "../include/die.h"


int main() {
  Die* die;
  STATUS check;

  die = die_ini(56);
  if(!die)
  {
    printf("Error when creating dice\n");
    goto error0;
  }

  if(die_roll(die) == ERROR) goto error1;


  check = die_print(stdout, die);
  if(check == ERROR)
  {
    printf("Error when printing\n");
    goto error1;
  }

  die_die_die(die);
  return 0;

/*Error time!*/
  error1:
    die_die_die(die);
  error0:
    return -1;

}
