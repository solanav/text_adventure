#ifndef GAME_READER_H
#define GAME_READER_H

#include "types.h"
#include "game.h"

typedef struct _Game Game;

STATUS game_load_spaces(Game* game, char* filename);
STATUS game_add_space(Game* game, Space* space);
Id     game_get_space_id_at(Game* game, int position);
STATUS game_set_player_location(Game* game, Id id);
STATUS game_set_object_location(Game* game, Id id);

#endif
