#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/die.h"
#include "../include/die_test.h"
#include "../include/test.h"

#define MAX_TESTS 6

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
        printf("Running all test for module Die:\n");
    } else {
        test = atoi(argv[1]);
        all = 0;
        printf("Running test %d:\t", test);
	if (test < 1 || test > MAX_TESTS) {
	  printf("Error: unknown test %d\n", test);
	  exit(EXIT_SUCCESS);
        }
    }

	if (all || test == 1) test1_dieCreate();
    if (all || test == 2) test1_dieRoll();
    if (all || test == 3) test2_dieRoll();
    if (all || test == 4) test1_dieGetLastRoll();
    if (all || test == 5) test2_dieGetLastRoll();

	PRINT_PASSED_PERCENTAGE;

	return 0;
}

void test1_dieCreate()
{
	int result = die_ini(5) != NULL;
	PRINT_TEST_RESULT(result);
}

void test1_dieRoll()
{
	Die * d = NULL;
	PRINT_TEST_RESULT(die_roll(d) == ERROR);
}

void test2_dieRoll()
{
	Die* d;
	d = die_ini(66);
	PRINT_TEST_RESULT(die_roll(d) == OK);
}

void test1_die_getLastRoll()
{
	Die * d = NULL;
	PRINT_TEST_RESULT(die_getLastRoll(d) == -1);
}

void test2_dieGetLastRoll()
{
	Die* d;
	d = die_ini(66);
	die_roll(d);
	PRINT_TEST_RESULT(die_getLastRoll(d) > 0 && die_getLastRoll(d) < 7);
}
