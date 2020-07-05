

#ifndef RACING_GAME_FACE_T_H
#define RACING_GAME_FACE_T_H

typedef struct {
    unsigned int vertIndex1;
    unsigned int vertIndex2;
    unsigned int vertIndex3;
    unsigned int faceIndex;
    struct face_t *next;
    struct face_t *last;
} face_t;

#endif //RACING_GAME_FACE_T_H
