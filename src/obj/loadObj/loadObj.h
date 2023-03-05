

#ifndef GAME_LOADOBJ_H
#define GAME_LOADOBJ_H

#include <stdio.h>
#include <string.h>
#include "obj_t.h"
#include "objUtils.h"
#include "loadFile.h"

/**
 * @function loadOBJ
 * @brief loads an obj data information from a string
 * @param data - the string containing the obj data
 * @return obj - obj_t initialized with the verts and faces from the data
 */
obj_t *loadObj(char *data);
/**
 * @function loadObjFromFile
 * @brief reads obj data from utils into an obj_t struct
 * @param filePath - Path to the utils to load
 * @return obj - obj_t initialized with the verts and faces from the data
 */
obj_t *loadObjFromFile(const char *filePath);

#endif //GAME_LOADOBJ_H
