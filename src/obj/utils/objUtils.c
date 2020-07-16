/**
 * @author nsix
 * @file objUtils.c
 * @brief Utilities for creating, modifying, and destroying obj_t types
 * @see objUtils.h for function descriptions
 */


#include "objUtils.h"

obj_t *createObj() {
    obj_t *obj = (obj_t *) malloc(sizeof(obj_t));
    if (obj == NULL) {
        printf("Error: could not malloc obj pointer\n");
        return obj;
    }
    strcpy(obj->objName, "New Obj");
    obj->vertexCount = 0;
    obj->texCoordCount = 0;
    obj->vertNormCount = 0;
    obj->faceCount = 0;
    obj->startVertex = NULL;
    obj->startTexCoord = NULL;
    obj->startVertNorm = NULL;
    obj->startFace = NULL;
    return obj;
}

void deleteObj(obj_t **obj) {

    unsigned int vertFreeCount = 0;
    if ((*obj)->startVertex != NULL) {
        vertex_t *vertIndex = (*obj)->startVertex;
        while (vertIndex->next != NULL) {
            vertIndex = vertIndex->next;
            free(vertIndex->last);
            vertIndex->last = NULL;
            vertFreeCount++;
        }
        free(vertIndex);
        vertIndex = NULL;
        vertFreeCount++;
        if (vertFreeCount != (*obj)->vertexCount) {
            printf("Warning: Possible memory leak.\nFreed Vert Count: %d\nDeclared Vert Count: %d\n", vertFreeCount,
                   (*obj)->vertexCount);
        }
    }

    unsigned int texCoordFreeCount = 0;
    if ((*obj)->startTexCoord != NULL) {
        texCoord_t *texCoordIndex = (*obj)->startTexCoord;
        while (texCoordIndex->next != NULL) {
            texCoordIndex = texCoordIndex->next;
            free(texCoordIndex->last);
            texCoordIndex->last = NULL;
            texCoordFreeCount++;
        }
        free(texCoordIndex);
        texCoordIndex = NULL;
        texCoordFreeCount++;
        if (texCoordFreeCount != (*obj)->texCoordCount) {
            printf("Warning: Possible memory leak.\nFreed Tex Coord Count: %d\nDeclared Tex Coord Count: %d\n", texCoordFreeCount,
                   (*obj)->texCoordCount);
        }
    }


    unsigned int vertNormFreeCount = 0;
    if ((*obj)->startVertNorm != NULL) {
        vertNorm_t *vertNormIndex = (*obj)->startVertNorm;
        while (vertNormIndex->next != NULL) {
            vertNormIndex = vertNormIndex->next;
            free(vertNormIndex->last);
            vertNormIndex->last = NULL;
            vertNormFreeCount++;
        }
        free(vertNormIndex);
        vertNormIndex = NULL;
        vertNormFreeCount++;
        if (vertNormFreeCount != (*obj)->vertNormCount) {
            printf("Warning: Possible memory leak.\nFreed Vert Norm Count: %d\nDeclared Vert Norm Count: %d\n", vertNormFreeCount,
                   (*obj)->vertNormCount);
        }
    }

    unsigned int faceFreeCount = 0;
    if ((*obj)->startFace != NULL) {
        face_t *faceIndex = (*obj)->startFace;
        while (faceIndex->next != NULL) {
            faceIndex = faceIndex->next;
            free(faceIndex->last);
            faceIndex->last = NULL;
            faceFreeCount++;
        }
        free(faceIndex);
        faceIndex = NULL;
        faceFreeCount++;
        if (faceFreeCount != (*obj)->faceCount) {
            printf("Warning: Possible memory leak.\nFace Vert Count: %d\nDeclared Face Count: %d\n", faceFreeCount,
                   (*obj)->faceCount);
        }
    }

    free(*obj);
    *obj = NULL;
}

void setObjName(obj_t *obj, char *newName) {
    strcpy(obj->objName, newName);
}

vertex_t *addVertToEnd(obj_t *obj) {
    // Allocate the memory for the vertex
    vertex_t *vertex = (vertex_t *) malloc(sizeof(vertex_t));
    if (vertex == NULL) {
        printf("Error: could not malloc vertex pointer\n");
        return NULL;
    }

    vertex->next = NULL;
    vertex->last = NULL;
    vertex->x = 0.0f;
    vertex->y = 0.0f;
    vertex->z = 0.0f;

    unsigned int count = 1;
    if (obj->startVertex == NULL) {
        obj->startVertex = vertex;
    } else {
        vertex_t *vertIndex = obj->startVertex;
        while (vertIndex->next != NULL) {
            count++;
            vertIndex = vertIndex->next;
        }
        count++;
        vertIndex->next = vertex;
        vertex->last = vertIndex;
    }

    obj->vertexCount = count;
    vertex->index = count;
    return vertex;
}

