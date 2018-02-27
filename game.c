/**
 * @brief It implements the game interface and all the associated callbacks
 * for each command
 *
 * @file game.c
 * @author Profesores PPROG
 * @version 1.0
 * @date 13-01-2015
 * @copyright GNU Public License
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "game.h"
#include "game_reader.h"

#define N_CALLBACK 6

/**
   Define the function type for the callbacks
*/
typedef void (*callback_fn)(Game* game);

/**
   List of callbacks for each command in the game
*/
void game_callback_unknown(Game* game);
void game_callback_exit(Game* game);
void game_callback_following(Game* game);
void game_callback_previous(Game* game);
void game_callback_pickup(Game* game);
void game_callback_drop(Game* game);
void game_callback_roll(Game* game);

static callback_fn game_callback_fn_list[N_CALLBACK]=
{
  game_callback_unknown,
  game_callback_exit,
  game_callback_following,
  game_callback_previous,
  game_callback_pickup,
  game_callback_drop,
  game_callback_roll
};

/**
   Game interface implementation
*/

STATUS game_create(Game* game)
{
  /*
   * Fill game structure with empty values
   *
   * game: the main game structure
   *
   * returns: ERROR or OK
   */
  int i;

  for (i = 0; i < MAX_SPACES; i++) {
    game->spaces[i] = NULL;
  }

  game->player = player_create("player1", NO_ID, NO_ID, 1);
  game->object = obj_create("head", 1);

  game_set_player_location(game, NO_ID);
  game_set_object_location(game, NO_ID);

  game->last_cmd = NO_CMD;

  return OK;
}

STATUS game_create_from_file(Game* game, char* filename)
{
  // Create game
  if (game_create(game) == ERROR) return ERROR;

  // Load provided file
  if (game_load_spaces(game, filename) == ERROR) return ERROR;

  printf("[DEBUG] SET OBJECT AT -> %ld\n", game_get_space_id_at(game, 4));

  game_set_player_location(game, game_get_space_id_at(game, 0));
  game_set_object_location(game, game_get_space_id_at(game, 4));

  printf("[DEBUG] PLAYER LOC    -> %ld\n", game_get_player_location(game));
  printf("[DEBUG] OBJECT LOC    -> %ld\n", game_get_object_location(game));

  return OK;
}

STATUS game_destroy(Game* game)
{
  int i = 0;

  for (i = 0; (i < MAX_SPACES) && (game->spaces[i] != NULL); i++) {
    space_destroy(game->spaces[i]);
  }

  return OK;
}



Space* game_get_space(Game* game, Id id)
{
  int i = 0;

  if (id == NO_ID) return NULL;

  for (i = 0; i < MAX_SPACES && game->spaces[i] != NULL; i++)
  {
    if (id == space_get_id(game->spaces[i])){
      return game->spaces[i];
    }
  }

  return NULL;
}

Id game_get_player_location(Game* game)
{
  return player_getLocId(game->player);
}

Id game_get_object_location(Game* game) // error here
{
  int i;

  if (!game) return NO_ID;

  // Itera por los espacios comprobando si esta el objeto que buscas
  for (i = 0; i < MAX_SPACES; i++)
  {
    if (space_get_object_id(game->spaces[i]) == obj_getId(game->object))
    {
      return space_get_id(game->spaces[i]);
    }
  }

  // Si no lo encuentra
  return NO_ID;
}

STATUS game_update(Game* game, T_Command cmd)
{
  game->last_cmd = cmd;
  (*game_callback_fn_list[cmd])(game);
  return OK;
}

T_Command game_get_last_command(Game* game)
{
  return game->last_cmd;
}

void game_print_data(Game* game)
{
  int i = 0;

  printf("\n\n-------------\n\n");

  printf("=> Spaces: \n");
  for (i = 0; i < MAX_SPACES && game->spaces[i] != NULL; i++)
  {
    space_print(game->spaces[i]);
  }

  printf("=> Object location: %d\n", (int) game_get_object_location(game));
  printf("=> Player location: %d\n", (int) game_get_player_location(game));
  printf("prompt:> ");
}

