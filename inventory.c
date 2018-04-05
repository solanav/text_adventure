#include "inventory.h"

struct _Inventory{
Set * objects; //guarda los bjetos del inventario.
int num_MaxObj;//numero máximo de objetos que se pueden guardar.

};

Inventory * inventory_create(){

Inventory *newinv = NULL;
if (id==NO_ID)
	return NULL;

newinv = (Inventory *) malloc(sizeof (Inventory));
if(newinv==NULL)
	return NULL;

newinv->objects = set_create (num_MaxObj);

return newinv;

}

STATUS inventory_destroy(Inventory*inv){

set_destroy(Set * objects);
free(inv);


}

STATUS inventory_set_add (Inventory* inv, Id*id){

if (!inv)
return ERROR;
set_add(objects, id);
return OK;
}
STATUS inventory_set_del(Inventory * inv){
if (!inv)
return ERROR;
set_del(objects, id);
return OK;
}
STATUS inventory_print (Inventory* inv, FILE *f){
  if (!inv) return ERROR;
  set_print_debug(f, objects);	
  return OK;
}

