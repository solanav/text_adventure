/**
 * @brief It implements the command interpreter
 *
 * @file command.c
 * @author Profesores PPROG
 * @version 1.0
 * @date 19-12-2014
 * @copyright GNU Public License
 */

#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include "command.h"

#define CMD_LENGHT 30
#define N_CMD 8

struct _F_Command
{
  T_Command text;
  Id id;
};

char *cmd_to_str[N_CMD] = {"No command", "Unknown", "Exit", "Following", "Previous", "Pickup %ld", "Drop %ld", "Roll"};
char *short_cmd_to_str[N_CMD] = {"","","e","f","p", "u %ld", "d %ld", "r"};


/* LAST get_user_input FUCTION; NOW OBSOLETE, TODO: DELETE WHEN SURE
F_Command get_user_input()
{
  F_Command cmd = command_create(NO_CMD, NO_ID);
  char input[CMD_LENGHT] = "";
  int i=UNKNOWN - NO_CMD + 1;

  if ((input = fgets(stdout)) > 0)
  {
    cmd = UNKNOWN;
    while(cmd == UNKNOWN && i < N_CMD)
    {
      if (!strcasecmp(input,short_cmd_to_str[i]) || !strcasecmp(input,cmd_to_str[i]))
      {
        cmd = i + NO_CMD;
      }
      else
      {
        i++;
      }
    }
  }
  return cmd;
}
*/

F_Command * get_user_input()
{
  int i = UNKNOWN - NO_CMD + 1;
  char string[CMD_LENGHT], input[CMD_LENGHT];
  Id id;
  F_Command * command = command_create(NO_CMD, NO_ID);

  if(fgets(input, CMD_LENGHT, stdout) != NULL) return command;

  if(!sscanf(input, "%s", string)) return command;
  while(i < (N_CMD - 2))
  {
    if(strcasecmp(string, short_cmd_to_str[i]) || strcasecmp(string, cmd_to_str[i]))
    {
      command_setCmd(command, i);
      return command;
    }
    else
    {
      i++;
    }
  }
  if(!sscanf(input, "%s %ld", string, &id))
  {
    if(i == PICK_UP || i== DROP)
    {
      command_setCmd(command, i);
      command_setId(command, id);
      return command;
    }
    else
      return command;
  }

  return command;
}

F_Command * command_create(T_Command cmd, Id id)
{
  F_Command * command;

  command = calloc(1, sizeof(F_Command));

  command->text = cmd;
  command->id = id;

  return command;
}

STATUS command_setCmd(F_Command * cmd, T_Command command)
{
  if(!cmd) return ERROR;

  cmd->text = command;
  return OK;
}

T_Command command_getCmd(F_Command * cmd)
{
  if(!cmd) return NO_CMD;

  return cmd->text;
}

Id command_getId(F_Command * cmd)
{
  if(!cmd) return NO_ID;

  return cmd->id;
}

STATUS command_setId(F_Command * cmd, Id id)
{
  if(!cmd) return ERROR;

  cmd->id = id;
  return OK;
}

void command_free(F_Command * cmd)
{
  if(!cmd) return;

  free(cmd);
}
