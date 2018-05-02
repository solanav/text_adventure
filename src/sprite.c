/**
 * @brief It declares the sprite module
 *
 * @file sprite.c
 * @author Antonio Solana
 * @copyright GNU Public License
 */

#include "../include/sprite.h"

struct _Sprite
{
	Id id;		   /*!< Id del sprite*/
	char data[17][39]; /*!< Datos en ascii*/
};

Sprite *sprite_create(Id id)
{
	Sprite *sprite;
	int i;

	sprite = (Sprite *)calloc(1, sizeof(Sprite));

	if (!sprite)
		return NULL;

	sprite->id = id;

	for (i = 0; i < 16; i++)
	{
		sprite->data[i][0] = '\0';
	}

	return sprite;
}

void sprite_destroy(Sprite *sprite)
{
	if (sprite)
		free(sprite);
}

Id sprite_getId(Sprite *sprite)
{
	if (!sprite)
		return NO_ID;

	return sprite->id;
}

char *sprite_getData(Sprite *sprite, int line)
{
	if (!sprite)
		return NULL;

	return sprite->data[line];
}

STATUS sprite_putLine(Sprite *sprite, char *string, int line)
{
	if (!sprite)
		return ERROR;

	strncpy(sprite->data[line], string, 38);

	return OK;
}

void sprite_print(Sprite *sprite)
{
	int i;

	for (i = 0; i < 17; i++)
	{
		printf("%s\n", sprite->data[i]);
	}
}