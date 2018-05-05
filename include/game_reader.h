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

/**
*	@author Catalín Rotaru
*	@brief Loads the game from a file
*	@param Game*
*	@param char* filename
*	@return STATUS OK or ERROR
*	@exception No game or error when opening
*/
STATUS game_load_spaces(Game* game, char* filename);

/**
*	@author Antonio Solana
*	@brief Loads links from a file
*	@param Game*
*	@param char* filename
*	@return STATUS OK or ERROR
*	@exception No game or error at open
*/
STATUS game_load_links (Game* game, char* filename);

#endif
