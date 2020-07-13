/**
 * Created by nsix on 7/5/2020.
 */

#ifndef GAME_GLSLUTILS_H
#define GAME_GLSLUTILS_H

#include <string.h>
#include <stdio.h>
#include <malloc.h>
#include <errno.h>
#include <GL/glew.h>

int createShader(const char *source, unsigned int shaderType, unsigned int programId);

int createShaderFromFile(const char *filePath, unsigned int shaderType, unsigned int programId);

int linkProgram(unsigned int programId);

#endif //GAME_GLSLUTILS_H
