/**
 * Created by nsix on 7/15/2020.
 */

#ifndef GAME_TEXCOORD_T_H
#define GAME_TEXCOORD_T_H

typedef struct texCoord_t {
    float u;
    float v;
    unsigned int index;
    struct texCoord_t *next;
    struct texCoord_t *last
} texCoord_t;
#endif //GAME_TEXCOORD_T_H
