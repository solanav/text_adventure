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

STATUS game_loadSpaces(Game* game, char* filename);
STATUS game_loadLinks (Game* game, char* filename);
STATUS game_loadObjects(Game* game, char* filename);
STATUS game_loadAll(Game* game, char* filename);


#endif
