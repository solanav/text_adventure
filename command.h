/**
 * @brief It implements the command interpreter
 *
 * @file command.h
 * @author Profesores PPROG
 * @version 1.0
 * @date 19-12-2014
 * @copyright GNU Public License
 */

#ifndef COMMAND_H
#define COMMAND_H

#include "types.h"

typedef enum enum_Command
{
  NO_CMD = -1,
  UNKNOWN,
  EXIT,
  FOLLOWING,
  PREVIOUS,
  ROLL,
  PICK_UP,
  DROP
} T_Command;

typedef struct _F_Command F_Command;

F_Command * get_user_input();

F_Command * command_create(T_Command, Id);

STATUS command_setCmd(F_Command *,T_Command);

T_Command command_getCmd(F_Command * );

Id command_getId(F_Command *);

STATUS command_setId(F_Command *, Id);

void command_free(F_Command *);

#endif
