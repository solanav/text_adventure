/**
 * @brief Commands and user input
 *
 * @file command.h
 * @author NONAME
 * @date 2018-04-09
 * @copyright GNU Public License
 */

#ifndef COMMAND_H
#define COMMAND_H

#include <string.h>
#include <stdlib.h>

#include "../include/types.h"

typedef enum enum_Command
{
  NO_CMD = -1,
  UNKNOWN,
  EXIT,
  PICK_UP,
  DROP,
  ROLL,
  MOVE,
  CHECK
} T_Command;

typedef struct _F_Command F_Command;

STATUS get_user_input(F_Command *);

F_Command * command_create();
void command_free(F_Command *);

STATUS command_setCmd(F_Command *, T_Command);
T_Command command_getCmd(F_Command * );

STATUS command_set_id(F_Command *, char *);
char * command_get_id(F_Command *);

void command_free(F_Command *);

#endif