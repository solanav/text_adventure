/**
 * @brief Defines input independent actions
 *
 * @file game_rules.h
 * @author Antonio Solana
 * @copyright GNU Public License
 */

#ifndef GAME_RULES_H
#define GAME_RULES_H

#include "../include/types.h"

typedef enum enum_Rules {
	NO_RULES,
	NO_LIGHT,
	GO_START,
	NO_TORCH,
	BECOME_TREE,
	GO_RAND,
	HIDE_ALL
} Rules;

typedef struct _Rule_Data Rule_Data;

/**
*	@author Antonio Solana
*	@brief Creates the rules structure
*	@return Rules_Data
*	@exception Broken calloc
*/
Rule_Data *rules_create();

/**
*	@author Antonio Solana
*	@brief Destroys the rules structure given
*	@param Rule_Data*
*/
void rules_destroy(Rule_Data *);

STATUS rules_setMoveCount(Rule_Data *rule_data, int count);
STATUS rules_setDieVal(Rule_Data *rule_data, short dieval);
int rules_getDieVal(Rule_Data *rule_data);
int rules_getMoveCount(Rule_Data *rule_data);

#endif