BOOL game_is_over(Game* game)
{
  return FALSE;
}

/**
   Callbacks implementation for each action
*/

void game_callback_unknown(Game* game)
{
}

void game_callback_exit(Game* game)
{
}

void game_callback_following(Game* game)
{
  int i = 0;
  Id current_id = NO_ID;
  Id space_id = NO_ID;

  space_id = game_get_player_location(game);
  if (space_id == NO_ID)
  {
    return;
  }

  for (i = 0; i < MAX_SPACES && game->spaces[i] != NULL; i++)
  {
    current_id = space_get_id(game->spaces[i]);
    if (current_id == space_id)
    {
      current_id = space_get_south(game->spaces[i]);
      if (current_id != NO_ID)
      {
	      game_set_player_location(game, current_id);
      }
      return;
    }
  }
}

void game_callback_previous(Game* game)
{
  int i = 0;
  Id current_id = NO_ID;
  Id space_id = NO_ID;

  space_id = game_get_player_location(game);

  if (NO_ID == space_id)
  {
    return;
  }

  for (i = 0; i < MAX_SPACES && game->spaces[i] != NULL; i++)
  {
    current_id = space_get_id(game->spaces[i]);
    if (current_id == space_id)
    {
      current_id = space_get_north(game->spaces[i]);
      if (current_id != NO_ID)
      {
	      game_set_player_location(game, current_id);
      }
      return;
    }
  }
}

void game_callback_pickup(Game* game)
{
  Id playerloc_id = game_get_player_location(game);
  Id objectloc_id = game_get_object_location(game);

  if(objectloc_id == NO_ID)return;

  if (playerloc_id == objectloc_id)
  {
    player_setObjId(game->player, obj_getId(game->object));
    space_set_object_id(game_get_space(game, playerloc_id), NO_ID);
    return;
  }
}

void game_callback_drop(Game* game)
{
  Id playerloc_id = game_get_player_location(game);
  Id obj_id = player_getObjId(game->player);

  if(obj_id == NO_ID) return;

  space_set_object_id(game_get_space(game, playerloc_id), obj_id);
  player_setObjId(game->player, NO_ID);
}

void game_callback_roll(Game* game)
{
}

STATUS game_add_space(Game* game, Space* space)
{
  int i = 0;

  if (space == NULL) return ERROR;

  while ( (i < MAX_SPACES) && (game->spaces[i] != NULL))
  {
    i++;
  }

  if (i >= MAX_SPACES) return ERROR;

  game->spaces[i] = space;

  return OK;
}

Id game_get_space_id_at(Game* game, int position)
{

  if (position < 0 || position >= MAX_SPACES) return NO_ID;

  return space_get_id(game->spaces[position]);
}

STATUS game_set_player_location(Game* game, Id id)
{
  /*
   * Sets player location to "id"
   *
   * game: the main game structure
   * id: new location for player
   *
   * returns: ERROR or OK
   */

  if (id == NO_ID) return ERROR;

  player_setLocId(game->player, id);

  return OK;
}

STATUS game_set_object_location(Game* game, Id id)
{
  /*
   * Sets object location to "id"
   *
   * game: the main game structure
   * id: new location for object
   *
   * returns: ERROR or OK
   */

  int i;

  if (id == NO_ID || !game) return ERROR;

  for (i = 0; i < MAX_SPACES; i++)
  {
    if (space_get_id(game->spaces[i]) == id)
    {
      space_set_object_id(game->spaces[i], obj_getId(game->object));
      printf("%p - %p\n", game->object, game->object);
      printf("-> %ld\n", game_get_object_location(game));
      return OK;
    }
  }

  return ERROR;
}
