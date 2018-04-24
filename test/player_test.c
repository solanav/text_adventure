#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/player.h"
#include "../include/player_test.h"
#include "../include/test.h"

#define MAX_TESTS 16

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
        printf("Running all test for module Player:\n");
    } else {
        test = atoi(argv[1]);
        all = 0;
        printf("Running test %d:\t", test);
	if (test < 1 || test > MAX_TESTS) {
	  printf("Error: unknown test %d\n", test);
	  exit(EXIT_SUCCESS);
        }
    }

	if (all || test == 1)   test1_playerCreate();
   if (all || test == 2)  test1_playerSetName();
   if (all || test == 3)  test2_playerSetName();
   if (all || test == 4)  test1_playerSetLocId();
   if (all || test == 5)  test2_playerSetLocId();
   if (all || test == 6)  test1_playerSetObjId();
   if (all || test == 7)  test2_playerSetObjId();
   if (all || test == 8)  test1_playerSetId();
   if (all || test == 9)  test2_playerSetId();
   if (all || test == 10) test1_playerGetName();
	 if (all || test == 11) test1_playerGetLocId();
	 if (all || test == 12) test1_playerGetObjId();
	 if (all || test == 13) test1_playerGetId();
	 if (all || test == 14) test1_playerRemoveObjectId();
	 if (all || test == 15) test2_playerRemoveObjectId();

	PRINT_PASSED_PERCENTAGE;

	return 0;
}

void test1_playerCreate()
{
	int p = player_create("Idi", 1, 1, 1) != NULL;
	PRINT_TEST_RESULT(p);
}

void test1_playerSetName()
{
	Player *p = NULL;
	PRINT_TEST_RESULT(player_setName(p, "I") == ERROR);
}

void test2_playerSetName()
{
	Player *p = player_create("I", 1, 1, 1);
	PRINT_TEST_RESULT(player_setName(p, "W") == OK);
}

void test1_player_setLocId()
{
	Player *p = NULL;
	PRINT_TEST_RESULT(player_setLocId(p, 2) == ERROR);
}

void test2_playerSetLocId()
{
	Player *p = player_create("I", 1, 1, 1);
	PRINT_TEST_RESULT(player_setLocId(p, 2) == OK);
}

void test1_playerSetObjId()
{
	Player *p = NULL;
	PRINT_TEST_RESULT(player_setObjId(p, 2) == ERROR);
}

void test2_playerSetObjId()
{
	Player *p = player_create("I", 1, 1, 1);
	PRINT_TEST_RESULT(player_setObjId(p, 2) == OK);
}

void test1_playerSetId()
{
	Player *p = NULL;
	PRINT_TEST_RESULT(player_setId(p, 2) == ERROR);
}

void test2_playerSetId()
{
	Player *p = player_create("I", 1, 1, 1);
	PRINT_TEST_RESULT(player_setId(p, 2) == OK);
}

void test1_playerGetName()
{
	Player *p = player_create("I", 1, 1, 1);
	PRINT_TEST_RESULT(strcmp(player_getName(p), "I") == 0);
}

void test1_playerGetLocId()
{
	Player *p = player_create("I", 1, 1, 1);
	PRINT_TEST_RESULT(player_getLocId(p) == 1);
}

void test1_playerGetObjId()
{
	Player *p = player_create("I", 1, 1, 1);
	player_setObjId(p, 1);
	PRINT_TEST_RESULT(player_getObjId(p, 0) == 1);
}

void test1_playerGetId()
{
	Player *p = player_create("I", 1, 1, 1);
	PRINT_TEST_RESULT(player_getId(p) == 1);
}

void test1_playerRemoveObjectId()
{
	Player *p = NULL;
	PRINT_TEST_RESULT(player_removeObjId(p, 1) == ERROR);
}

void test2_playerRemoveObjectId()
{
	Player *p = player_create("I", 1, 1, 1);
	PRINT_TEST_RESULT(player_removeObjId(p, 1) == OK);
}
