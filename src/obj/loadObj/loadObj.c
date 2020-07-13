

#include "loadObj.h"

obj_t *loadObj(char *data) {
    obj_t *obj = createObj();

    char *line = data;

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
        } else if (!strcmp(s, "f")) { // read face indices
            face_t *face = addFaceToEnd(obj);
            int v1, v2, v3;
            sscanf(line, "%s %d %d %d", s, &v1, &v2, &v3);
            setFaceVertIndices(obj, face->index, v1, v2, v3);
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