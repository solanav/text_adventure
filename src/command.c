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
#define N_CMD 11

struct _F_Command
{
  T_Command text; /*!< Instruccion*/
  char id[CMD_LENGHT];/*!< Parametro*/
};

char *cmd_to_str[N_CMD] = {"No command", "Unknown", "Exit", "Pickup", "Drop", "Roll", "Move", "Check","Turn_on","Turn_off","Open"};
char *short_cmd_to_str[N_CMD] = {"", "", "e", "p", "d", "r", "m", "c","t-on","t-off","o"};

STATUS get_userInput(F_Command * command)
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
		if(aux_command == PICK_UP || aux_command == DROP)
		{
			command_setId(command, string1);
			printf("\tCommand is either pick or drop. Setting id to %s.\n", command_getId(command));
		}

		/* Command requires a string */
		if(aux_command == MOVE)
		{
			printf("\tCommand is move. Setting id. [%s %s]\n", string0, string1);

			if (strcasecmp(string1, "n")==0 || strcasecmp(string1, "north")==0)
				command_setId(command, "north");
			else if (strcasecmp(string1, "e")==0 || strcasecmp(string1, "east")==0)
				command_setId(command, "east");
			else if (strcasecmp(string1, "s")==0 || strcasecmp(string1, "south")==0)
				command_setId(command, "south");
			else if (strcasecmp(string1, "w")==0 || strcasecmp(string1, "west")==0)
				command_setId(command, "west");
			else
				command_setId(command, NULL);
		}

		/* Command requires a string */
		if(aux_command == CHECK)
		{
			printf("\tCommand is check. Setting id. [%s %s]\n", string0, string1);
			if (strcasecmp(string1, "space")==0 || strcasecmp(string1, "s")==0)
				command_setId(command, "space");
		 	else
				command_setId(command, string1);
		}

    if(aux_command == TURN_ON)
    {
      printf("\tCommand is turn on. Setting id. [%s %s]\n", string0, string1);
      if (strcasecmp(string1, "Turn-on")==0 || strcasecmp(string1, "t-on")==0)
        command_setId(command, "Turn-on");
      else
        command_setId(command, string1);
    }
    if(aux_command == TURN_OFF)
    {
      printf("\tCommand is turn off. Setting id. [%s %s]\n", string0, string1);
      if (strcasecmp(string1, "Turn-off")==0 || strcasecmp(string1, "t-off")==0)
        command_setId(command, "Turn_off");
      else
        command_setId(command, string1);
    }
    if(aux_command == OPEN)
    {
      if (strcasecmp(string1, "open")==0 || strcasecmp(string1, "o")==0)
      {
        command_setId(command, "open");
        printf("\tCommand is open <link>. Setting <object>. Open %s with %s \n", string0, string1);
    }
      else
        command_setId(command, string1);
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

void command_free(F_Command * cmd)
{
  if(!cmd) return;

  free(cmd);
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

char * command_getId(F_Command * cmd)
{
  if(!cmd) return NULL;

  return cmd->id;
}

STATUS command_setId(F_Command * cmd, char * string)
{
  printf("Trying to set command id to -> %s\n", string);
  if(!cmd || !string) return ERROR;
  printf("Done\n");
  strcpy(cmd->id, string);
  return OK;
}
