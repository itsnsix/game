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
            printf("Warning: Possible memory leak.\nFreed Vert Count: %d\nDeclared Vert Count: %d\n", vertFreeCount, (*obj)->vertexCount);
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

void setVertCoordinates(vertex_t *vertex, float x, float y, float z) {
    vertex->x = x;
    vertex->y = y;
    vertex->z = z;
}

void addFaceToEnd(obj_t *obj) {
    face_t *face = (face_t *) malloc(sizeof(face_t));
    face->vertIndex1 = 0;
    face->vertIndex2 = 0;
}