/**
 * @author nsix
 * @file vertex_t
 * @brief defines the obj vertex
 * @note vertex indices start at 1 -- same as obj files
 */

#ifndef GAME_VERTEX_T_H
#define GAME_VERTEX_T_H
typedef struct vertex_t {
    float x;
    float y;
    float z;
    unsigned int index;
    struct vertex_t *next;
    struct vertex_t *last;
} vertex_t;
#endif //GAME_VERTEX_T_H
