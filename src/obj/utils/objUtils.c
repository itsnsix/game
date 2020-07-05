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
    obj->faceCount = 0;
    obj->vertexCount = 0;
    obj->startVertex = NULL;
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
            printf("Warning: Possible memory leak.\nFace Vert Count: %d\nDeclared Face Count: %d\n", vertFreeCount,
                   (*obj)->vertexCount);
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

face_t *addFaceToEnd(obj_t *obj) {
    face_t *face = (face_t *) malloc(sizeof(face_t));
    if (face == NULL) {
        printf("Error: could not malloc face pointer\n");
        return NULL;
    }
    face->vertIndex1 = 0;
    face->vertIndex2 = 0;
    face->vertIndex3 = 0;
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