/**
 * @brief Main function
 *
 * @file game.h
 * @author Bernardo Zambrano
 * @copyright GNU Public License
 */

#ifndef GAME_H
#define GAME_H

#include "../include/command.h"
#include "../include/space.h"
#include "../include/object.h"
#include "../include/player.h"
#include "../include/die.h"
#include "../include/link.h"
#include "../include/inventory.h"
#include "../include/sprite.h"
#include "../include/game_rules.h"

#define MAX_OBJECTS 1024

typedef struct _Game Game;

Game *game_create();
STATUS game_create_from_file(Game *, char *);

STATUS game_update(Game *, F_Command *);
STATUS game_destroy(Game *);

BOOL game_is_over(Game *);

void game_print_screen(Game *);
void game_print_data(Game *);

Space *game_get_space(Game *, Id);
Player *game_get_player(Game *);
Die *game_get_die(Game *game);
Object *game_get_object(Game *, char *);
Object *game_get_object_from_id(Game *game, Id id);
Link *game_get_link(Game *, Id);
Id game_get_link_id_at(Game *, int);

Id game_get_player_location(Game *);
Id game_get_object_location(Game *, Id);
Id game_get_space_id_at(Game *, int);
int game_get_last_roll(Game *);

STATUS game_add_space(Game *, Space *);
STATUS game_add_object(Game *game, Object *object);
STATUS game_set_player_location(Game *, Id);
STATUS game_set_object_location(Game *, Id, Id, char *, char *);
STATUS game_set_link(Game *, Id, Id, Id, int, LinkStatus);

STATUS game_load_spaces(Game *, char *);

F_Command *game_get_last_command(Game *, int);
T_Command game_get_last_command_text(Game *, int);
char * game_get_last_command_parameters(Game *, int);

BOOL game_areSpacesAdjacent(Game *, Id, Id);

/*
*	@author: Antonio Solana
*	@brief: Searches in sprite index for the pointer that corresponds to your id
*	@param: Game
*	@param: id of sprite
*	@return: STATUS
*/
Sprite *game_get_sprite(Game *game, Id id);

/*
*	@author: Antonio Solana
*	@brief: Adds a new sprite to game sprite index in game structure
*	@param: Game
*	@param: sprite pointer to add
*	@param: position to add it in
*	@return: STATUS
*/
STATUS game_add_sprite(Game *game, Sprite *sprite, int i);

/*
*	@author: Antonio Solana
*	@brief: Updates current sprite for every space according to rules
*	@param: Game
*	@return: STATUS
*/
STATUS update_sprites(Game *game);

/*
*	@author: Antonio Solana
*	@brief: Updates game according to rules
*	@param: Game
*	@return: STATUS
*/
STATUS update_rules(Game *game, Rule_Data *);

#endif
