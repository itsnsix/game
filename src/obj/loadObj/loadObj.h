

#ifndef RACING_GAME_LOADOBJ_H
#define RACING_GAME_LOADOBJ_H

#include "obj_t.h"

/**
 * @function loadOBJ
 * @brief loads an obj data information from a string
 * @param data - the string containing the obj data
 * @param obj - pointer to the object to load it into
 */
void loadObj(const char *data, obj_t *obj);

/**
 * @function loadObjFromFile
 * @brief reads obj data from file into an obj_t struct
 * @param file - Path to the file to load
 * @param obj - pointer to the object to load data into
 */
void loadObjFromFile(const char *file, obj_t *obj);

#endif //RACING_GAME_LOADOBJ_H
