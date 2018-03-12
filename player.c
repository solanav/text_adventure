#include <string.h>

#include "player.h"
#include "object.h"
#include "set.h"

struct _Player {
  char name[STDSIZE];
  Id location_id;
  Set * inventory;
  Id id;
};

Player * player_create(char * name, Id location_id, Id object_id, Id id)
{
	/**
	 * Returns null if no name is given to the player
	 * Returns pointer to the newly created player if ok
	 *
	**/
	Player * new_player;
	new_player = (Player *) calloc(1, sizeof(Player));

	if (!name) return NULL;

	strcpy(new_player->name, name);
	new_player->location_id = location_id;
	new_player->id = id;

	new_player->inventory = set_create(4);

	return new_player;
}

void player_destroy(Player *player)
{
  if(!player) return;

  set_destroy(player->inventory);
  free(player);
}


STATUS player_setName(Player * player, char * newName)
{
	if(!player||!newName) return ERROR;

	if(!strcpy(player->name, newName)) return ERROR;

	return OK;
}

STATUS player_setLocId(Player * player, Id new_locId)
{
	if(!player) return ERROR;

	player->location_id = new_locId;

	return OK;
}

STATUS player_setObjId(Player * player, Id new_objId)
{
	if(!player) return ERROR;

	set_add(player->inventory, new_objId);

	return OK;
}

STATUS player_setId(Player * player, Id new_id)
{
	if(!player) return ERROR;
 	player->id = new_id;

	return OK;
}

char * player_getName(Player * player)
{
	if(!player) return NULL;

	return player->name;
}

Id player_getLocId(Player * player)
{
	if(!player) return NO_ID;

	return player->location_id;
}

Id player_getObjId(Player * player, int num)
{
	if(!player) return NO_ID;

	return set_get_id(player->inventory, num);
}

Id player_getId(Player * player)
{
	if(!player) return NO_ID;

	return player->id;
}

STATUS player_removeObjId(Player * player, Id id)
{
	if (!player) return ERROR;

	set_del(player->inventory, id);

	return OK;
}
