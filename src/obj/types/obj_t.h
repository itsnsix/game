/**
 * @author nsix
 * @file obj_t.h
 * @brief Defines the obj_t struct for obj files
 */

#ifndef GAME_OBJ_H
#define GAME_OBJ_H
#include "vertex_t.h"
#include "face_t.h"
#include "texCoord_t.h"
#include "vertNorm_t.h"

typedef struct {
    unsigned int objId;
    char objName[24];
    unsigned int vertexCount;
    unsigned int texCoordCount;
    unsigned int vertNormCount;
    unsigned int faceCount;
    vertex_t *startVertex;
    face_t *startFace;
    texCoord_t *startTexCoord;
    vertNorm_t *startVertNorm;
} obj_t;
#endif //GAME_OBJ_H
