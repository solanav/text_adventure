#ifndef LINK
#define LINK

#include "game.h"

typedef struct _Link Link;

Link * link_create(Id);
void link_destroy(Link *);

STATUS set_linkId(Link *, Id);
STATUS set_spacesId(Game *, Link *, Id, Id);
STATUS set_linkStatus(Link *, LinkStatus);

Id get_linkId(Link *);
Id get_linkspace1(Link *);
Id get_linkspace2(Link *);
LinkStatus get_linkStatus(Link *);

STATUS print_link(Link *);

#endif
