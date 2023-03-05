
#ifndef GAME_IMAGE_T_H
#define GAME_IMAGE_T_H

#include <stddef.h>
#include <stdlib.h>
typedef struct {
    unsigned char *imageData;
    char imageType[4];
    u_int32_t width;
    u_int32_t height;
    u_int8_t bitDepth;
    u_int8_t colorType;
    u_int8_t compressionMethod;
    u_int8_t filterMethod;
    u_int8_t interlaceMethod;

} image_t;
#endif //GAME_IMAGE_T_H
