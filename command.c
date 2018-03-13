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
#define N_CMD 10

struct _F_Command
{
  T_Command text;
  Id id;
};

char *cmd_to_str[N_CMD] = {"No command", "Unknown", "Exit", "Following", "Previous", "Pickup", "Drop", "Roll", "Left", "Right"};
char *short_cmd_to_str[N_CMD] = {"","","e","f","p", "u", "d", "r", "<", ">"};


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

STATUS get_user_input(F_Command * command)
{
  Id id;
  int i = UNKNOWN, command_found = 0;
  char string[CMD_LENGHT], input[CMD_LENGHT];

  if(fgets(input, CMD_LENGHT, stdin) != NULL && input[0] != '\n')
  {
    if(sscanf(input, "%s", string))
    {
      for(i = 0; i < N_CMD && command_found == 0; i++)
      {
	  	printf("Comparing %s to %s or %s\n", string, short_cmd_to_str[i], cmd_to_str[i]);
        if((strcasecmp(string, short_cmd_to_str[i]) == 0 || strcasecmp(string, cmd_to_str[i]) == 0))
        {
		  printf("\tSetting parameter CMD of command to -> %d\n", i+NO_CMD);
          command_setCmd(command, i + NO_CMD);
		  command_found = 1;
        }
      }
    }
	  if (command_found == 0)
	  {
	  	printf("\tNot found the command, returning unknown");
	  	command_setCmd(command, UNKNOWN);
    }



	printf("\nCommand -> %d\n", command_getCmd(command));
	printf("\tPICK_UP -> %d\n", PICK_UP);
	printf("\tDROP    -> %d\n", DROP);
	printf("\tROLL    -> %d\n", ROLL);

    if(command_getCmd(command) == PICK_UP || command_getCmd(command) == DROP)
    {
	  printf("Looks like your command was either PICKUP or DROP? or not\n");
      sscanf(input, "%s %ld", string, &id);
      command_setId(command, id);
    }
  }
  else
  {
    /*Invalid fgets setting cmd to UNKNOWN*/
    command_setCmd(command, UNKNOWN);
  }

  return OK;
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
  printf("Someone is setting a command to %d\n", command);
  cmd->text = command;
  return OK;
}

T_Command command_getCmd(F_Command * cmd)
{
  if(!cmd) return NO_CMD;
  printf("Trying to get command -> %d\n", cmd->text);
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
