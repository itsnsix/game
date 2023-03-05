//
// Created by nsix on 2/21/21.
//

#include "byteSwap.h"

void byteSwap(char *bytes, size_t n) {
    for (int i = 0; i < (n + 1) / 2; i++) {
        char tmp = bytes[i];
        bytes[i] = bytes[n - i - 1];
        bytes[n - i - 1] = tmp;
    }
}