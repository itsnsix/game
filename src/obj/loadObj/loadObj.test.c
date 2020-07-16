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
    obj_t *obj = loadObjFromFile(DATA_DIR "triangle.obj");
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

void test_loadObjFromFile_vt() {
    obj_t *obj = loadObjFromFile(DATA_DIR "plane_vt.obj");

    vertex_t *v1 = obj->startVertex;
    vertex_t *v2 = v1->next;
    vertex_t *v3 = v2->next;
    vertex_t *v4 = v3->next;

    texCoord_t *vt1 = obj->startTexCoord;
    texCoord_t *vt2 = vt1->next;
    texCoord_t *vt3 = vt2->next;
    texCoord_t *vt4 = vt3->next;

    face_t *f1 = obj->startFace;
    face_t *f2 = f1->next;

    assert("vert1 has correct coordinates", v1->x == -1.0 && v1->y == 0.000000 && v1->z == 1.0);
    assert("vert2 has correct coordinates", v2->x == 1.0 && v2->y == 0.000000 && v1->z == 1.0);
    assert("vert3 has correct coordinates", v3->x == -1.0 && v3->y == 0.000000 && v3->z == -1.0);
    assert("vert3 has correct coordinates", v4->x == 1.0 && v4->y == 0.000000 && v4->z == -1.0);

    assert("texCoord1 has correct coordinates", vt1->u == 1.000000 && vt1->v == 0.000000);
    assert("texCoord2 has correct coordinates", vt2->u == 0.000000 && vt2->v == 1.000000);
    assert("texCoord3 has correct coordinates", vt3->u == 0.000000 && vt3->v == 0.000000);
    assert("texCoord4 has correct coordinates", vt4->u == 1.000000 && vt4->v == 1.000000);

    assert("face1 has correct texCoord indices", f1->texCoordIndex1 == vt1->index && f1->texCoordIndex2 == vt2->index && f1->texCoordIndex3 == vt3->index);
    assert("face2 has correct texCoord indices", f2->texCoordIndex1 == vt1->index && f2->texCoordIndex2 == vt4->index && f2->texCoordIndex3 == vt2->index);
    deleteObj(&obj);
}

void test_loadObjFromFile_vn() {
    obj_t *obj = loadObjFromFile(DATA_DIR "plane_vn.obj");

    vertex_t *v1 = obj->startVertex;
    vertex_t *v2 = v1->next;
    vertex_t *v3 = v2->next;
    vertex_t *v4 = v3->next;

    vertNorm_t *vn1 = obj->startVertNorm;

    face_t *f1 = obj->startFace;
    face_t *f2 = f1->next;

    assert("vert1 has correct coordinates", v1->x == -1.0 && v1->y == 0.000000 && v1->z == 1.0);
    assert("vert2 has correct coordinates", v2->x == 1.0 && v2->y == 0.000000 && v1->z == 1.0);
    assert("vert3 has correct coordinates", v3->x == -1.0 && v3->y == 0.000000 && v3->z == -1.0);
    assert("vert3 has correct coordinates", v4->x == 1.0 && v4->y == 0.000000 && v4->z == -1.0);

    assert("vertNorm1 has correct coordinates", vn1->x == 0.000000 && vn1->y == 1.000000 && vn1->z == 0.000000);

    assert("face1 has correct vertNorm indices", f1->vertNormIndex1 == vn1->index && f1->vertNormIndex2 == vn1->index && f1->vertNormIndex3 == vn1->index);
    assert("face2 has correct vertNorm indices", f2->vertNormIndex1 == vn1->index && f2->vertNormIndex2 == vn1->index && f2->vertNormIndex3 == vn1->index);
    deleteObj(&obj);
}

void test_loadObjFromFile_vtvn() {
    obj_t *obj = loadObjFromFile(DATA_DIR "plane_vtvn.obj");

    vertex_t *v1 = obj->startVertex;
    vertex_t *v2 = v1->next;
    vertex_t *v3 = v2->next;
    vertex_t *v4 = v3->next;

    texCoord_t *vt1 = obj->startTexCoord;
    texCoord_t *vt2 = vt1->next;
    texCoord_t *vt3 = vt2->next;
    texCoord_t *vt4 = vt3->next;

    vertNorm_t *vn1 = obj->startVertNorm;

    face_t *f1 = obj->startFace;
    face_t *f2 = f1->next;

    assert("vert1 has correct coordinates", v1->x == -1.0 && v1->y == 0.000000 && v1->z == 1.0);
    assert("vert2 has correct coordinates", v2->x == 1.0 && v2->y == 0.000000 && v1->z == 1.0);
    assert("vert3 has correct coordinates", v3->x == -1.0 && v3->y == 0.000000 && v3->z == -1.0);
    assert("vert3 has correct coordinates", v4->x == 1.0 && v4->y == 0.000000 && v4->z == -1.0);

    assert("texCoord1 has correct coordinates", vt1->u == 1.000000 && vt1->v == 0.000000);
    assert("texCoord2 has correct coordinates", vt2->u == 0.000000 && vt2->v == 1.000000);
    assert("texCoord3 has correct coordinates", vt3->u == 0.000000 && vt3->v == 0.000000);
    assert("texCoord4 has correct coordinates", vt4->u == 1.000000 && vt4->v == 1.000000);

    assert("vertNorm1 has correct coordinates", vn1->x == 0.000000 && vn1->y == 1.000000 && vn1->z == 0.000000);

    assert("face1 has correct vertNorm indices", f1->vertNormIndex1 == vn1->index && f1->vertNormIndex2 == vn1->index && f1->vertNormIndex3 == vn1->index);
    assert("face2 has correct vertNorm indices", f2->vertNormIndex1 == vn1->index && f2->vertNormIndex2 == vn1->index && f2->vertNormIndex3 == vn1->index);
    assert("face1 has correct texCoord indices", f1->texCoordIndex1 == vt1->index && f1->texCoordIndex2 == vt2->index && f1->texCoordIndex3 == vt3->index);
    assert("face2 has correct texCoord indices", f2->texCoordIndex1 == vt1->index && f2->texCoordIndex2 == vt4->index && f2->texCoordIndex3 == vt2->index);

    deleteObj(&obj);
}



int main() {
    initSuite("loadObj", &setup, &teardown);
    addTest(test_loadObj);
    addTest(test_loadObjFromFile);
    addTest(test_loadObjFromFile_vt);
    addTest(test_loadObjFromFile_vn);
    addTest(test_loadObjFromFile_vtvn);
    runTests();
    return 0;
}