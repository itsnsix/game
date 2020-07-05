

#ifndef RACING_GAME_OBJ_H
#define RACING_GAME_OBJ_H
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
#endif //RACING_GAME_OBJ_H
