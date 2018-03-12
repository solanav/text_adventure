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
#include "command.h"

#define CMD_LENGHT 30
#define N_CMD 8

struct _F_Command
{
  T_Command text;
  char name[1024];
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
  char string[CMD_LENGHT], input[CMD_LENGHT], str[20];
  F_Command * command = command_create(NO_CMD, "no_name");

  if(fgets(input, CMD_LENGHT, stdin) != NULL)
  {
    if(sscanf(input, "%s", string))
    {
      for(i = 0; i < N_CMD; i++)
      {
        if(strcasecmp(string, short_cmd_to_str[i]) || strcasecmp(string, cmd_to_str[i]))
        {
          command_setCmd(command, i);
        }
      }
    }
    if(command_getCmd(command) == PICK_UP || command_getCmd(command) == DROP)
    {
      sscanf(input, "%s %s", string, str);
      command_setCmd(command, i);
      command_setName(command, str);
    }
    return command;
  }

  return command;
}

F_Command * command_create(T_Command cmd, char * name)
{
  F_Command * command;

  command = calloc(1, sizeof(F_Command));
  command->text = cmd;

  strcpy(command->name, name);

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

char * command_getName(F_Command * cmd)
{
  if(!cmd) return NULL;

  return cmd->name;
}

STATUS command_setName(F_Command * cmd, char * str)
{
  if(!cmd) return ERROR;

  strcpy(cmd->name, str);
  return OK;
}

void command_free(F_Command * cmd)
{
  if(!cmd) return;

  free(cmd);
}
