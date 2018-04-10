#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/object.h"
#include "../include/object_test.h"
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
        printf("Running all test for module Object:\n");
    } else {
        test = atoi(argv[1]);
        all = 0;
        printf("Running test %d:\t", test);
	if (test < 1 || test > MAX_TESTS) {
	  printf("Error: unknown test %d\n", test);
	  exit(EXIT_SUCCESS);
        }
    }

	if (all || test == 1) test1_object_create();
    if (all || test == 2) test2_object_create();
    if (all || test == 3) test1_object_set_name();
    if (all || test == 4) test2_object_set_name();
    if (all || test == 5) test1_object_set_id();
    if (all || test == 6) test2_object_set_id();
    if (all || test == 7) test1_object_set_description();
    if (all || test == 8) test2_object_set_description();
    if (all || test == 9) test1_object_get_name();
    if (all || test == 10) test1_object_get_description();
	if (all || test == 11) test1_object_get_id();

	PRINT_PASSED_PERCENTAGE;

	return 0;
}

void test1_object_create()
{
	int result = object_create("name", 5) != NULL;
	PRINT_TEST_RESULT(result);
}

void test2_object_create()
{
	Object *o;
	o = object_create("name", 5);
	PRINT_TEST_RESULT(object_get_id(o) == 5);
}

void test1_object_set_name()
{
	Object *s = NULL;
    PRINT_TEST_RESULT(object_set_name(s, "hola") == ERROR);
}

void test2_object_set_name()
{
	Object *s = object_create("name", 5);
	PRINT_TEST_RESULT(object_set_name(s, "hola") == OK);
}

void test1_object_set_id()
{
	Object *s = NULL;
    PRINT_TEST_RESULT(object_set_id(s, 5) == ERROR);
}

void test2_object_set_id()
{
	Object *s = object_create("name", 5);
	PRINT_TEST_RESULT(object_set_id(s, 6) == OK);
}

void test1_object_set_description()
{
	Object *s = NULL;
    PRINT_TEST_RESULT(object_set_description(s, "End this") == ERROR);
}

void test2_object_set_description()
{
	Object *s = object_create("name", 5);
	PRINT_TEST_RESULT(object_set_description(s, "End this") == OK);
}

void test1_object_get_name()
{
	Object *s = object_create("name", 5);
	PRINT_TEST_RESULT(strcmp("name", object_get_name(s)) == 0);
}

void test1_object_get_description()
{
	Object *s = object_create("name", 5);
	object_set_description(s, "This is a description");
	PRINT_TEST_RESULT(strcmp("This is a description", object_get_description(s)) == 0);
}

void test1_object_get_id()
{
	Object *s = object_create("name", 5);
	PRINT_TEST_RESULT(object_get_id(s) == 5);
}
