#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/sprite.h"
#include "../include/sprite_test.h"
#include "../include/test.h"

#define MAX_TESTS 14

/**
 * @brief Funcion principal de pruebas para el modulo Sprite Test.
 *
 * Dos modos de ejecucion:
 *   1.-Si se ejecuta sin parametros se ejecutan todas las pruebas
 *   2.-Si se ejecuta con un numero entre 1 y el numero de pruebas solo ejecuta
 *      la prueba indicada
 *
 */
int main(int argc, char **argv)
{
	int test = 0;
	int all = 1;

	if (argc < 2)
	{
		printf("Running all test for module Sprite:\n");
	}
	else
	{
		test = atoi(argv[1]);
		all = 0;
		printf("Running test %d:\t", test);
		if (test < 1 || test > MAX_TESTS)
		{
			printf("Error: unknown test %d\n", test);
			exit(EXIT_SUCCESS);
		}
	}

	if (all || test == 1)
		test1_sprite_create();
	if (all || test == 2)
		test2_sprite_create();
	if (all || test == 2)
		test1_sprite_set();
	if (all || test == 2)
		test2_sprite_set();
	

	PRINT_PASSED_PERCENTAGE;

	return 0;
}
void test1_sprite_create()
{
	Sprite *o;
	o = sprite_create(1);
	PRINT_TEST_RESULT(sprite_getId(o) == 1);
}

void test2_sprite_create()
{
	Sprite *o;
	o = sprite_create(9999999);
	PRINT_TEST_RESULT(sprite_getId(o) == 9999999);
}

void test1_sprite_set()
{
	Sprite *o;
	o = sprite_create(1);
	sprite_putLine(o, "testing", 0);
	PRINT_TEST_RESULT(strcmp(sprite_getData(o, 0), "testing") == 0);
}

void test2_sprite_set()
{
	char *data;

	Sprite *o;
	o = sprite_create(1);
	
	data = (char *)calloc(1, sizeof(char));
	strcpy(data, "testingtestingtestingtestingtestingtestingtestingtestingtestingtestingtestingtestingtestingtestingtestingtestingtestingtestingtestingtestingtestingtestingtestingtestingtestingtestingtestingtestingtestingtestingtestingtestingtestingtestingtestingtestingtestingtestingtestingtestingtestingtestingtestingtestingtestingtestingtesting");
		
	PRINT_TEST_RESULT(sprite_putLine(o, data, 0) == OK);
}