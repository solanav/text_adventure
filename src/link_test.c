#include <stdio.h>

#include "../include/link.h"
#include "../hdr/types.h"

int main()
{
	Link * link_test;

	link_test = link_create(2);
	if(!link_test) goto err0;

	if(link_setId(link_test, 3) == ERROR)
	{
		fprintf(stderr, "Error when setting Id\n");
		goto err1;
	}

	if(link_setSpaces(link_test, 1, 2) == ERROR)
	{
		fprintf(stderr, "Error when setting space ids\n");
		goto err1;
	}

	if(link_setStatus(link_test, OPEN) == ERROR)
	{
		fprintf(stderr, "Error when setting status");
		goto err1;
	}

	link_print(link_test);

	link_destroy(link_test);
	return 0;

	err1:
	link_destroy(link_test);
	err0:
	return 1;
}
