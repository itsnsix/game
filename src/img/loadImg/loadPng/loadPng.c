#include "loadPng.h"

int verifyPngSignature(const char *pngHeader) {
    const char validPngSignature[8] = "\x89PNG\r\n\x1a\n";
    return !memcmp(pngHeader, validPngSignature, 8);
}

image_t *loadPng(char *data) {
    image_t *image = (image_t *) malloc(sizeof (image_t));

    // check that the png is valid
    if (!verifyPngSignature(data)) {
        printf("Error: Invalid PNG signature\n");
        image = NULL;
        return image;
    }

    strcpy(image->imageType, "png");

    parseIHDR(data + 8, image);

    return image;
}

image_t *loadPngFromFile(const char *filePath) {
    char *fileContents = loadFile(filePath);
    image_t * image = loadPng(fileContents);
    free(fileContents);
    return image;
}

void getChunkInfo(const char *chunkInfo, u_int32_t *size, char *type) {
    memcpy(size, chunkInfo, 4);
    // byte swap for little endianness
    byteSwap((char *) size, 4);
    memcpy(type, chunkInfo + 4, 4);
    // null terminate
    type[4] = '\0';
}

void parseIHDR(char *data, image_t *image) {
    u_int32_t size;
    char type[5];
    getChunkInfo(data, &size, type);

    // first chunk should be 13 bytes type IHDR
    if (size != 13 || !strcmp(type, "IHDR")) {
        printf("Error: Invalid IHDR.\n");
        printf("Size: %u\nType: %s", size, type);
        image = NULL;
        return;
    }

    // width
    data += 8;
    memcpy(&image->width, data, 4);
    byteSwap((char *) &image->width, 4);
    // height
    data += 4;
    memcpy(&image->height, data, 4);
    byteSwap((char *) &image->height, 4);
    // bit depth
    memcpy(&image->bitDepth, ++data, 1);
    // color type
    memcpy(&image->colorType, ++data, 1);
    // compression method
    memcpy(&image->compressionMethod, ++data, 1);
    // filter method
    memcpy(&image->filterMethod, ++data, 1);
    // interlace method
    memcpy(&image->interlaceMethod, ++data, 1);
}