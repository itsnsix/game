/**
 * Created by nsix on 7/5/2020.
 */

#include "glslUtils.h"

int createShader(const char *source, unsigned int shaderType, unsigned int programId) {
    char infoLog[512];

    GLuint shader = glCreateShader(shaderType);

    glShaderSource(shader, 1, &source, NULL);
    glCompileShader(shader);
    GLint compiled = GL_FALSE;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
    if (compiled != GL_TRUE) {
        printf("Unable to compile shader %d\n", shader);
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        printf("Error: %s\n", infoLog);
        return -1;
    }
    glAttachShader(programId, shader);
    glDeleteShader(shader);
    return 0;
}

int createShaderFromFile(const char *filePath, unsigned int shaderType, unsigned int programId) {
    FILE *file = fopen(filePath, "r");
    if (file == NULL) {
        printf("Couldn't open file. errno: %d\n", errno);
        return -1;
    }
    fseek(file, 0, SEEK_END);
    long fsize = ftell(file);
    fseek(file, 0, SEEK_SET);

    char *fileContents = (char *) malloc(sizeof(char) * fsize);
    fread(fileContents, 1, fsize, file);
    fclose(file);

    fileContents[fsize] = '\0';

    return createShader(fileContents, shaderType, programId);
}

int linkProgram(unsigned int programId) {
    glLinkProgram(programId);
    GLint programSuccess = GL_TRUE;
    glGetProgramiv(programId, GL_LINK_STATUS, &programSuccess);
    if (programSuccess != GL_TRUE) {
        printf("Error linking program %d!\n", programId);
        return -1;
    }
    return 0;
}