#include <stdio.h>
#include <stdlib.h>

#include "set.h"

int main()
{
	Set * test_set, * test_set_copy;
	int i, inv_size=15;
	Id j=2;

	test_set = set_create(inv_size);

	if(!test_set) goto error0;

	for(i=0; i<inv_size; i++)
	{
		if(set_add(test_set, j)==ERROR) goto error1;
		j++;
	}

	if(set_print_debug(stdout, test_set)==ERROR) goto error1;

	test_set_copy = set_cp_all(test_set);

	printf("\n################ Now we remove a couple of items\n\n");

	if(set_del(test_set, 3)==ERROR) goto error1;
	if(set_del(test_set, 7)==ERROR) goto error1;
	if(set_del(test_set, 2)==ERROR) goto error1;
	if(set_del(test_set, 8)==ERROR) goto error1;

	if(set_print_debug(stdout, test_set)==ERROR) goto error1;

	printf("\n################ Now we rearrange\n\n");

	if(set_rearrange(test_set)==ERROR) goto error1;

	if(set_print_debug(stdout, test_set)==ERROR) goto error1;

	printf("\n################ Now we remove all\n\n");

	if(set_rm_all(test_set)==ERROR) goto error1;

	if(set_print_debug(stdout, test_set)==ERROR) goto error1;

	printf("\n################ Now we print test copy\n\n");

	if(set_print_debug(stdout, test_set_copy)==ERROR) goto error1;


	printf("\nEverything works as intended, lets go!\n\n");
	return 0;

	error1:
		free(test_set);
	error0:
		return -1;
}
