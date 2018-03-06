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

F_Command get_user_input()
{
  F_Command cmd = NO_CMD;
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

F_Command command_create(T_Command cmd, Id id)
{
  F_Command command;

  command.text = cmd;
  command.id = id;

  return command;
}

F_Command input_read(char* input)
{
  int i;
  char string[CMD_LENGHT];
  Id id;
  F_Command command=command_create(NO_CMD, NO_ID);

  if(!sscanf(input, "%s", string)) return command;
  while(i < N_CMD)
  {
    if()
  }
}
