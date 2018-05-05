/**
 * @brief Defines input independent actions
 *
 * @file game_rules.c
 * @author Antonio Solana
 * @copyright GNU Public License
 */

#include <stdio.h>
#include <stdlib.h>

#include "../include/game_rules.h"

struct _Rule_Data
{
	int move_count; /*!< Counts movement from the player*/
	int die_val;    /*!< Val of die*/
};

Rule_Data *rules_create()
{
	Rule_Data *rule_data = (Rule_Data *)calloc(1, sizeof(Rule_Data));

	rule_data->move_count = 0;
	rule_data->die_val = 0;

	return rule_data;
}

void rules_destroy(Rule_Data *rule_data)
{
	if (rule_data)
		free(rule_data);
}

STATUS rules_setMoveCount(Rule_Data *rule_data, int count)
{
	if (!rule_data)
		return ERROR;

	rule_data->move_count = count;
	return OK;
}

int rules_getMoveCount(Rule_Data *rule_data)
{
	if (!rule_data)
		return ERROR;

	return rule_data->move_count;
}

STATUS rules_setDieVal(Rule_Data *rule_data, short dieval)
{
	if (!rule_data)
		return ERROR;

	rule_data->die_val = dieval;
	return OK;
}

int rules_getDieVal(Rule_Data *rule_data)
{
	if (!rule_data)
		return ERROR;

	return rule_data->die_val;
}
