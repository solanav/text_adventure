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

typedef struct _F_Command F_Command;

STATUS get_user_input(F_Command *);

F_Command *command_create();
void command_free(F_Command *);

STATUS command_setCmd(F_Command *, T_Command);
T_Command command_getCmd(F_Command *);

STATUS command_set_id(F_Command *, char *);
char *command_get_id(F_Command *);

void command_free(F_Command *);

#endif
