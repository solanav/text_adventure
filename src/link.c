/**
 * @brief Creates the links between spaces
 *
 * @file link.c
 * @author Pablo Sánchez
 * @copyright GNU Public License
 */

#include <stdio.h>
#include <stdlib.h>

#include "../include/link.h"

struct _Link
{
	Id linkId;		   /*!< Id del link*/
	Id linkspace1, linkspace2; /*!< id de los espacios conectados*/
	int direction;		   /*!< Norte, sur, este u oeste*/
	LinkStatus door;	   /*!< Estatus del link OPENED/CLOSED*/
};

Link *link_create(Id id)
{
	Link *l;

	if (id == NO_ID)
		return NULL;

	l = (Link *)calloc(1, sizeof(Link));

	if (!l)
		return NULL;

	l->linkId = id;
	l->direction = -1;

	return l;
}

void link_destroy(Link *l)
{
	if (!l)
		return;

	free(l);
}

STATUS link_setDirection(Link *l, int direction)
{
	if (!l)
		return ERROR;

	l->direction = direction;

	return OK;
}

STATUS link_setId(Link *l, Id id)
{
	if (!l)
		return ERROR;

	l->linkId = id;

	return OK;
}

STATUS link_setStatus(Link *l, LinkStatus door)
{
	if (!l)
		return ERROR;

	l->door = door;

	return OK;
}

STATUS link_setSpaces(Link *l, Id space1, Id space2)
{
	if (!l || space1 == NO_ID || space2 == NO_ID)
		return ERROR;

	l->linkspace1 = space1;
	l->linkspace2 = space2;

	return OK;
}

Id link_getDirection(Link *l)
{
	if (!l)
		return NO_ID;

	return l->direction;
}

Id link_getId(Link *l)
{
	if (!l)
		return NO_ID;

	return l->linkId;
}

Id link_getSpace1(Link *l)
{
	if (!l)
		return NO_ID;

	return l->linkspace1;
}

Id link_getSpace2(Link *l)
{
	if (!l)
		return NO_ID;

	return l->linkspace2;
}

LinkStatus link_getStatus(Link *l)
{
	if (!l)
		return NO_LINK;

	return l->door;
}

STATUS link_print(Link *link)
{
	if (!link)
		return ERROR;

	printf("Link id: %ld\n", link->linkId);
	printf("\tFirst space id: %ld\n", link->linkspace1);
	printf("\tSecond space id: %ld\n", link->linkspace2);

	if (link->door == OPENED)
		printf("\tLink status: OPENED\n");
	if (link->door == CLOSED)
		printf("\tLink status: CLOSED\n");

	return OK;
}

Id link_getDestination(Link *l, Id originId)
{
	if (!l)
		return NO_ID;

	if (originId == l->linkspace1)
		return l->linkspace2;
	else if (originId == l->linkspace2)
		return l->linkspace1;
	else
		return NO_ID;
}
