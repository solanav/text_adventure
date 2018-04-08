#ifndef GAME_READER_H
#define GAME_READER_H

#include "types.h"
#include "game.h"

STATUS game_load_spaces(Game* game, char* filename);
STATUS game_load_links (Game* game, char* filename);

#endif