texCoord_t *addTexCoordToEnd(obj_t *obj) {
    texCoord_t *texCoord = (texCoord_t *) malloc(sizeof(texCoord_t));
    if (texCoord == NULL) {
        printf("Error: could not malloc texCoord pointer\n");
        return NULL;
    }
    
    texCoord->next = NULL;
    texCoord->last = NULL;
    texCoord->u = 0.0f;
    texCoord->v = 0.0f;
    
    unsigned int count = 1;
    if (obj->startTexCoord == NULL) {
        obj->startTexCoord = texCoord;
    } else {
        texCoord_t *texCoordIndex = obj->startTexCoord;
        while (texCoordIndex->next != NULL) {
            count++;
            texCoordIndex = texCoordIndex->next;
        }
        count++;
        texCoordIndex->next = texCoord;
        texCoord->last = texCoordIndex;
    }
    
    obj->texCoordCount = count;
    texCoord->index = count;
    return texCoord;
}

vertNorm_t *addVertNormToEnd(obj_t *obj) {
    // Allocate the memory for the vertex
    vertNorm_t *vertNorm = (vertNorm_t *) malloc(sizeof(vertNorm_t));
    if (vertNorm == NULL) {
        printf("Error: could not malloc vertex pointer\n");
        return NULL;
    }

    vertNorm->next = NULL;
    vertNorm->last = NULL;
    vertNorm->x = 0.0f;
    vertNorm->y = 0.0f;
    vertNorm->z = 0.0f;

    unsigned int count = 1;
    if (obj->startVertNorm== NULL) {
        obj->startVertNorm = vertNorm;
    } else {
        vertNorm_t *vertNormIndex = obj->startVertNorm;
        while (vertNormIndex->next != NULL) {
            count++;
            vertNormIndex = vertNormIndex->next;
        }
        count++;
        vertNormIndex->next = vertNorm;
        vertNorm->last = vertNormIndex;
    }

    obj->vertNormCount = count;
    vertNorm->index = count;
    return vertNorm;
}

face_t *addFaceToEnd(obj_t *obj) {
    face_t *face = (face_t *) malloc(sizeof(face_t));
    if (face == NULL) {
        printf("Error: could not malloc face pointer\n");
        return NULL;
    }
    face->vertIndex1 = 0;
    face->vertIndex2 = 0;
    face->vertIndex3 = 0;
    face->texCoordIndex1 = 0;
    face->texCoordIndex2 = 0;
    face->texCoordIndex3 = 0;
    face->vertNormIndex1 = 0;
    face->vertNormIndex2 = 0;
    face->vertNormIndex3 = 0;
    face->next = NULL;
    face->last = NULL;

    unsigned int count = 1;
    if (obj->startFace == NULL) {
        obj->startFace = face;
    } else {
        face_t *faceIndex = obj->startFace;
        while (faceIndex->next != NULL) {
            count++;
            faceIndex = faceIndex->next;
        }
        count++;
        faceIndex->next = face;
        face->last = faceIndex;
    }
    obj->faceCount = count;
    face->index = count;
    return face;
}

int setVertCoordinates(obj_t *obj, unsigned int vertIndex, float x, float y, float z) {
    vertex_t *vertex = findVert(obj, vertIndex);
    if (vertex != NULL) {
        vertex->x = x;
        vertex->y = y;
        vertex->z = z;
        return 0;
    }
    return -1;
}

int setTextureCoordinates(obj_t *obj, unsigned int texCoordIndex, float u, float v) {
    texCoord_t *texCoord = findTexCoord(obj, texCoordIndex);
    if (texCoord != NULL) {
        texCoord->u = u;
        texCoord->v = v;
        return 0;
    }
    return -1;
}

int setVertNormCoordinates(obj_t *obj, unsigned int vertNormIndex, float x, float y, float z) {
    vertNorm_t *vertNorm = findVertNorm(obj, vertNormIndex);
    if (vertNorm != NULL) {
        vertNorm->x = x;
        vertNorm->y = y;
        vertNorm->z = z;
        return 0;
    }
    return -1;
}

int setFaceVertIndices(obj_t *obj, unsigned int fI, unsigned int v1I, unsigned int v2I, unsigned int v3I) {
    face_t *face = findFace(obj, fI);
    vertex_t *v1 = findVert(obj, v1I);
    vertex_t *v2 = findVert(obj, v2I);
    vertex_t *v3 = findVert(obj, v3I);

    if (face == NULL || v1 == NULL || v2 == NULL || v3 == NULL) {
        return -1;
    }

    face->vertIndex1 = v1->index;
    face->vertIndex2 = v2->index;
    face->vertIndex3 = v3->index;

    return 0;
}

int setFaceTexCoordIndices(obj_t *obj, unsigned int fI, unsigned int vt1I, unsigned int vt2I, unsigned int vt3I) {
    face_t *face = findFace(obj, fI);
    texCoord_t *vt1 = findTexCoord(obj, vt1I);
    texCoord_t *vt2 = findTexCoord(obj, vt2I);
    texCoord_t *vt3 = findTexCoord(obj, vt3I);

    if (face == NULL || vt1 == NULL || vt2 == NULL || vt3 == NULL) {
        return -1;
    }

    face->texCoordIndex1 = vt1->index;
    face->texCoordIndex2 = vt2->index;
    face->texCoordIndex3 = vt3->index;

    return 0;
}

