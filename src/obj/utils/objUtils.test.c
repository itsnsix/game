/**
 * @author nsix
 * @file objUtils.test.c
 * @brief Unit test for objUtils
 */

#include <stdio.h>
#include "objUtils.h"
#include "testUtils.h"

void setup() {

}

void tearDown() {

}

void test_createObj() {
    obj_t *obj = createObj();
    assert("obj struct has correct name", !strcmp(obj->objName, "New Obj"));
    assert("obj has vert count of 0", obj->vertexCount == 0);
    assert("obj has starting vert of NULL", obj->startVertex == NULL);
    assert("obj has face count of 0", obj->faceCount == 0);
    assert("obj has starting face of NULL", obj->startFace == NULL);
    deleteObj(&obj);
    assert("obj was deleted", obj == NULL);
}

/** @note: to actually test deletion, run valgrind */
void test_deleteObj() {
    obj_t *obj = createObj();
    assert("obj struct has correct name", !strcmp(obj->objName, "New Obj"));
    assert("obj has vert count of 0", obj->vertexCount == 0);
    assert("obj has starting vert of NULL", obj->startVertex == NULL);
    assert("obj has face count of 0", obj->faceCount == 0);
    assert("obj has starting face of NULL", obj->startFace == NULL);
    deleteObj(&obj);
    assert("obj was deleted", obj == NULL);
}

void test_setObjName() {
    obj_t *obj = createObj();
    assert("obj struct has correct name", !strcmp(obj->objName, "New Obj"));
    setObjName(obj, "Renamed Obj");
    assert("obj struct has correct name", !strcmp(obj->objName, "Renamed Obj"));
    deleteObj(&obj);
}

void test_addVertToEnd() {
    obj_t *obj = createObj();
    addVertToEnd(obj);
    vertex_t *vert0 = obj->startVertex;
    assert("obj has 1 vert", obj->vertexCount == 1);
    assert("vert0 is not null", vert0 != NULL);
    assert("vert0 has correct index", vert0->vertIndex == 1);
    assert("vert0 has correct x coordinates", vert0->x == 0.0f);
    assert("vert0 has correct y coordinates", vert0->y == 0.0f);
    assert("vert0 has correct z coordinates", vert0->z == 0.0f);
    assert("vert0 has null next", vert0->next == NULL);
    assert("vert0 has null last", vert0->last == NULL);

    addVertToEnd(obj);
    vertex_t *vert1 = vert0->next;

    assert("obj has 2 verts", obj->vertexCount == 2);
    assert("vert0 does not have null next", vert0->next != NULL);
    assert("vert1 has null next", vert1->next == NULL);
    assert("vert1 does not have last", vert1->last != NULL);
    assert("vert1 has correct index", obj->startVertex->next->vertIndex == 2);
    assert("vert0->next points to vert1", vert0->next == vert1);
    assert("vert1->last points to vert0", vert1->last == vert0);

    addVertToEnd(obj);
    vertex_t *vert2 = vert1->next;

    assert("obj has 3 verts", obj->vertexCount == 3);
    assert("vert2 has correct index", vert2->vertIndex == 3);
    assert("vert2 has null next", vert2->next == NULL);
    assert("vert2 does not have null last", vert2->last != NULL);
    assert("vert1->next points to vert2", vert1->next == vert2);
    assert("vert2->last points to vert1", vert2->last == vert1);
    deleteObj(&obj);
}

void test_addFaceToEnd() {
    obj_t *obj = createObj();
    addFaceToEnd(obj);
    face_t *face0 = obj->startFace;
    assert("obj has 1 face", obj->faceCount == 1);
    assert("face0 is not null", face0 != NULL);
    assert("face0 has the correct face index", face0->faceIndex == 1);
    assert("face0 has the correct vertex indices",
           face0->vertIndex1 == 0 && face0->vertIndex2 == 0 && face0->vertIndex3 == 0);
    assert("face0 last is null", face0->last == NULL);
    assert("face0 next is null", face0->next == NULL);

    addFaceToEnd(obj);
    face_t *face1 = face0->next;
    assert("obj has 2 faces", obj->faceCount == 2);
    assert("face1 is not null", face1 != NULL);
    assert("face1->last points to face0", face1->last == face0);
    assert("face0->next points to face1", face0->next == face1);
    assert("face1->next points to null", face1->next == NULL);

    addFaceToEnd(obj);
    face_t *face2 = face1->next;
    assert("obj has 3 faces", obj->faceCount == 3);
    assert("face2 is not null", face2 != NULL);
    assert("face2->last points to face1", face2->last == face1);
    assert("face1->next points to face2", face1->next == face2);
    assert("face2->next points to null", face2->next == NULL);
    deleteObj(&obj);
}

