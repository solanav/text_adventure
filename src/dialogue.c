#include <stdio.h>
#include <string.h>
#include "../include/game.h"
#include "../include/die.h"
#include "../include/dialogue.h"

#define DIALOGUE 400

char * dialogue_generate(Game * game)
{
	char * dialogue = calloc(DIALOGUE, sizeof(char));
	char aux[DIALOGUE];
	Die* die = die_ini(5);
	T_Command CMD = game_get_last_command_text(game, 0);

	die_roll(die);

	if(!game) return NULL;

	switch (CMD) {
		case NO_CMD:
			strcpy(dialogue, "Do you know what you are trying to do? This is so wrong");
			if(game_get_last_command_text(game, 0) == game_get_last_command_text(game, 1))
			{
				strcpy(dialogue, "You are sure you lived this before, weird");
			}
			die_die_die(die);
			return dialogue;
		case UNKNOWN:
			strcpy(dialogue, "Are you even trying?");
			if(game_get_last_command_text(game, 0) == game_get_last_command_text(game, 1))
			{
				if(die_get_last_roll(die) < 2)
					strcpy(dialogue, "What, again?");
				else if(die_get_last_roll(die) < 4)
					strcpy(dialogue, "...");
				else
					strcpy(dialogue, "This does not seem right, again");
			}
			die_die_die(die);
			return dialogue;
		case PICK_UP:
			if(strcmp("you can't move that", game_get_last_command_parameters(game, 0)) == 0)
			{
				if(die_get_last_roll(die) < 2)
					strcpy(dialogue, "Won't budge");
				else if(die_get_last_roll(die) <4)
					strcpy(dialogue, "Too heavy");
				else
					strcpy(dialogue, "Can't use that");
			}
			else if(sscanf(game_get_last_command_parameters(game, 0), "%sOK", aux) != 0)
				sprintf(dialogue, "You pick %s up and put it in your bag", aux);
			else
				strcpy(dialogue, "Are you sure about that");
			die_die_die(die);
			return dialogue;
		case DROP:
			strcpy(aux, game_get_last_command_parameters(game, 0));
			if(strcmp(aux, "no") != 0)
				sprintf(dialogue, "You pick %s up and put it on the ground, you won't miss it", aux);
			else
				strcpy(dialogue, "You look in your bag but you do not find it");
			die_die_die(die);
			return dialogue;
		case ROLL:
			if(game_get_last_roll(game) == 1)
				strcpy(dialogue, "1. Limbo");
			else if(game_get_last_roll(game) == 2)
				strcpy(dialogue, "2. Lust");
			else if(game_get_last_roll(game) == 3)
				strcpy(dialogue, "3. Gluttony");
			else if(game_get_last_roll(game) == 4)
				strcpy(dialogue, "4. Greed");
			else if(game_get_last_roll(game) == 5)
				strcpy(dialogue, "5. Wrath");
			else if(game_get_last_roll(game) == 6)
				strcpy(dialogue, "6. Heresy");
			else if(game_get_last_roll(game) == 7)
				strcpy(dialogue, "7. Violence");
			else if(game_get_last_roll(game) == 8)
				strcpy(dialogue, "8. Fraud");
			else
				strcpy(dialogue, "9. Treachery");
			die_die_die(die);
			return dialogue;
		case MOVE:
			strcpy(aux, game_get_last_command_parameters(game, 0));
			if(strcmp(aux, "north") == 0)
				strcpy(dialogue, "You venture forth, north");
			else if(strcmp(aux, "west") == 0)
				strcpy(dialogue, "You finally decide to move west");
			else if(strcmp(aux, "east") == 0)
				strcpy(dialogue, "East is where you head");
			else if(strcmp(aux, "south") == 0)
				strcpy(dialogue, "Lets go south this time");
			else if(strcmp(aux, "thats closed") == 0)
				strcpy(dialogue, "Hmmm, you probably need a key");
			else
				strcpy(dialogue, "I'm pretty sure that's a wall");
			die_die_die(die);
			return dialogue;
		case CHECK:
			strcpy(dialogue, game_get_last_command_parameters(game, 0));
			die_die_die(die);
			return dialogue;
		case TURNON:
			strcpy(aux, game_get_last_command_parameters(game, 0));
			if(strcmp(aux, "no") == 0)
			{
				if(die_get_last_roll(die) < 2)
					strcpy(dialogue, "Well, that was stupid");
				else if(die_get_last_roll(die) <4)
					strcpy(dialogue, "Did you really just tried that?");
				else
					strcpy(dialogue, "That did nothing, obviously");
			}
			else
				strcpy(dialogue, "It gives some light, might be useful");
			die_die_die(die);
			return dialogue;
		case TURNOFF:
			strcpy(aux, game_get_last_command_parameters(game, 0));
			if(strcmp(aux, "no") == 0)
			{
				if(die_get_last_roll(die) < 2)
					strcpy(dialogue, "Really?");
				else if(die_get_last_roll(die) <4)
					strcpy(dialogue, "I don't think you can do that");
				else
					strcpy(dialogue, "Nice");
			}
			else
				strcpy(dialogue, "Who turned off the lights? It was you");
			die_die_die(die);
			return dialogue;
		case OPEN:
			strcpy(aux, game_get_last_command_parameters(game, 0));
			if(strcmp(aux, "no") == 0)
			{
				strcpy(dialogue, "Im pretty sure you can't open THAT");
			}
			else if(strcmp(aux, "error") == 0)
			{
				strcpy(dialogue, "It won't open, sucks to be you I guess");
			}
			else
				strcpy(dialogue, "A loud creek is heard, and the gate opens");
			die_die_die(die);
			return dialogue;
		default:
			strcpy(dialogue, "How?");
			die_die_die(die);
			return dialogue;
	}
}
