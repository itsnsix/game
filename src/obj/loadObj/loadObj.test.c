/**
 * @author nsix
 * @file objUtils.test.c
 * @brief Unit test for loadObj
 */

#include "testUtils.h"
#include "loadObj.h"

void setup() {

}

void teardown() {

}

void test_loadObj() {
    char objData[] =
            "v -1.000000 0.000000 1.000000\n"
            "v 1.000000 0.000000 1.000000\n"
            "v -1.000000 0.000000 -1.000000\n"
            "s off\n"
            "f 3 2 1";

    obj_t *obj = loadObj(objData);
    assert("obj has 3 vertices", obj->vertexCount == 3);
    assert("obj has 1 face", obj->faceCount == 1);
    vertex_t *v1 = obj->startVertex;
    vertex_t *v2 = v1->next;
    vertex_t *v3 = v2->next;
    assert("vertices correctly point to next vertex", v1->next == v2 && v2->next == v3 && v3->next == NULL);
    assert("vertices correctly point to last vertex", v3->last == v2 && v2->last == v1 && v1->last == NULL);
    face_t *face = obj->startFace;
    assert("faces have the correct vert indices", face->vertIndex1 == 3 && face->vertIndex2 == 2 && face->vertIndex3 == 1);

    assert("vert1 has correct coordinates", v1->x == -1.000000 && v1->y == 0.000000 && v1->z == 1.000000);
    assert("vert2 has correct coordinates", v2->x == 1.000000 && v2->y == 0.000000 && v1->z == 1.000000);
    assert("vert3 has correct coordinates", v3->x == -1.000000 && v3->y == 0.000000 && v3->z == -1.000000);

    deleteObj(&obj);
}

void test_loadObjFromFile() {
    obj_t *obj = loadObjFromFile(TRIANGLE_OBJ_FILE_PATH);
    assert("obj has 3 vertices", obj->vertexCount == 3);
    assert("obj has 1 face", obj->faceCount == 1);
    vertex_t *v1 = obj->startVertex;
    vertex_t *v2 = v1->next;
    vertex_t *v3 = v2->next;
    assert("vertices correctly point to next vertex", v1->next == v2 && v2->next == v3 && v3->next == NULL);
    assert("vertices correctly point to last vertex", v3->last == v2 && v2->last == v1 && v1->last == NULL);
    face_t *face = obj->startFace;
    assert("faces have the correct vert indices", face->vertIndex1 == 3 && face->vertIndex2 == 2 && face->vertIndex3 == 1);

    assert("vert1 has correct coordinates", v1->x == -1.000000 && v1->y == 0.000000 && v1->z == 1.000000);
    assert("vert2 has correct coordinates", v2->x == 1.000000 && v2->y == 0.000000 && v1->z == 1.000000);
    assert("vert3 has correct coordinates", v3->x == -1.000000 && v3->y == 0.000000 && v3->z == -1.000000);
    deleteObj(&obj);
}

int main() {
    initSuite("loadObj", &setup, &teardown);
    addTest(test_loadObj);
    addTest(test_loadObjFromFile);
    runTests();
    return 0;
}