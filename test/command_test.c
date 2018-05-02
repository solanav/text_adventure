#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/command.h"
#include "../include/command_test.h"
#include "../include/test.h"

#define MAX_TESTS 8

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
        printf("Running all test for module Command:\n");
    } else {
        test = atoi(argv[1]);
        all = 0;
        printf("Running test %d:\t", test);
	if (test < 1 || test > MAX_TESTS) {
	  printf("Error: unknown test %d\n", test);
	  exit(EXIT_SUCCESS);
        }
    }

	if (all || test == 1) test1_command_create();
    if (all || test == 2) test1_command_set_cmd();
    if (all || test == 3) test2_command_set_cmd();
    if (all || test == 4) test1_command_get_cmd();
    if (all || test == 5) test1_command_set_id();
    if (all || test == 6) test2_command_set_id();
    if (all || test == 7) test1_command_get_id();

	PRINT_PASSED_PERCENTAGE;

	return 0;
}

void test1_command_create()
{
	int c = command_create() != NULL;
	PRINT_TEST_RESULT(c);
}

void test1_command_set_cmd()
{
	F_Command *c = NULL;
	PRINT_TEST_RESULT(command_setCmd(c, MOVE) == ERROR);
}

void test2_command_set_cmd()
{
	F_Command *c;
	c = command_create();
	PRINT_TEST_RESULT(command_setCmd(c, MOVE) == OK);
}

void test1_command_get_cmd()
{
	F_Command *c;
	c = command_create();
	command_setCmd(c, MOVE);
	PRINT_TEST_RESULT(command_getCmd(c) == MOVE);
}

void test1_command_set_id()
{
	F_Command *c = NULL;
	PRINT_TEST_RESULT(command_set_id(c, "13") == ERROR);
}

void test2_command_set_id()
{
	F_Command *c = command_create();
	PRINT_TEST_RESULT(command_set_id(c, "west") == OK);
}

void test1_command_get_id()
{
	F_Command *c = command_create();
	command_set_id(c, "west");
	PRINT_TEST_RESULT(strcmp(command_get_id(c), "west") == 0);
}
