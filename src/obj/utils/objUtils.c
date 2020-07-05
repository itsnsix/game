/**
 * @author nsix
 * @file objUtils.c
 * @brief Utilities for creating, modifying, and destroying obj_t types
 * @see objUtils.h for function descriptions
 */

#include <stddef.h>
#include <string.h>
#include <stdio.h>
#include <malloc.h>
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

void addVertToEnd(obj_t *obj) {
    // Allocate the memory for the vertex
    vertex_t *vertex = (vertex_t *) malloc(sizeof(vertex_t));
    if (vertex == NULL) {
        printf("Error: could not malloc vertex pointer\n");
        return;
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
    vertex->vertIndex = count;
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

void addFaceToEnd(obj_t *obj) {
    face_t *face = (face_t *) malloc(sizeof(face_t));
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
    face->faceIndex = count;
}

int setFaceVertIndices(obj_t *obj, unsigned int fI, unsigned int v1I, unsigned int v2I, unsigned int v3I) {
    face_t *face = findFace(obj, fI);
    vertex_t *v1 = findVert(obj, v1I);
    vertex_t *v2 = findVert(obj, v2I);
    vertex_t *v3 = findVert(obj, v3I);

    if (face == NULL || v1 == NULL || v2 == NULL || v3 == NULL) {
        return -1;
    }

    face->vertIndex1 = v1->vertIndex;
    face->vertIndex2 = v2->vertIndex;
    face->vertIndex3 = v3->vertIndex;

    return 0;
}

vertex_t *findVert(obj_t *obj, unsigned int vertIndex) {
    vertex_t *vertex = obj->startVertex;

    if (vertex == NULL) {
        return NULL;
    }

    while (vertex != NULL) {
        if (vertex->vertIndex == vertIndex) {
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
        if (face->faceIndex == faceIndex) {
            return face;
        }
        face = face->next;
    }

    return NULL;
}