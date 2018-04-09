#include "../include/die.h"

struct _Die
{
  Id id;
  short int result;
};

Die* die_ini(Id id)
{
  Die* die;

  die = calloc(1, sizeof(Die));
  if(!die) return NULL;

  die->id = id;

  return die;
}

void die_die_die(Die* die)
{
  if(!die) return;

  free(die);
}

STATUS die_roll(Die* die)
{
  if(!die) return ERROR;
  srand(time(NULL));

  die->result = (rand()%6)+1;

  return OK;
}

STATUS die_print(FILE* f, Die* die)
{
  if(!f || !die) return ERROR;

  fprintf(f, "Dice Id: %ld\n", die->id);
  fprintf(f, "Stored result: %d\n", die->result);

  return OK;
}

short int die_get_last_roll(Die * die)
{
  if(!die) return -1;

  return die->result;
}
