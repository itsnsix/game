/**
 * @author nsix
 * @file face_t.h
 * @brief Defines the face_t struct for obj faces
 * @note face indices start at 1 -- same as obj files.
 */

#ifndef GAME_FACE_T_H
#define GAME_FACE_T_H

typedef struct face_t {
    unsigned int vertIndex1;
    unsigned int vertIndex2;
    unsigned int vertIndex3;
    unsigned int index;
    struct face_t *next;
    struct face_t *last;
} face_t;

#endif //GAME_FACE_T_H
