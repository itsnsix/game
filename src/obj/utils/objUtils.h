

#ifndef RACING_GAME_OBJUTILS_H
#define RACING_GAME_OBJUTILS_H

#include "obj_t.h"

/**
 * @function createObj
 * @brief Creates DYNAMICALLY ALLOCATED obj_t struct pointer with values properly initialized
 * @return obj_t struct with values properly initialized
 * Face and vert count are set to 0, pointers are set to NULL, objName is set to "New Obj"
 * @warning you must pass the created obj to deleteObj when you are done with it to avoid memory leaks
 */
obj_t *createObj();

/**
 * @function deleteObj
 * @brief clears all data associated with and the obj itself
 * @param obj - obj to delete
 */
void deleteObj(obj_t **obj);

/**
 * @function setObjName
 * @brief sets the name of the obj function
 * @param obj - pointer to obj to set the name of
 * @param newName - the new name to set the obj to
 */
void setObjName(obj_t *obj, char *newName);

/**
 * @function addVertToEnd
 * @brief adds a vertex_t type to the end with values properly initialized
 * @param obj - pointer to the obj_t to add vertex to.
 */
void addVertToEnd(obj_t *obj);

/**
 * @function setVertCoordinates
 * @breif sets the coordinates of a vertex
 * @param vert - pointer to vertex to set
 * @param x - x coordinate
 * @param y - y coordinate
 * @param z - z coordinate
 */
void setVertCoordinates(vertex_t *vert, float x, float y, float z);

/**
 * @funciton addFaceToEnd
 * @brief adds face to an obj
 * @param obj - pointer to the obj to add the face to.
 */
void addFaceToEnd(obj_t *obj);

#endif //RACING_GAME_OBJUTILS_H
