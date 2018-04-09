/** 
 * @brief It declares the tests for the space module
 * 
 * @file space_test.h
 * @author Profesores Pprog
 * @version 2.0 
 * @date 19-01-2016
 * @copyright GNU Public License
 */

#ifndef SPACE_TEST_H
#define SPACE_TEST_H

/**
 * @test Prueba la función de creación de un espacio
 * @pre Un identificador como parámetro
 * @post Un puntero no nulo al espacio creado
 */
void test1_space_create();

/**
 * @test Prueba la función de creación de un espacio
 * @pre Un identificador como parámetro
 * @post El identificador del espacio es el introducido
 */
void test2_space_create();

/**
 * @test Prueba la función para establecer el nombre de un espacio
 * @pre Nombre que establecer al espacio
 * @post La salida debe ser OK
 */
void test1_space_set_name();

/**
 * @test Prueba la función para establecer el nombre de un espacio
 * @pre El espacio al que establecer el nombre es un puntero a NULL
 * @post La salida debe ser ERROR
 */
void test2_space_set_name();

/**
 * @test Prueba la función para establecer el nombre de un espacio
 * @pre El espacio es un puntero no NULL, pero el nombre a establecer es NULL
 * @post La salida debe ser ERROR
 */
void test3_space_set_name();
void test1_space_set_north();
void test2_space_set_north();
void test3_space_set_north();
void test4_space_set_north();
void test1_space_set_south();
void test2_space_set_south();
void test3_space_set_south();
void test4_space_set_south();
void test1_space_set_east();
void test2_space_set_east();
void test3_space_set_east();
void test4_space_set_east();
void test1_space_set_west();
void test2_space_set_west();
void test3_space_set_west();
void test4_space_set_west();
void test1_space_get_id();
void test2_space_get_id();
void test1_space_set_object();
void test2_space_set_object();
void test1_space_get_name();
void test2_space_get_name();
void test1_space_get_north();
void test2_space_get_north();
void test1_space_get_south();
void test2_space_get_south();
void test1_space_get_east();
void test2_space_get_east();
void test1_space_get_west();
void test2_space_get_west();
void test1_space_get_object();
void test2_space_get_object();
void test3_space_get_object();

#endif
