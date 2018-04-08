#include "inventory.h"

struct _Inventory{
Set * objects; //guarda los bjetos del inventario.
int num_MaxObj;//numero máximo de objetos que se pueden guardar.

};

Inventory * inventory_create(int num_MaxObj)
{

	Inventory *newinv = NULL;

	newinv = (Inventory *) malloc(sizeof (Inventory));
	if(newinv==NULL) return NULL;

	newinv->objects = set_create (num_MaxObj);
	newinv->num_MaxObj = num_MaxObj;

	return newinv;
}

void inventory_destroy(Inventory*inv)
{
	if(!inv) return;

	set_destroy(inv->objects);
	free(inv);
}

STATUS inventory_set_add (Inventory* inv, Id id)
{

	if (!inv) return ERROR;

	set_add(inv->objects, id);

	return OK;
}

STATUS inventory_set_del(Inventory * inv, Id id)
{
	if (!inv) return ERROR;

	set_del(inv->objects, id);

	return OK;
}
STATUS inventory_print (Inventory* inv, FILE *f)
{

	if (!inv) return ERROR;

	set_print_debug(f, inv->objects);

	return OK;
}
