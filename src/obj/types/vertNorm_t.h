/**
 * Created by nsix on 7/15/2020.
 */

#ifndef GAME_VERTNORM_T_H
#define GAME_VERTNORM_T_H

typedef struct vertNorm_t {
    float x;
    float y;
    float z;
    unsigned int index;
    struct vertNorm_t *next;
    struct vertNorm_t *last;
} vertNorm_t;

#endif //GAME_VERTNORM_T_H
