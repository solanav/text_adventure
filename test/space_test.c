/**
 * @brief It tests space module
 *
 * @file space_test.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/space.h"
#include "../include/space_test.h"
#include "../include/test.h"

#define MAX_TESTS 28

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


    if (all || test == 1)  test1SpaceCreate();
    if (all || test == 2)  test2SpaceCreate();
    if (all || test == 3)  test1SpaceSetName();
    if (all || test == 4)  test2SpaceSetName();
    if (all || test == 5)  test3SpaceSetName();
    if (all || test == 6)  test1SpaceSetNorth();
    if (all || test == 7)  test2SpaceSetNorth();
    if (all || test == 8)  test1SpaceSetSouth();
    if (all || test == 9)  test2SpaceSetSouth();
    if (all || test == 10) test1SpaceSetEast();
    if (all || test == 11) test2SpaceSetEast();
    if (all || test == 12) test1SpaceSetWest();
    if (all || test == 13) test2SpaceSetWest();
    if (all || test == 14) test1SpaceGetName();
    if (all || test == 15) test2SpaceGetName();
    if (all || test == 16) test1SpaceGetObject();
    if (all || test == 17) test2SpaceGetObject();
    if (all || test == 18) test3SpaceGetObject();
    if (all || test == 19) test1SpaceGetNorth();
    if (all || test == 20) test2SpaceGetNorth();
    if (all || test == 21) test1SpaceGetSouth();
    if (all || test == 22) test2SpaceGetSouth();
    if (all || test == 23) test1SpaceGetEast();
    if (all || test == 24) test2SpaceGetEast();
    if (all || test == 25) test1SpaceGetWest();
    if (all || test == 26) test2SpaceGetWest();
    if (all || test == 27) test1SpaceGetId();
    if (all || test == 28) test2SpaceGetId();

    PRINT_PASSED_PERCENTAGE;

    return 0;
}

void test1_spaceCreate() {
  int result = space_create(5)!=NULL ;
  PRINT_TEST_RESULT(result);
}

void test2_spaceCreate() {
    Space *s;
    s = space_create(4);
    PRINT_TEST_RESULT(space_getId(s) == 4);
}

void test1_spaceSetName() {
    Space *s;
    s = space_create(5);
    PRINT_TEST_RESULT(space_setName(s, "hola") == OK);
}

void test2_spaceSetName() {
    Space *s = NULL;
    PRINT_TEST_RESULT(space_setName(s, "hola") == ERROR);
}

void test3_spaceSetName() {
    Space *s;
    s = space_create(5);
    PRINT_TEST_RESULT(space_setName(s, NULL) == ERROR);
}

void test1_spaceSetNorth() {
    Space *s;
    s = space_create(5);
    PRINT_TEST_RESULT(space_setNorth(s, 4) == OK);
}

void test2_spaceSetNorth() {
    Space *s = NULL;
    PRINT_TEST_RESULT(space_setNorth(s, 4) == ERROR);
}

void test1_spaceSetSouth() {
    Space *s;
    s = space_create(5);
    PRINT_TEST_RESULT(space_setSouth(s, 4) == OK);
}

void test2_spaceSetSouth() {
    Space *s = NULL;
    PRINT_TEST_RESULT(space_setSouth(s, 4) == ERROR);
}

void test1_spaceSetEast() {
    Space *s;
    s = space_create(5);
    PRINT_TEST_RESULT(space_setEast(s, 4) == OK);
}

void test2_spaceSetEast() {
    Space *s = NULL;
    PRINT_TEST_RESULT(space_setEast(s, 4) == ERROR);
}

void test1_spaceSetWest() {
    Space *s;
    s = space_create(5);
    PRINT_TEST_RESULT(space_setWest(s, 4) == OK);
}

void test2_spaceSetWest() {
    Space *s = NULL;
    PRINT_TEST_RESULT(space_setWest(s, 4) == ERROR);
}

void test1_spaceSetObject() {
    Space *s;
    s = space_create(1);
    PRINT_TEST_RESULT(space_addObject(s,TRUE) == OK);
}

void test2_spaceSetObject() {
    Space *s = NULL;
    PRINT_TEST_RESULT(space_addObject(s,TRUE) == ERROR);
}

void test1_spaceGetName() {
    Space *s;
    s = space_create(1);
    space_setName(s, "adios");
    PRINT_TEST_RESULT(strcmp(space_getName(s), "adios") == 0);

}

void test2_space_getName() {
    Space *s = NULL;
    PRINT_TEST_RESULT(space_getName(s) == NULL);

}

void test1_spaceGetObject() {
    Space *s;
    s = space_create(1);
    PRINT_TEST_RESULT(space_getObjectsId(s) != NULL);

}

void test2_spaceGetObject() {
    Space *s;
    s = space_create(1);
    space_addObject(s,TRUE);
    PRINT_TEST_RESULT(space_getObjectsId(s) != NULL);

}

void test3_spaceGetObject() {
    Space *s = NULL;
    PRINT_TEST_RESULT(space_getObjectsId(s) == NULL);
}

void test1_spaceGetNorth() {
    Space *s;
    s = space_create(5);
    space_setNorth(s, 4);
    PRINT_TEST_RESULT(space_getNorth(s) == 4);
}

void test2_spaceGetNorth() {
    Space *s = NULL;
    PRINT_TEST_RESULT(space_getNorth(s) == NO_ID);
}

void test1_spaceGetSouth() {
    Space *s;
    s = space_create(5);
    space_setSouth(s, 2);
    PRINT_TEST_RESULT(space_getSouth(s) == 2);
}

void test2_spaceGetSouth() {
    Space *s = NULL;
    PRINT_TEST_RESULT(space_getSouth(s) == NO_ID);
}

void test1_spaceGetEast() {
    Space *s;
    s = space_create(5);
    space_setEast(s, 1);
    PRINT_TEST_RESULT(space_getEast(s) == 1);
}

void test2_spaceGetEast() {
    Space *s = NULL;
    PRINT_TEST_RESULT(space_getEast(s) == NO_ID);
}

void test1_spaceGetWest() {
    Space *s;
    s = space_create(5);
    space_setWest(s, 6);
    PRINT_TEST_RESULT(space_getWest(s) == 6);
}

void test2_spaceGetWest() {
    Space *s = NULL;
    PRINT_TEST_RESULT(space_getWest(s) == NO_ID);
}

void test1_spaceGetId() {
    Space *s;
    s = space_create(25);
    PRINT_TEST_RESULT(space_getId(s) == 25);
}

void test2_spaceGetId() {
    Space *s = NULL;
    PRINT_TEST_RESULT(space_getId(s) == NO_ID);
}
