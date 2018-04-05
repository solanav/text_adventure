#include <stdio.h>
#include <stdlib.h>
#include "link.h"

struct _Link
{
	Id linkId;
	Id linkspace1, linkspace2;
	LinkStatus door;
};

Link * link_create(Id id)
{
	Link * l;

	if(id == NO_ID) return NULL;

	l = (Link *)calloc(1, sizeof(Link));

	if(!l) return NULL;

	l->linkId = id;

	return l;
}

void link_destroy(Link * l)
{
	if(!l) return;

	free(l);
}

STATUS set_linkId(Link * l, Id id)
{
	if(!l) return ERROR;

	l->linkId = id;

	return OK;
}

STATUS set_spacesId(Game* g, Link * l, Id space1, Id space2)
{
	if(!g || !l || space1 == NO_ID || space2 == NO_ID) return ERROR;

	if(game_areSpacesAdjacent(g, space1, space2) == TRUE)
	{
		l->linkspace1 = space1;
		l->linkspace2 = space2;
		return OK;
	}

	return ERROR;
}

STATUS set_linkStatus(Link * l, LinkStatus door)
{
	if(!l) return ERROR;

	l->door = door;

	return OK;
}

Id get_linkId(Link * l)
{
	if(!l) return NO_ID;

	return l->linkId;
}

Id get_linkspace1(Link * l)
{
	if(!l) return NO_ID;

	return l->linkspace1;
}

Id get_linkspace2(Link * l)
{
	if(!l) return NO_ID;

	return l->linkspace2;
}

LinkStatus get_linkStatus(Link * l)
{
	if(!l) return NO_LINK;

	return l->door;
}

/*ONLY FOR DEBUGGING*/

STATUS print_link(Link * link)
{
	if(!link) return ERROR;

	printf("Link id: %ld\n", link->linkId);
	printf("First space id: %ld\n", link->linkspace1);
	printf("Second space id: %ld\n", link->linkspace2);
	if(link->door == OPEN)
		printf("Link status: OPEN");
	if(link->door == CLOSED)
		printf("Link status: CLOSED");

	return OK;
}

Id get_linkDestination(Link * l, Id originId)
{
	if(!l) return NO_ID;

	if(originId == l->linkspace1)
		return l->linkspace2;
	else if(originId == l->linkspace2)
		return l->linkspace1;
	else
		return NO_ID;
}
