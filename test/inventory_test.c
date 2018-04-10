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
        printf("Running all test for module Space:\n");
    } else {
        test = atoi(argv[1]);
        all = 0;
        printf("Running test %d:\t", test);
	if (test < 1 || test > MAX_TESTS) {
	  printf("Error: unknown test %d\n", test);
	  exit(EXIT_SUCCESS);
        }
    }

	if (all || test == 1) test1_inventory_create();
    if (all || test == 2) test1_inventory_set_ids();
    if (all || test == 3) test1_inventory_get_ids();
    if (all || test == 4) test1_inventory_get_id_at();
	if (all || test == 5) test1_inventory_add_id();
	if (all || test == 6) test2_inventory_add_id();
	if (all || test == 7) test1_inventory_del_id();
	if (all || test == 8) test2_inventory_del_id();

	PRINT_PASSED_PERCENTAGE;

	return 1;
}

void test1_inventory_create()
{
	int i = inventory_create(1) != NULL;
	PRINT_TEST_RESULT(i);
}

void test1_inventory_set_ids()
{
	Inventory *i = inventory_create(1);
	Set *s = set_create(1);
	set_add(s, (long int)12);
	PRINT_TEST_RESULT(inventory_set_ids(i, s) == OK);
}

void test1_inventory_get_ids()
{
	Inventory *i = inventory_create(1);
	inventory_add_id(i, (long int) 15);
	PRINT_TEST_RESULT(inventory_get_ids(i) != NULL);
}

void test1_inventory_get_id_at()
{
	Inventory *i = NULL;
	PRINT_TEST_RESULT(inventory_get_id_at(i, 1) == NO_ID);
}

void test2_inventory_get_id_at()
{
	Inventory *i = inventory_create(1);
	inventory_add_id(i, (long int)12);
	PRINT_TEST_RESULT(inventory_get_id_at(i, 1) == 12);
}

void test1_inventory_add_id()
{
	Inventory *i = NULL;
	PRINT_TEST_RESULT(inventory_add_id(i, 1) == ERROR);
}

void test2_inventory_add_id()
{
	Inventory *i = inventory_create(1);
	PRINT_TEST_RESULT(inventory_add_id(i, 2) == OK);
}

void test1_inventory_del_id()
{
	Inventory *i = NULL;
	PRINT_TEST_RESULT(inventory_del_id(i, 1) == ERROR);
}

void test2_inventory_del_id()
{
	Inventory *i = inventory_create(1);
	inventory_add_id(i, 2);
	PRINT_TEST_RESULT(inventory_del_id(i, 2) == OK);
}
