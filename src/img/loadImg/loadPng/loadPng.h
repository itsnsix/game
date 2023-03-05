#ifndef GAME_LOADPNG_H
#define GAME_LOADPNG_H

#include <string.h>
#include <stdio.h>
#include "image_t.h"
#include "loadFile.h"
#include "byteSwap.h"
/**
 * Verifies the first 8 bytes of a png image
 * @param pngHeader - Pointer to the start of the png data
 * @return - 1 if the utils is valid, 0 if it is invalid.
 */
int verifyPngSignature(const char *pngHeader);
/**
 * Loads png image data into an image_t pointer
 * @param data - Pointer to the start of the png data
 * @return - pointer to the image_t representing the image data
 * @see image_t
 * @warning the image_t pointer is created on heap. make sure to free it
 */
image_t *loadPng(char *data);

/**
 * Loads a png from a utils path.
 * @param filePath - Absolute path to the utils to load
 * @return - pointer to the image_t representing the image data
 * @see image_t
 * @warning the image_t pointer is created on heap. make sure to free it
 */
image_t *loadPngFromFile(const char *filePath);

/**
 * Reads the chunk size and type from the first 8 bytes of the chunk
 * @param chunkInfo - pointer to the start of the chunk
 * @param size - pointer to the variable that will contain the size of the chunk in bytes
 * @param type - pointer to the variable that will contain the chunk type
 * @note - PNG uses big endian. getChunkInfo will byte swap the size variable to little endian.
 * @note - Type will be null terminated.
 */
void getChunkInfo(const char *chunkInfo, u_int32_t *size, char *type);

/**
 * Reads the IHDR chunk data and places it in the image_t struct
 * @param data - Pointer to the start of the IHDR header (immediately after the signature)
 * @param image - Pointer to the image_t struct where data is written into
 * @note a valid png has the IHDR immediately after the signature at byte 8
 */
void parseIHDR(char *data, image_t *image);

#endif //GAME_LOADPNG_H
