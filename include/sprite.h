/**
* @brief It declares the sprite module
*
* @file sprite.h
* @author Antonio Solana
* @copyright GNU Public License
*/

#ifndef SPRITE_H
#define SPRITE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "types.h"

typedef struct _Sprite Sprite;

Sprite *sprite_create(Id id);
void sprite_destroy(Sprite *sprite);
Id sprite_getId(Sprite *sprite);
char *sprite_getData(Sprite *sprite, int line);
STATUS sprite_putLine(Sprite *sprite, char *string, int line);
void sprite_print(Sprite *sprite);

#endif