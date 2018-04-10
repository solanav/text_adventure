#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/set.h"
#include "../include/set_test.h"
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
        printf("Running all test for module Set:\n");
    } else {
        test = atoi(argv[1]);
        all = 0;
        printf("Running test %d:\t", test);
	if (test < 1 || test > MAX_TESTS) {
	  printf("Error: unknown test %d\n", test);
	  exit(EXIT_SUCCESS);
        }
    }

	if (all || test == 1) test1_set_create();
    if (all || test == 2) test1_set_add();
    if (all || test == 3) test2_set_add();
    if (all || test == 4) test1_set_del();
    if (all || test == 5) test2_set_del();
    if (all || test == 6) test1_set_get_id();
    if (all || test == 7) test2_set_get_id();
    if (all || test == 8) test1_set_rm_all();
    if (all || test == 9) test2_set_rm_all();
    if (all || test == 10) test1_set_rearrange();
	if (all || test == 11) test2_set_rearrange();
	if (all || test == 12) test1_set_cp_all();
	if (all || test == 13) test2_set_cp_all();

	PRINT_PASSED_PERCENTAGE;

	return 1;
}

void test1_set_create()
{
	int s = set_create(1) != NULL;
	PRINT_TEST_RESULT(s);
}

void test1_set_add()
{
	Set *s = NULL;
	PRINT_TEST_RESULT(set_add(s, 1) == ERROR);
}

void test2_set_add()
{
	Set *s = set_create(1);
	PRINT_TEST_RESULT(set_add(s, 1) == OK);
}

void test1_set_del()
{
	Set *s = NULL;
	PRINT_TEST_RESULT(set_del(s, 1) == ERROR);
}

void test2_set_del()
{
	Set *s = set_create(1);
	set_add(s, 1);
	PRINT_TEST_RESULT(set_del(s, 1) == OK);
}

void test1_set_get_id()
{
	Set *s = NULL;
	PRINT_TEST_RESULT(set_get_id(s, 1) == -1);
}

void test2_set_get_id()
{
	Set *s = set_create(1);
	set_add(s, 1);
	PRINT_TEST_RESULT(set_get_id(s, 0) == 1);
}

void test1_set_rm_all()
{
	Set *s = NULL;
	PRINT_TEST_RESULT(set_rm_all(s) == ERROR);
}

void test2_set_rm_all()
{
	Set *s = set_create(1);
	set_add(s, 1);
	PRINT_TEST_RESULT(set_rm_all(s) == OK);
}

void test1_set_rearrange()
{
	Set *s = NULL;
	PRINT_TEST_RESULT(set_rearrange(s) == ERROR);
}

void test2_set_rearrange()
{
	Set *s = set_create(1);
	PRINT_TEST_RESULT(set_rearrange(s) == OK);
}

void test1_set_cp_all()
{
	Set *s = NULL;
	PRINT_TEST_RESULT(set_cp_all(s) == NULL);
}

void test2_set_cp_all()
{
	Set *s = set_create(1);
	set_add(s, 1);
	PRINT_TEST_RESULT(set_cp_all(s) != NULL);
}