int setFaceVertNormIndices(obj_t *obj, unsigned int fI, unsigned int vn1I, unsigned int vn2I, unsigned int vn3I) {
    face_t *face = findFace(obj, fI);
    vertNorm_t *vn1 = findVertNorm(obj, vn1I);
    vertNorm_t *vn2 = findVertNorm(obj, vn2I);
    vertNorm_t *vn3 = findVertNorm(obj, vn3I);

    if (face == NULL || vn1 == NULL || vn2 == NULL || vn3 == NULL) {
        return -1;
    }

    face->vertNormIndex1 = vn1->index;
    face->vertNormIndex2 = vn2->index;
    face->vertNormIndex3 = vn3->index;

    return 0;
}

vertex_t *findVert(obj_t *obj, unsigned int vertIndex) {
    vertex_t *vertex = obj->startVertex;

    if (vertex == NULL) {
        return NULL;
    }

    while (vertex != NULL) {
        if (vertex->index == vertIndex) {
            return vertex;
        }
        vertex = vertex->next;
    }

    return NULL;
}

texCoord_t *findTexCoord(obj_t *obj, unsigned int texCoordIndex) {
    texCoord_t *texCoord = obj->startTexCoord;

    if (texCoord == NULL) {
        return NULL;
    }

    while (texCoord != NULL) {
        if (texCoord->index == texCoordIndex) {
            return texCoord;
        }
        texCoord = texCoord->next;
    }

    return NULL;
}

vertNorm_t *findVertNorm(obj_t *obj, unsigned int vertNormIndex) {
    vertNorm_t *vertNorm = obj->startVertNorm;

    if (vertNorm == NULL) {
        return NULL;
    }

    while (vertNorm != NULL) {
        if (vertNorm->index == vertNormIndex) {
            return vertNorm;
        }
        vertNorm = vertNorm->next;
    }

    return NULL;
}

face_t *findFace(obj_t *obj, unsigned int faceIndex) {
    face_t *face = obj->startFace;

    if (face == NULL) {
        return NULL;
    }

    while (face != NULL) {
        if (face->index == faceIndex) {
            return face;
        }
        face = face->next;
    }

    return NULL;
}

float *flattenVerts(obj_t *obj) {
    if (obj->vertexCount == 0) {
        return NULL;
    }
    float *vertArray = (float *) malloc(sizeof(float) * obj->vertexCount * 3);
    if(vertArray == NULL) {
        printf("Error: could not malloc vertex float array\n");
        return NULL;
    }

    int count = 0;
    vertex_t *vert = obj->startVertex;
    while (vert != NULL && count < obj->vertexCount * 3) {
        vertArray[count] = vert->x;
        vertArray[count + 1] = vert->y;
        vertArray[count + 2] = vert->z;

        count += 3;
        vert = vert->next;
    }

    return vertArray;
}

float *flattenTexCoords(obj_t *obj) {
    if (obj->texCoordCount == 0) {
        return NULL;
    }
    float *texCoordArray = (float *) malloc(sizeof(float) * obj->texCoordCount * 2);
    if(texCoordArray == NULL) {
        printf("Error: could not malloc texCoord float array\n");
        return NULL;
    }

    int count = 0;
    texCoord_t *texCoord = obj->startTexCoord;
    while (texCoord != NULL && count < obj->texCoordCount * 2) {
        texCoordArray[count] = texCoord->u;
        texCoordArray[count + 1] = texCoord->v;

        count += 2;
        texCoord = texCoord->next;
    }

    return texCoordArray;
}

float *flattenVertNorms(obj_t *obj) {
    if (obj->vertNormCount == 0) {
        return NULL;
    }
    float *vertNormArray = (float *) malloc(sizeof(float) * obj->vertNormCount * 3);
    if(vertNormArray == NULL) {
        printf("Error: could not malloc vertex norm float array\n");
        return NULL;
    }

    int count = 0;
    vertNorm_t *vertNorm = obj->startVertNorm;
    while (vertNorm != NULL && count < obj->vertNormCount * 3) {
        vertNormArray[count] = vertNorm->x;
        vertNormArray[count + 1] = vertNorm->y;
        vertNormArray[count + 2] = vertNorm->z;

        count += 3;
        vertNorm = vertNorm->next;
    }

    return vertNormArray;
}

unsigned int *flattenFaces(obj_t *obj) {
    if (obj->faceCount == 0) {
        return NULL;
    }

    unsigned int *faceArray = (unsigned int *) malloc(sizeof(int) * obj->faceCount * 3);
    if(faceArray == NULL) {
        printf("Error: could not malloc face int array\n");
        return NULL;
    }

    int count = 0;
    face_t *face = obj->startFace;
    while (face != NULL && count < obj->faceCount * 3) {
        faceArray[count] = face->vertIndex1 - 1;
        faceArray[count + 1] = face->vertIndex2 - 1;
        faceArray[count + 2] = face->vertIndex3 - 1;

        count += 3;
        face = face->next;
    }

    return faceArray;
}