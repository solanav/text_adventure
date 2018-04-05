#ifndef LINK
#define LINK

#include "game.h"

#define MAX_LINK 100

typedef struct _link Link;

Link * link_create(Id);
void link_destroy(Link *);

STATUS set_linkId(Link *, Id);
STATUS set_spacesId(Game *, Link *, Id, Id);
STATUS set_linkStatus(Link *, LinkStatus);

Id get_linkId(Link *);
Id get_linkspace1(Link *);
Id get_linkspace2(Link *);
LinkStatus get_linkStatus(Link *);

Id get_linkDestination(Link *, Id );

STATUS print_link(Link *);

#endif
