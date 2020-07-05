/**
 * @author nsix
 * @file obj_t.h
 * @brief Defines the obj_t struct for obj files
 */

#ifndef GAME_OBJ_H
#define GAME_OBJ_H
#include "vertex_t.h"
#include "face_t.h"

typedef struct {
    unsigned int objId;
    char objName[24];
    unsigned int vertexCount;
    unsigned int faceCount;
    vertex_t *startVertex;
    face_t *startFace;
} obj_t;
#endif //GAME_OBJ_H
