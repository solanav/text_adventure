/**
 * @brief It declares the tests for the space module
 *
 * @file space_test.h
 * @author Profesores Pprog
 * @copyright GNU Public License
 */

#ifndef SPACE_TEST_H
#define SPACE_TEST_H

/**
 * @test Prueba la función de creación de un espacio
 * @pre Un identificador como parámetro
 * @post Un puntero no nulo al espacio creado
 */
void test1_spaceCreate();

/**
 * @test Prueba la función de creación de un espacio
 * @pre Un identificador como parámetro
 * @post El identificador del espacio es el introducido
 */
void test2_spaceCreate();

/**
 * @test Prueba la función para establecer el nombre de un espacio
 * @pre Nombre que establecer al espacio
 * @post La salida debe ser OK
 */
void test1_spaceSetName();

/**
 * @test Prueba la función para establecer el nombre de un espacio
 * @pre El espacio al que establecer el nombre es un puntero a NULL
 * @post La salida debe ser ERROR
 */
void test2_spaceSetName();

/**
 * @test Prueba la función para establecer el nombre de un espacio
 * @pre El espacio es un puntero no NULL, pero el nombre a establecer es NULL
 * @post La salida debe ser ERROR
 */
void test3_spaceSetName();
void test1_spaceSetNorth();
void test2_spaceSetNorth();
void test3_spaceSetNorth();
void test4_spaceSetNorth();
void test1_spaceSetSouth();
void test2_spaceSetSouth();
void test3_spaceSetSouth();
void test4_spaceSetSouth();
void test1_spaceSetEast();
void test2_spaceSetEast();
void test3_spaceSetEast();
void test4_spaceSetEast();
void test1_spaceSetWest();
void test2_spaceSetWest();
void test3_spaceSetWest();
void test4_spaceSetWest();
void test1_spaceGetId();
void test2_spaceGetId();
void test1_spaceSetObject();
void test2_spaceSetObject();
void test1_spaceGetName();
void test2_spaceGetName();
void test1_spaceGetNorth();
void test2_spaceGetNorth();
void test1_spaceGetSouth();
void test2_spaceGetSouth();
void test1_spaceGetEast();
void test2_spaceGetEast();
void test1_spaceGetWest();
void test2_spaceGetWest();
void test1_spaceGetObject();
void test2_spaceGetObject();
void test3_spaceGetObject();

#endif
