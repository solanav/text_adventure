/**
 * @brief Commands and user input
 *
 * @file command.c
 * @author Antonio Solana
 * @copyright GNU Public License
 */

#include <stdio.h>
#include <strings.h>

#include "../include/command.h"

#define CMD_LENGHT 30
#define N_CMD 10

struct _F_Command
{
  T_Command text; /*!< Instruction*/
  char id[CMD_LENGHT];/*!< Parameter*/
};

char *cmd_to_str[N_CMD] = {"No command", "Unknown", "Exit", "Pickup", "Drop", "Roll", "Move", "Check", "Save", "Load"};
char *short_cmd_to_str[N_CMD] = {"", "", "e", "p", "d", "r", "m", "c", "s", "l"};

STATUS get_user_input(F_Command * command)
{
	T_Command aux_command;
	int i = UNKNOWN, command_found = 0;
	char string0[CMD_LENGHT] = {0}, string1[CMD_LENGHT] = {0}, input[CMD_LENGHT] = {0};

	if(fgets(input, CMD_LENGHT, stdin) != NULL && input[0] != '\n')
	{
		/* Check what command the user is giving */
		if(sscanf(input, "%s\n", string0) != 1)
		{
			printf("Invalid input");
			command_setCmd(command, UNKNOWN);
			return ERROR;
		}

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

		sscanf(input, "%s %s\n", string0, string1);
		/* Command requires an string */
		aux_command = command_getCmd(command);
		if(aux_command == PICK_UP || aux_command == DROP || aux_command == SAVE || aux_command == LOAD)
		{
			command_set_id(command, string1);
			printf("\tCommand requires parameters. Setting id to %s.\n", command_get_id(command));
		}

		/* Command requires a string */
		if(aux_command == MOVE)
		{
			printf("\tCommand is move. Setting id. [%s %s]\n", string0, string1);

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

		/* Command requires a string */
		if(aux_command == CHECK)
		{
			printf("\tCommand is check. Setting id. [%s %s]\n", string0, string1);
			if (strcasecmp(string1, "space")==0 || strcasecmp(string1, "s")==0)
				command_set_id(command, "space");
		 	else
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

  printf("COMMAND");

  command = calloc(1, sizeof(F_Command));
  command->text = UNKNOWN;

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

char * command_get_id(F_Command * cmd)
{
  if(!cmd) return NULL;

  return cmd->id;
}

STATUS command_set_id(F_Command * cmd, char * string)
{
  printf("Trying to set command id to -> %s\n", string);
  if(!cmd || !string) return ERROR;
  printf("Done\n");
  strcpy(cmd->id, string);
  return OK;
}

void command_free(F_Command * cmd)
{
  if(!cmd) return;

  free(cmd);
}