void test_setVertCoordinates() {
    obj_t *obj = createObj();
    addVertToEnd(obj);
    vertex_t *vert0 = obj->startVertex;
    assert("vert0 has correct x coordinates", vert0->x == 0.0f);
    assert("vert0 has correct y coordinates", vert0->y == 0.0f);
    assert("vert0 has correct z coordinates", vert0->z == 0.0f);
    setVertCoordinates(obj, vert0->vertIndex, -0.5f, 0.5f, -0.5f);
    assert("vert0 has correct x coordinates", vert0->x == -0.5f);
    assert("vert0 has correct y coordinates", vert0->y == 0.5f);
    assert("vert0 has correct z coordinates", vert0->z == -0.5f);

    int result = setVertCoordinates(obj, 10, -0.5f, 0.5f, -0.5f);
    assert("setVertCoordinates returns -1 when it can't find the vert", result == -1);

    deleteObj(&obj);
}

void test_setFaceVertIndices() {
    obj_t *obj = createObj();
    addVertToEnd(obj);
    vertex_t *v1 = obj->startVertex;
    addVertToEnd(obj);
    vertex_t *v2 = v1->next;
    addVertToEnd(obj);
    vertex_t *v3 = v2->next;

    addFaceToEnd(obj);
    face_t *face = obj->startFace;

    setFaceVertIndices(obj, face->faceIndex, v1->vertIndex, v2->vertIndex, v3->vertIndex);

    assert("face has the correct vert indices 1", face->vertIndex1 == v1->vertIndex);
    assert("face has the correct vert indices 2", face->vertIndex2 == v2->vertIndex);
    assert("face has the correct vert indices 3", face->vertIndex3 == v3->vertIndex);

    int result = setFaceVertIndices(obj, 10, v1->vertIndex, v2->vertIndex, v3->vertIndex);
    assert("setFaceVertIndices returns -1 if it can't find the face", result == -1);
    result = setFaceVertIndices(obj, face->faceIndex, 10, v2->vertIndex, v3->vertIndex);
    assert("setFaceVertIndices returns -1 if it can't find v1", result == -1);
    result = setFaceVertIndices(obj, face->faceIndex, v1->vertIndex, 10, v3->vertIndex);
    assert("setFaceVertIndices returns -1 if it can't find v2", result == -1);
    result = setFaceVertIndices(obj, face->faceIndex, v1->vertIndex, v2->vertIndex, 10);
    assert("setFaceVertIndices returns -1 if it can't find v3", result == -1);

    deleteObj(&obj);
}

void test_findVert() {
    obj_t *obj = createObj();
    addVertToEnd(obj);
    vertex_t *v1 = obj->startVertex;
    addVertToEnd(obj);
    vertex_t *v2 = v1->next;
    addVertToEnd(obj);
    vertex_t *v3 = v2->next;

    vertex_t *vert = findVert(obj, v1->vertIndex);
    assert("find vert found the correct vert", vert == v1);
    vert = findVert(obj, v2->vertIndex);
    assert("find vert found the correct vert", vert == v2);
    vert = findVert(obj, v3->vertIndex);
    assert("find vert found the correct vert", vert == v3);
    vert = findVert(obj, 100);
    assert("find vert returned null when it couldn't find the vert", vert == NULL);

    deleteObj(&obj);
}

void test_findFace() {
    obj_t *obj = createObj();
    addFaceToEnd(obj);
    face_t *f1 = obj->startFace;
    addFaceToEnd(obj);
    face_t *f2 = f1->next;
    addFaceToEnd(obj);
    face_t *f3 = f2->next;

    face_t *face = findFace(obj, f1->faceIndex);
    assert("find face found the correct face", face == f1);
    face = findFace(obj, f2->faceIndex);
    assert("find face found the correct face", face == f2);
    face = findFace(obj, f3->faceIndex);
    assert("find face found the correct face", face == f3);
    face = findFace(obj, 100);
    assert("find face returned null when it couldn't find the face", face == NULL);

    deleteObj(&obj);
}

int main() {
    initSuite("objUtils", &setup, &tearDown);
    addTest(test_createObj);
    addTest(test_deleteObj);
    addTest(test_setObjName);
    addTest(test_addVertToEnd);
    addTest(test_addFaceToEnd);
    addTest(test_setVertCoordinates);
    addTest(test_setFaceVertIndices);
    addTest(test_findVert);
    addTest(test_findFace);
    runTests();
    return 0;
}