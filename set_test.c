#include <stdio.h>
#include <stdlib.h>

#include "set.h"

int main()
{
	Set * test_set;
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
	
	printf("\n################ Now we remove last item\n\n");

	if(set_pick(test_set, 3)==ERROR) goto error1;

	if(set_print_debug(stdout, test_set)==ERROR) goto error1;

	printf("\n################ Now we remove all\n\n");

	if(set_rm_all(test_set)==ERROR) goto error1;

	if(set_print_debug(stdout, test_set)==ERROR) goto error1;

	/*if(set_print_debug(stdout, test_set)==ERROR) goto error1;
	*/	
	return 0;

	error1:
		free(test_set);
	error0:
		return -1;
}
