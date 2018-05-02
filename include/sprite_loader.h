/**
 * @brief Reads the sprites from a file
 *
 * @file sprite_loader.h
 * @author Antonio Solana
 * @copyright GNU Public License
 */

#ifndef SPRITE_LOADER_H
#define SPRITE_LOADER_H

#include "../include/types.h"
#include "../include/game.h"

STATUS sprite_loader_map(Game* game, char* filename);

#endif
