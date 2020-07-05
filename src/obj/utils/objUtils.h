

#ifndef GAME_OBJUTILS_H
#define GAME_OBJUTILS_H

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
 * @param obj - obj with vertex to assign
 * @param vertexIndex - index of vert to assign
 * @param x - x coordinate
 * @param y - y coordinate
 * @param z - z coordinate
 */
int setVertCoordinates(obj_t *obj, unsigned int vertexIndex, float x, float y, float z);

/**
 * @funciton addFaceToEnd
 * @brief adds face to an obj
 * @param obj - pointer to the obj to add the face to.
 */
void addFaceToEnd(obj_t *obj);

/**
 * @function setFaceVertIndices
 * @brief assigns the vertices that make up a face
 * @param v1 - First vertex assigned to face->vertexIndex1
 * @param v2 - Second vertex assigned to face->vertexIndex2
 * @param v3 - Third vertex assigned to face-vertexIndesx3
 * @return returns -1 if it failed 0 if it succeeded
 */
int setFaceVertIndices(obj_t *obj, unsigned int fI, unsigned int v1I, unsigned int v2I, unsigned int v3I);

/**
 * @function findVert
 * @brief returns a pointer to the vertex specified at the index
 * @param obj - pointer to obj containing the vert to find
 * @param vertIndex - index of vert to find
 * @return pointer to the found vert or NULL
 */
vertex_t *findVert(obj_t *obj, unsigned int vertIndex);

/**
 * @function findFace
 * @brief returns a pointer to the face specified at the index
 * @param obj - pointer to obj containing the feac to find
 * @param faceIndex - index of face to find
 * @return pointer to the found face or NULL
 */
face_t *findFace(obj_t *obj, unsigned int faceIndex);



#endif //GAME_OBJUTILS_H
