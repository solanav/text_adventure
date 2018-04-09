/**
 * @brief Commands and user input
 *
 * @file command.h
 * @author NONAME
 * @date 2018-04-09
 * @copyright GNU Public License
 */

#ifndef GAME_READER_H
#define GAME_READER_H

#include "../include/types.h"
#include "../include/game.h"

STATUS game_load_spaces(Game* game, char* filename);
STATUS game_load_links (Game* game, char* filename);

#endif
