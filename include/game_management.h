/**
 * @brief Reads data for the game from files
 *
 * @file game_reader.h
 * @author Catalín Rotaru
 * @copyright GNU Public License
 */

#ifndef GAME_READER_H
#define GAME_READER_H

#include "../include/types.h"
#include "../include/game.h"
#include "../include/command.h"
#include "../include/space.h"
#include "../include/object.h"
#include "../include/player.h"
#include "../include/die.h"
#include "../include/link.h"
#include "../include/inventory.h"

STATUS game_load(Game* game, char * filename);
STATUS game_save(Game * game, char * filename);
STATUS game_load_saved_game(Game * game, char * filename);

#endif
