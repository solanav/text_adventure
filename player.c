#include <string.h>
#include "player.h"
#include "object.h"

struct _Player {
  char name[STDSIZE];
  Id location_id;
  Id object_id;
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
	new_player = (Player *) malloc(sizeof(Player));

	if (!name) return NULL;

	strcpy(new_player->name, name);
	new_player->location_id = location_id;
	new_player->object_id = object_id;
	new_player->id = id;

	return new_player;
}


Player * player_setName(Player * player, char * newName)
{
	if(!player||!newName) return NULL;

	strcpy(player->name, newName);

	return player;
}

Player * player_setLocId(Player * player, Id new_locId)
{
	if(!player) return NULL;

	player->location_id = new_locId;

	return player;
}

Player * player_setObjId(Player * player, Id new_objId)
{
	if(!player) return NULL;

	player->object_id = new_objId;

	return player;
}

Player * player_setId(Player * player, Id new_id)
{
	if(!player) return NULL;

	player->id = new_id;

	return player;
}

char * player_getName(Player * player)
{
	if(!player) return NULL;

	return player->name;
}

Id player_getLocId(Player * player)
{
	if(!player) return -1;

	return player->location_id;
}

Id player_getObjId(Player * player)
{
	if(!player) return -1;

	return player->object_id;
}

Id player_getId(Player * player)
{
	if(!player) return -1;

	return player->id;
}
