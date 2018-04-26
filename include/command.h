/**
 * @brief Commands and user input
 *
 * @file command.h
 * @author Antonio Solana
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
  CHECK,
  TURN_ON,
  TURN_OFF,
  OPEN
} T_Command;

typedef struct _F_Command F_Command;

STATUS get_userInput(F_Command *);

F_Command * command_create();
void command_free(F_Command *);

STATUS command_setCmd(F_Command *, T_Command);
T_Command command_getCmd(F_Command * );


char * command_getId(F_Command *);
STATUS command_setId(F_Command *, char *);

void command_free(F_Command *);

#endif
