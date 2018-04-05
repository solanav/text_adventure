#include <stdio.h>
#include "link.h"
#include "types.h"

int main()
{
	Link * link_test;

	link_test = link_create(2);
	if(!link_test) goto err0;

	if(set_linkId(link_test, 3) == ERROR)
	{
		fprintf(stderr, "Error when setting Id\n");
		goto err1;
	}

	if(set_linkSpaces(link_test, 1, 2) == ERROR)
	{
		fprintf(stderr, "Error when setting space ids\n");
		goto err1;
	}

	if(set_linkStatus(link_test, OPEN) == ERROR)
	{
		fprintf(stderr, "Error when setting status");
		goto err1;
	}

	print_link(link_test);

	link_destroy(link_test);
	return 0;

	err1:
	link_destroy(link_test);
	err0:
	return 1;
}
