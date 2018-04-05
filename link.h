#ifndef LINK
#define LINK

#include "types.h"

#define MAX_LINK 100

typedef struct _link Link;

Link * link_create(Id);
void link_destroy(Link *);

STATUS link_setId(Link *, Id);
STATUS link_setStatus(Link *, LinkStatus);
STATUS link_setSpaces(Link *, Id, Id);

Id link_getId(Link *);
Id link_getSpace1(Link *);
Id link_getSpace2(Link *);
LinkStatus link_getStatus(Link *);

Id link_getDestination(Link *, Id );

STATUS link_print(Link *);

#endif
