//
// Created by nsix on 2/21/21.
//

#ifndef GAME_BYTESWAP_H
#define GAME_BYTESWAP_H
#include <stdlib.h>

/**
 * Reverses the order of n number of bytes starting with the first byte pointed to
 * @param bytes - pointer to the start of bytes to swap
 * @param size - number of bytes to swap
 */
void byteSwap(char *bytes, size_t n);
#endif //GAME_BYTESWAP_H