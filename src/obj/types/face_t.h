

#ifndef GAME_FACE_T_H
#define GAME_FACE_T_H

typedef struct face_t {
    unsigned int vertIndex1;
    unsigned int vertIndex2;
    unsigned int vertIndex3;
    unsigned int faceIndex;
    struct face_t *next;
    struct face_t *last;
} face_t;

#endif //GAME_FACE_T_H
