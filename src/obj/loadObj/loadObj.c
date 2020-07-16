

#include "loadObj.h"

obj_t *loadObj(char *data) {
    obj_t *obj = createObj();

    char *line = data;

    int hasTexCoords = 0;
    int hasVertNorms = 0;

    while (line) {
        char *newline = strchr(line, '\n');
        if (newline) {
            *newline = '\0';
        }

        char s[3];
        sscanf(line, "%s", s);
        if (!strcmp(s, "o")) { // read object name
            char objName[24];
            sscanf(line, "%s %s", s, objName);
            setObjName(obj, objName);
        } else if (!strcmp(s, "v")) { // read vertices
            vertex_t *v = addVertToEnd(obj);
            float x, y, z;
            sscanf(line, "%s %f %f %f", s, &x, &y, &z);
            setVertCoordinates(obj, v->index, x, y, z);
        } else if (!strcmp(s, "vt")) { // texture coordinates
            hasTexCoords = 1;
            texCoord_t *vt = addTexCoordToEnd(obj);
            float u, v;
            sscanf(line, "%s %f %f", s, &u, &v);
            setTextureCoordinates(obj, vt->index, u, v);
        } else if (!strcmp(s, "vn")) { // read vertex normals
            hasVertNorms = 1;
            vertNorm_t *vn = addVertNormToEnd(obj);
            float x, y, z;
            sscanf(line, "%s %f %f %f", s, &x, &y, &z);
            setVertNormCoordinates(obj, vn->index, x, y, z);
        } else if (!strcmp(s, "f")) { // read face indices
            face_t *face = addFaceToEnd(obj);
            int v1, v2, v3;
            if (!hasTexCoords && !hasVertNorms) {
                sscanf(line, "%s %d %d %d", s, &v1, &v2, &v3);
                setFaceVertIndices(obj, face->index, v1, v2, v3);
            } else if (hasTexCoords && !hasVertNorms) {
                int vt1, vt2, vt3;
                sscanf(line, "%s %d/%d %d/%d %d/%d", s, &v1, &vt1, &v2, &vt2, &v3, &vt3);
                setFaceVertIndices(obj, face->index, v1, v2, v3);
                setFaceTexCoordIndices(obj, face->index, vt1, vt2, vt3);
            } else if (!hasTexCoords && hasVertNorms) {
                int vn1, vn2, vn3;
                sscanf(line, "%s %d//%d %d//%d %d//%d", s, &v1, &vn1, &v2, &vn2, &v3, &vn3);
                setFaceVertIndices(obj, face->index, v1, v2, v3);
                setFaceVertNormIndices(obj, face->index, vn1, vn2, vn3);
            } else {
                int vt1, vt2, vt3;
                int vn1, vn2, vn3;
                sscanf(line, "%s %d/%d/%d %d/%d/%d %d/%d/%d", s, &v1, &vt1, &vn1, &v2, &vt2, &vn2, &v3, &vt3, &vn3);
                setFaceVertIndices(obj, face->index, v1, v2, v3);
                setFaceTexCoordIndices(obj, face->index, vt1, vt2, vt3);
                setFaceVertNormIndices(obj, face->index, vn1, vn2, vn3);
            }

        }

        if (newline) {
            *newline = '\n';
        }

        line = newline ? newline + 1 : NULL;
    }

    return obj;
}

obj_t *loadObjFromFile(const char *filePath) {
    FILE *file = fopen(filePath, "r");
    if (file == NULL) {
        printf("Couldn't open file. errno: %d\n", errno);
        return NULL;
    }
    fseek(file, 0, SEEK_END);
    long fsize = ftell(file);
    fseek(file, 0, SEEK_SET);

    char *fileContents = (char *) malloc(sizeof(char) * fsize);
    fread(fileContents, 1, fsize, file);
    fclose(file);

    fileContents[fsize] = '\0';
    obj_t *obj = loadObj(fileContents);
    free(fileContents);
    return obj;
}