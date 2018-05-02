#include <stdio.h>
#include <string.h>
#include "game.h"
#include "die.h"
#include "dialogue.h"

char * dialogue_generate(Game * game)
{
	char * dialogue;
	int flag = 0;
	Die* die = die_ini(5);

	if(!game) return NULL;

	switch (CMD) {
		case NO_CMD:
			strcpy(dialogue, "Do you know what you are trying to do? This is so wrong");
			if(game_get_last_command_text(game, 0) == game_get_last_command_text(game, 1))
			{
				strcpy(dialogue, "You are sure you lived this before, weird");
			}
			return dialogue;
		case UNKNOWN:
			strcpy(dialogue, "Are you even trying?");
			if(game_get_last_command_text(game, 0) == game_get_last_command_text(game, 1))
			{
				die_roll(die);
				if(die_get_last_roll(die) < 2)
					strcpy(dialogue, "What, again?");
				else if(die_get_last_roll(die) < 4)
					strcpy(dialogue, "...");
				else
					strcpy(dialogue, "This does not seem right, again");
			}
			return dialogue;
		case PICK_UP:

	}
}
