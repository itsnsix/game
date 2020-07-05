/**
 * @author nsix
 * @file objUtils.test.c
 * @brief Unit test for objUtils
 */

#include "objUtils.h"
#include <stdio.h>
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

}

void test_setVertCoordinates() {
    obj_t *obj = createObj();
    addVertToEnd(obj);
    vertex_t *vert0 = obj->startVertex;
    assert("vert0 has correct x coordinates", vert0->x == 0.0f);
    assert("vert0 has correct y coordinates", vert0->y == 0.0f);
    assert("vert0 has correct z coordinates", vert0->z == 0.0f);
    setVertCoordinates(vert0, -0.5f, 0.5f, -0.5f);
    assert("vert0 has correct x coordinates", vert0->x == -0.5f);
    assert("vert0 has correct y coordinates", vert0->y == 0.5f);
    assert("vert0 has correct z coordinates", vert0->z == -0.5f);
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
    runTests();
    return 0;
}