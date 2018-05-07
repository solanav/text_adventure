/**
 * @brief Creates the links between spaces
 *
 * @file link.h
 * @author Pablo Sánchez Redondo
 * @copyright GNU Public License
 */

#ifndef LINK
#define LINK

#include "../include/types.h"

#define MAX_LINK 1024

typedef struct _Link Link;

/**
*	@author: Pablo Sánchez
*	@brief: Allocs memory for one link
*	@param: Null
*	@return: a Link
*/
Link *link_create(Id);

/**
*	@author: Pablo Sánchez
*	@brief: Frees the Link
*	@param: *Link
*	@return: void
*/
void link_destroy(Link *);

/**
*	@author: Pablo Sánchez
*	@brief: Changes the link id to the given one
*	@param: *Link Id
*	@return: OK or ERROR
*/
STATUS link_setId(Link *, Id);

/**
*	@author: Pablo Sánchez
*	@brief: Changes the Link status to OPENED or CLOSED
*	@param: *Link LinkStatus
*	@return: OK or ERROR
*/
STATUS link_setStatus(Link *, LinkStatus);

/**
*	@author: Pablo Sánchez
*	@brief: Sets the spaces the link is joining
*	@param: *Link two spaces ids
*	@return: OK or ERROR
*/
STATUS link_setSpaces(Link *, Id, Id);

/**
*	@author: Pablo Sánchez
*	@brief: Gets the links id
*	@param: *Link
*	@return: link->id
*/
Id link_getId(Link *);

/**
*	@author: Pablo Sánchez
*	@brief: Gets the links name
*	@param: *Link
*	@return: link->name
*/
char * link_getName(Link *);

/**
*	@author: Pablo Sánchez
*	@brief: Gets the first Space of the link
*	@param: *Link
*	@return: link->space1
*/
Id link_getSpace1(Link *);

/**
*	@author: Pablo Sánchez
*	@brief: Gets the second Space of the link
*	@param: *Link
*	@return: link->space2
*/
Id link_getSpace2(Link *);

/**
*	@author: Pablo Sánchez
*	@brief: Gets the status the given link is in
*	@param: *Link
*	@return: OPENED or CLOSED
*/
LinkStatus link_getStatus(Link *);

/**
*	@author: Pablo Sánchez
*	@brief: Gets the other space the link is connecting
*	@param: *Link space_id
*	@return: space_id
*/
Id link_getDestination(Link *, Id);

/**
*	@author: Antonio Solana
*	@brief: Gets the direction of the link (relative to space1)
*	@param: *Link space_id
*	@return: space_id
*/
Id link_getDirection(Link *);

/**
*	@author: Antonio Solana
*	@brief: Sets the direction of the link (relative to space1)
*	@param: *Link space_id
*	@param: int 0 [north] 1 [east] 2 [south] 3 [west]
*	@return: space_id
*/
STATUS link_setDirection(Link *, int);

/**
*	@author: Pablo Sánchez
*	@brief: [DEBUG ONLY] prints the given link in stdout
*	@param: *Link
*	@return: OK or ERROR, printed the link;
*/
STATUS link_print(Link *);

#endif
