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
  CHECK
} T_Command;


typedef struct _F_Command F_Command;

/**
*	@author: Antonio Solana
*	@brief:  Checks for the user input and assigns the order required to a
*	F_Command structure
*
*	@param: *F_Command The game command
*	@return: STATUS OK or ERROR
*/
STATUS get_user_input(F_Command *);

/**
*	@author: Pablo Sánchez
*	@brief:  Creates an F_Command structure
*
*	@return: F_Command * command created
*/
F_Command * command_create();

/**
*	@author: Pablo Sánchez
*	@brief:  Destroys the F_Command given
*
*	@param: F_Command * command to destroy
*	@return: NULL
*/
void command_free(F_Command *);

/**
*	@author: Pablo Sánchez
*	@brief:  Sets the the instruction in the command
*
*	@param:	 F_Command * command to change instruction
*	@param:	 T_Command new instruction to set
*	@return: STATUS OK or ERROR
*/
STATUS command_setCmd(F_Command *, T_Command);

/**
*	@author: Pablo Sánchez
*	@brief:  Gets the the instruction in the command
*
*	@param:	 F_Command * command to get instruction
*	@return: T_Command instruction
*/
T_Command command_getCmd(F_Command * );

/**
*	@author: Pablo Sánchez
*	@brief:  Sets the the instruction parameters in the command
*
*	@param:	 F_Command * command to change instruction parameters
*	@param:	 char * new parameters to set
*	@return: STATUS OK or ERROR
*/
STATUS command_set_id(F_Command *, char *);

/**
*	@author: Pablo Sánchez
*	@brief:  Gets the the instruction parameters in the command
*
*	@param:	 F_Command * command to get instruction parameters
*	@return: char * parameters
*/
char * command_get_id(F_Command *);

#endif
