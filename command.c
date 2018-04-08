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
  char id[CMD_LENGHT];
};

char *cmd_to_str[N_CMD] = {"No command", "Unknown", "Exit", "Pickup", "Drop", "Roll", "Move", "Check"};
char *short_cmd_to_str[N_CMD] = {"", "", "e", "u", "d", "r", "m", "c"};

STATUS get_user_input(F_Command * command)
{
	T_Command aux_command;
	int i = UNKNOWN, command_found = 0;
	char string0[CMD_LENGHT], string1[CMD_LENGHT], input[CMD_LENGHT];

	if(fgets(input, CMD_LENGHT, stdin) != NULL && input[0] != '\n')
	{
		/* Check what command the user is giving */
		sscanf(input, "%s", string0);

		for(i = 0; i < N_CMD && command_found == 0; i++)
		{
			if((strcasecmp(string0, short_cmd_to_str[i]) == 0 || strcasecmp(string0, cmd_to_str[i]) == 0))
			{
				printf("Setting parameter CMD of command to -> %d\n", i+NO_CMD);
				command_setCmd(command, i + NO_CMD);
				command_found = 1;
			}
		}

		/* No command given */
		if (command_found == 0)
		{
			printf("\tNot found the command, returning unknown\n");
			command_setCmd(command, UNKNOWN);
		}

		sscanf(input, "%s %s", string0, string1);
		/* Command requires an string */
		aux_command = command_getCmd(command);
		if(aux_command == PICK_UP || aux_command == DROP)
		{
			command_set_id(command, string1);
			printf("\tCommand is either pick or drop. Setting id to %s.\n", command_get_id(command));
		}

		/* Command requires a string */
		if(aux_command == MOVE)
		{
			printf("\tCommand is move. Setting id.\n");
			if (strcasecmp(string1, "n")==0 || strcasecmp(string1, "north")==0)
				command_set_id(command, "north");
			else if (strcasecmp(string1, "e")==0 || strcasecmp(string1, "east")==0)
				command_set_id(command, "east");
			else if (strcasecmp(string1, "s")==0 || strcasecmp(string1, "south")==0)
				command_set_id(command, "south");
			else if (strcasecmp(string1, "w")==0 || strcasecmp(string1, "west")==0)
				command_set_id(command, "west");
			else
				command_set_id(command, NULL);
		}
		if(aux_command == CHECK)
		{
			printf("\tCommand is check. Setting id.\n");
				command_set_id(command, string1);
		}
	}
	else
	{
		/*Invalid fgets setting cmd to UNKNOWN*/
		command_setCmd(command, UNKNOWN);
	}

	return OK;
}

F_Command * command_create()
{
  F_Command * command;

  command = calloc(1, sizeof(F_Command));
  command->text = UNKNOWN;

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

char * command_get_id(F_Command * cmd)
{
  if(!cmd) return NULL;

  return cmd->id;
}

STATUS command_set_id(F_Command * cmd, char * string)
{
  if(!cmd) return ERROR;

  strcpy(cmd->id, string);
  return OK;
}

void command_free(F_Command * cmd)
{
  if(!cmd) return;

  free(cmd);
}
