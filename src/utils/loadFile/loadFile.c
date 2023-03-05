#include "loadFile.h"

char * loadFile(const char *filePath) {
    FILE *file = fopen(filePath, "r");
    if (file == NULL) {
        printf("Couldn't open file. errno: %d\n", errno);
        return NULL;
    }
    fseek(file, 0, SEEK_END);
    long fsize = ftell(file);
    fseek(file, 0, SEEK_SET);

    char *fileContents = (char *) malloc(sizeof(char) * fsize + 1);
    fread(fileContents, 1, fsize, file);
    fclose(file);

    fileContents[fsize] = '\0';

    return fileContents;
}