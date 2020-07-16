

#ifndef GAME_OBJUTILS_H
#define GAME_OBJUTILS_H

#include <stddef.h>
#include <string.h>
#include <stdio.h>
#include <malloc.h>
#include "obj_t.h"
#include "vertex_t.h"
#include "face_t.h"
#include "texCoord_t.h"
#include "vertNorm_t.h"

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
 * @return pointer to vertex that was created
 */
vertex_t *addVertToEnd(obj_t *obj);

/**
 * @function addTexCoordToEnd
 * @brief adds a texCoord type to the end with values properly initialized
 * @param obj - pointer to the obj_t to add texCoord to.
 * @return pointer to texCoord that was created
 */
texCoord_t *addTexCoordToEnd(obj_t *obj);

/**
 * @function addVertNormToEnd
 * @brief adds a vertNorm type to the end with values properly initialized
 * @param obj - pointer to the obj_t to add vertNomr to.
 * @return pointer to vertNorm that was created
 */
vertNorm_t *addVertNormToEnd(obj_t *obj);

/**
 * @funciton addFaceToEnd
 * @brief adds face to an obj
 * @param obj - pointer to the obj to add the face to.
 * @return pointer to vertex that was created
 */
face_t *addFaceToEnd(obj_t *obj);

/**
 * @function setVertCoordinates
 * @breif sets the coordinates of a vertex
 * @param obj - obj with vertex to assign
 * @param vertexIndex - index of vert to assign
 * @param x - x coordinate
 * @param y - y coordinate
 * @param z - z coordinate
 * @return 0 for success -1 for failure
 */
int setVertCoordinates(obj_t *obj, unsigned int vertexIndex, float x, float y, float z);

/**
 * @function setTextureCoordinates
 * @brief sets the coordinates for the specified texture coordinate
 * @param obj - obj with vertex to assign
 * @param texCoordIndex - index of texCoord to assign
 * @param u - u coordinate
 * @param v - v coordinate
 * @return 0 for success -1 for failure
 * @warning only supports 2D textures
 */
int setTextureCoordinates(obj_t *obj, unsigned int texCoordIndex, float u, float v);

/**
 * @function setVertCoordinates
 * @breif sets the coordinates of a vertex normal
 * @param obj - obj with vertex to assign
 * @param vertNormIndex - index of vertNorm to assign
 * @param x - x coordinate
 * @param y - y coordinate
 * @param z - z coordinate
 * @return 0 for success -1 for failure
 */
int setVertNormCoordinates(obj_t *obj, unsigned int vertNormIndex, float x, float y, float z);

/**
 * @function setFaceVertIndices
 * @brief assigns the vertices that make up a face
 * @param obj - object with face and verts to assign
 * @param fI - face index
 * @param v1 - First vertex assigned to face->vertexIndex1
 * @param v2 - Second vertex assigned to face->vertexIndex2
 * @param v3 - Third vertex assigned to face-vertexIndex3
 * @return -1 if it failed 0 if it succeeded
 */
int setFaceVertIndices(obj_t *obj, unsigned int fI, unsigned int v1I, unsigned int v2I, unsigned int v3I);

/**
 * @function setFaceTexCoordIndices
 * @breif assigns texture coordinates to faces
 * @param obj - object with face and verts to assign
 * @param fI - face index
 * @param vt1I - face->texCoordIndex1
 * @param vt2I - face->texCoordIndex2
 * @param vt3I - face->texCoordIndex3
 * @return -1 if it failed 0 if it succeeded
 */
int setFaceTexCoordIndices(obj_t *obj, unsigned int fI, unsigned int vt1I, unsigned int vt2I, unsigned int vt3I);

/**
 * @function setFaceVertNormIndices
 * @breif assigns vertex normal to faces
 * @param obj - object with face and verts to assign
 * @param fI - face index
 * @param vn1I - face->vertNormIndex1
 * @param vn2I - face->vertNormIndex2
 * @param vn3I - face->vertNormIndex3
 * @return -1 if it failed 0 if it succeeded
 */
int setFaceVertNormIndices(obj_t *obj, unsigned int fI, unsigned int vn1I, unsigned int vn2I, unsigned int vn3I);

/**
 * @function findVert
 * @brief returns a pointer to the vertex specified at the index
 * @param obj - pointer to obj containing the vert to find
 * @param vertIndex - index of vert to find
 * @return pointer to the found vert or NULL
 */
vertex_t *findVert(obj_t *obj, unsigned int vertIndex);

/**
 * @function findTexCoord
 * @brief returns a pointer to the texture coordinate specified at the index
 * @param obj - pointer to obj containing the vert to find
 * @param texCoordIndex - index of texCoord to find
 * @return pointer to the found texCoord or NULL
 */
texCoord_t *findTexCoord(obj_t *obj, unsigned int texCoordIndex);

/**
 * @function findVertNorm
 * @brief returns a pointer to the vertex normal specified at the index
 * @param obj - pointer to obj containing the vert to find
 * @param vertNormIndex - index of texCoord to find
 * @return pointer to the found vertNorm or NULL
 */
vertNorm_t *findVertNorm(obj_t *obj, unsigned int vertNormIndex);

/**
 * @function findFace
 * @brief returns a pointer to the face specified at the index
 * @param obj - pointer to obj containing the feac to find
 * @param faceIndex - index of face to find
 * @return pointer to the found face or NULL
 */
face_t *findFace(obj_t *obj, unsigned int faceIndex);

/**
 * @function flattenVert
 * @param obj - pointer to obj to flatten into an array
 * @return an array of floats where each float is the a vertex coordinate [x1, y1, z1, ... xN, yN, zN]
 * N is the number of verts
 */
float *flattenVerts(obj_t *obj);

/**
 * @function flattenTexCoords
 * @param obj - pointer to obj to flatten into an array
 * @return an array of floats where each float is the a texture coordinate [u1, v1, ... uN, vN]
 * N is the number of texture coordinates
 * @warning only supports 2D texture coordinates for now.
 */
float *flattenTexCoords(obj_t *obj);

/**
 * @function flattenVertNorms
 * @param obj - pointer to obj to flatten into an array
 * @return an array of floats where each float is the a vertex normal coordinate [x1, y1, z1, ... xN, yN, zN]
 * N is the number of vertex normals
 */
float *flattenVertNorms(obj_t *obj);

/**
 * @function flattenFaces
 * @param obj - pointer to obj to flatten into an array
 * @return an array of ints where each int is a vertex index faces are assumed triangles
 * @warning this will start indexing at 0 for openGL, not OBJ format
 */
unsigned int *flattenFaces(obj_t *obj);



#endif //GAME_OBJUTILS_H
