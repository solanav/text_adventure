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

/**
*	@author Antonio Solana
*	@brief Stores the input given into a command
*	@param F_Command* where the command is stored
*	@return STATUS OK or ERROR
*/
STATUS get_user_input(F_Command *);

/**
*	@author Pablo Sánchez
*	@brief Creates a new F_Command structure
*	@return F_Command* new
*	@exception Broken calloc
*/
F_Command *command_create();

/**
*	@author Pablo Sánchez
*	@brief Frees the F_Command structure
*	@param F_Command to free
*/
void command_free(F_Command *);

/**
*	@author Pablo Sánchez
*	@brief Sets the T_Command to the one given
*	@param F_Command *
*	@param T_Command
*	@return STATUS OK or ERROR
*	@exception No F_Command or value NULL
*/
STATUS command_setCmd(F_Command *, T_Command);

/**
*	@author Pablo Sánchez
*	@brief Gets the T_Command stored in the F_command
*	@param F_Command*
*	@return T_Command
*	@exception No F_Command or value NULL
*/
T_Command command_getCmd(F_Command *);

/**
*	@author Pablo Sánchez
*	@brief Sets the parameters of the command given
*	@param F_Command*
*	@param char* parameters
*	@return STATUS OK or ERROR
*	@exception NO F_Command or value NULL
*/
STATUS command_set_id(F_Command *, char *);

/**
*	@author Pablo Sánchez
*	@brief Gets the parameters stored in the F_Command
*	@param F_Command*
*	@return char* parameters
*	@exception No F_Command or value NULL
*/
char *command_get_id(F_Command *);

#endif
