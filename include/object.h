
/**
 * @brief Functions for the creation of objects
 *
 * @file object.h
 * @author Guillermo Ríos
 * @copyright GNU Public License
 */

 #ifndef OBJECT_H
 #define OBJECT_H

 #include <stdio.h>
 #include <stdlib.h>

 #include "types.h"



 /*
 	@param un campo de identificacion id
 	@param nombre del objeto name
 */
 typedef struct _Object Object;

 /*
 	@brief Crea object_create que reserva memoria
 	@param1 Este inicializa con el puntero id los campos del objeto que devuelve
 */
 Object* object_create(char* name, Id id);
 /*
 	@brief destruye un objeto liberando la memoria que lo contiene
 	@param puntero object de tipo Object
 	@return devuelve OK si se ha realizado correctamente o ERROR si no.
 */
 void object_destroy(Object* obj);
 /*
 	@brief modifica el nombre de un objeto
 	@param puntero object de tipo Object
 	@param string
 	@return devuelve OK si se ha modificado correctamente o ERROR si no
 */
 STATUS object_set_name(Object* obj, char* name);
 /*
 	@brief modifica la descricion de un objeto
 	@param puntero object de tipo Object
 	@param string
 	@return devuelve OK si se ha modificado correctamente o ERROR si no
 */
 STATUS object_set_description(Object* obj, char* descript);
 /*
 	@brief modifica la id del objeto
 	@param puntero object de tipo Object
 	@param el id del objeto
 	@return devuelve OK si se ha modificado correctamente o ERROR si no
 */
 STATUS object_set_id(Object* obj, Id id);
 /*
 	@brief Devuelve el nombre de un objeto
 	@param puntero object de tipo Object
 	@return devuelve object->name (el nombre del objeto) o NULL si algo ha fallado
 */
 char * object_get_name(Object* obj);
 /*
 	@brief Devuelve la descricion de un objeto
 	@param puntero object de tipo Object
 	@return devuelve object->descript o NULL si algo ha fallado
 */
 char * object_get_description(Object* obj);
 /*
   @author Bernardo Zambrano
   @brief Imprime la descricion de un objeto
   @param puntero object de tipo Object
   @param puntero FILE
   @return devuelve OK si se imprimió correctamente o ERROR si no
 */
 STATUS object_description_print(Object *obj, FILE *f);
 /*
 	@brief Nos da la id del objecto
 	@param puntero object de tipo Object
 	@return nos devuelve NO_ID si el objeto es nulo o el id del objeto
 */
 Id object_get_id(Object* obj);
 /*
   @author Bernardo Zambrano
   @brief Nos dice si el objeto es movible
   @param puntero object de tipo Object
   @return TRUE si lo es o FALSE si no o si hube algun error
 */
 BOOL * object_get_mobile(Object* obj);
 /*
   @author Bernardo Zambrano
   @brief modifica el valor movible de los objetos
   @param puntero object de tipo Object
   @param bool que se quiere poner
   @return devuelve OK si se ha modificado correctamente o ERROR si no
 */
 STATUS * object_set_mobile(Object*  obj,BOOL mobile);
 /*
   @author Bernardo Zambrano
   @brief Nos dice si el objeto se ha movido
   @param puntero object de tipo Object
   @return TRUE se ha movido o FALSE si no o si hube algun error
 */
 BOOL * object_get_moved(Object* obj);
 /*
   @author Bernardo Zambrano
   @brief modifica el campo moved de objeto
   @param puntero object de tipo Object
   @param bool que se quiere poner
   @return devuelve OK si se ha modificado correctamente o ERROR si no
 */
 STATUS * object_set_moved(Object*  obj, BOOL moved);

 /*
   @author Bernardo Zambrano
   @brief Nos dice si el objeto esta oculto
   @param puntero object de tipo Object
   @return TRUE se esta oculto o FALSE si no o si hube algun error
 */
 BOOL * object_get_hidden(Object* obj);
 /*
   @author Bernardo Zambrano
   @brief modifica el campo hidden de objeto
   @param puntero object de tipo Object
   @param bool que se quiere poner
   @return devuelve OK si se ha modificado correctamente o ERROR si no
 */
 STATUS * object_set_hidden(Object*  obj, BOOL hidden);

  /*
   @author Bernardo Zambrano
   @brief Nos dice si el objeto ilumina
   @param puntero object de tipo Object
   @return TRUE ilumina o FALSE si no o si hube algun error
 */
 BOOL * object_get_iluminati(Object* obj);
 /*
   @author Bernardo Zambrano
   @brief modifica el campo iluminati de objeto
   @param puntero object de tipo Object
   @param bool que se quiere poner
   @return devuelve OK si se ha modificado correctamente o ERROR si no
 */
 STATUS * object_set_ilumnati(Object*  obj, BOOL iluminati);

  /*
    @author Bernardo Zambrano
 	@brief Nos da la del espacio que abre el objeto
 	@param puntero object de tipo Object
 	@return nos devuelve NO_ID si el objeto es nuloo no abre ningun espacio o el id del espacio que abre
 */
 Id object_get_open(Object* obj);

  /*
 	@brief modifica la id del espacio abierto por el objeto  objeto
 	@param puntero object de tipo Object
 	@param el id del espacio que abre el objeto
 	@return devuelve OK si se ha modificado correctamente o ERROR si no
 */
 STATUS object_set_open(Object* obj, Id open);

 /*
  @author Bernardo Zambrano
  @brief Nos dice si el objeto esta encendido
  @param puntero object de tipo Object
  @return TRUE ilumina o FALSE si no o si hube algun error
*/
BOOL * object_get_on(Object* obj);
/*
  @author Bernardo Zambrano
  @brief modifica el campo "on" de objeto
  @param puntero object de tipo Object
  @param bool que se quiere poner
  @return devuelve OK si se ha modificado correctamente o ERROR si no
*/
STATUS * object_set_on(Object*  obj, BOOL on);

/*
 @author Guillermo Ríos
 @brief Devuelve la descricion de un objeto
 @param puntero object de tipo Object
 @return devuelve object->descript o NULL si algo ha fallado
*/
char * object_get_description_alternative(Object* obj);

/*
 @author Guillermo Ríos
 @brief modifica la descricion de un objeto
 @param puntero object de tipo Object
 @param string
 @return devuelve OK si se ha modificado correctamente o ERROR si no
*/
STATUS object_set_description_alternative(Object* obj, char* description_al);

/*
  @author Guillermo Ríos
  @brief Imprime la descricion alternativa de un objeto
  @param puntero object de tipo Object
  @param puntero FILE
  @return devuelve OK si se imprimió correctamente o ERROR si no
*/
STATUS object_description_al_print(Object *obj, FILE *f);

 #endif
