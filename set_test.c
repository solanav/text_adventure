#include <stdio.h>
#include <stdlib.h>

#include "set.h"

int main()
{
	Set * test_set;
	int i;
	Id j=2;

	test_set = set_create();
	if(!test_set) goto error0;

	for(i=0; i<10; i++)
	{
		if(set_add(test_set, j)==ERROR) goto error1;
		j++;
	}

	j = 4;

	if(set_del(test_set, j)==ERROR) goto error1;

	if(set_print(stdout, test_set)==ERROR) goto error1;
	return 0;

	error1:
		free(test_set);
	error0:
		return -1;
}
