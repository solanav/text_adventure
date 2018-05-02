/**
 * @brief It declares the die module
 *
 * @file die.c
 * @author Pablo Sánchez Redondo
 * @copyright GNU Public License
 */

#include "../include/die.h"

struct _Die
{
  Id id; /*!< Id del dado*/
  short int result; /*!< Valor de la ultima tirada*/
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

  die->result = (rand()%9)+1;

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
