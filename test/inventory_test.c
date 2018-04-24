#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/inventory.h"
#include "../include/inventory_test.h"
#include "../include/set.h"
#include "../include/test.h"

#define MAX_TESTS 9

/**
 * @brief Funcion principal de pruebas para el modulo Space.
 *
 * Dos modos de ejecucion:
 *   1.-Si se ejecuta sin parametros se ejecutan todas las pruebas
 *   2.-Si se ejecuta con un numero entre 1 y el numero de pruebas solo ejecuta
 *      la prueba indicada
 *
 */
int main(int argc, char** argv) {

    int test = 0;
    int all = 1;

    if (argc < 2) {
        printf("Running all test for module Inventory:\n");
    } else {
        test = atoi(argv[1]);
        all = 0;
        printf("Running test %d:\t", test);
	if (test < 1 || test > MAX_TESTS) {
	  printf("Error: unknown test %d\n", test);
	  exit(EXIT_SUCCESS);
        }
    }

	if (all || test == 1) test1_inventoryCreate();
    if (all || test == 2) test1_inventorySetIds();
    if (all || test == 3) test1_inventoryGetIds();
    if (all || test == 4) test1_inventoryGetIdAt();
	if (all || test == 5) test1_inventoryAddId();
	if (all || test == 6) test2_inventoryAddId();
	if (all || test == 7) test1_inventoryDelId();
	if (all || test == 8) test2_inventoryDelId();

	PRINT_PASSED_PERCENTAGE;

	return 0;
}

void test1_inventoryCreate()
{
	int i = inventory_create(1) != NULL;
	PRINT_TEST_RESULT(i);
}

void test1_inventorySetIds()
{
	Inventory *i = inventory_create(1);
	Set *s = set_create(1);
	set_add(s, (long int)12);
	PRINT_TEST_RESULT(inventory_setIds(i, s) == OK);
}

void test1_inventory_getIds()
{
	Inventory *i = inventory_create(1);
	inventory_addId(i, (long int) 15);
	PRINT_TEST_RESULT(inventory_getIds(i) != NULL);
}

void test1_inventory_getIdAt()
{
	Inventory *i = NULL;
	PRINT_TEST_RESULT(inventory_getIdAt(i, 1) == NO_ID);
}

void test2_inventory_getIdAt()
{
	Inventory *i = inventory_create(1);
	inventory_addId(i, (long int)12);
	PRINT_TEST_RESULT(inventory_getIdAt(i, 1) == 12);
}

void test1_inventory_addId()
{
	Inventory *i = NULL;
	PRINT_TEST_RESULT(inventory_addId(i, 1) == ERROR);
}

void test2_inventory_addId()
{
	Inventory *i = inventory_create(1);
	PRINT_TEST_RESULT(inventory_addId(i, 2) == OK);
}

void test1_inventory_delId()
{
	Inventory *i = NULL;
	PRINT_TEST_RESULT(inventory_delId(i, 1) == ERROR);
}

void test2_inventory_delId()
{
	Inventory *i = inventory_create(1);
	inventory_add_id(i, 2);
	PRINT_TEST_RESULT(inventory_delId(i, 2) == OK);
}
