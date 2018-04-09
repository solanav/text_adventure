#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/link.h"
#include "../include/link_test.h"
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

	if (all || test == 1) test1_link_create();
    if (all || test == 2) test2_link_create();
    if (all || test == 3) test1_link_set_id();
    if (all || test == 4) test2_link_set_id();
    if (all || test == 5) test1_link_set_status();
    if (all || test == 6) test2_link_set_status();
    if (all || test == 7) test1_link_set_spaces();
    if (all || test == 8) test2_link_set_spaces();
    if (all || test == 9) test1_link_get_id();
    if (all || test == 10) test1_link_get_space1();
	if (all || test == 11) test1_link_get_space2();
	if (all || test == 12) test1_link_get_status();
	if (all || test == 13) test1_link_get_destination();

	PRINT_PASSED_PERCENTAGE;

	return 1;
}
void test1_link_create()
{
	int result = link_create(5) != NULL;
	PRINT_TEST_RESULT(result);
}

void test2_link_create()
{
	Link *o;
	o = link_create(5);
	PRINT_TEST_RESULT(link_getId(o) == 5);
}

void test1_link_set_id()
{
	Link *s = NULL;
    PRINT_TEST_RESULT(link_setId(s, 5) == ERROR);
}

void test2_link_set_id()
{
	Link *s = link_create(5);
	PRINT_TEST_RESULT(link_setId(s, 6) == OK);
}

void test1_link_set_status()
{
	Link *s = NULL;
    PRINT_TEST_RESULT(link_setStatus(s, OPEN) == ERROR);
}

void test2_link_set_status()
{
	Link *s = link_create(5);
	PRINT_TEST_RESULT(link_setStatus(s, OPEN) == OK);
}

void test1_link_set_spaces()
{
	Link *s = NULL;
    PRINT_TEST_RESULT(link_setSpaces(s, 1, 2) == ERROR);
}

void test2_link_set_spaces()
{
	Link *s = link_create(5);
	PRINT_TEST_RESULT(link_setSpaces(s, 1, 2) == OK);
}

void test1_link_get_id()
{
	Link *s = link_create(5);
	PRINT_TEST_RESULT(link_getId(s) == 5);
}

void test1_link_get_space1()
{
	Link *s = link_create(5);
	link_setSpaces(s, 1, 2);
	PRINT_TEST_RESULT(link_getSpace1(s) == 1);
}

void test1_link_get_space2()
{
	Link *s = link_create(5);
	link_setSpaces(s, 1, 2);
	PRINT_TEST_RESULT(link_getSpace2(s) == 2);
}

void test1_link_get_status()
{
	Link *s = link_create(5);
	link_setStatus(s, OPEN);
	PRINT_TEST_RESULT(link_getStatus(s) == OPEN);
}

void test1_link_get_destination()
{
	Link *s = link_create(5);
	link_setSpaces(s, 1, 2);
	PRINT_TEST_RESULT(link_getDestination(s, 1) == 2);
}
