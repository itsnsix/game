
#include "testUtils.h"
#include "loadPng.h"

void setup() {

}

void teardown() {

}

void test_verifyPngSignature() {
    const char validPngSignature[8] = "\x89PNG\r\n\x1a\n";
    const char invalidPngSignature[8] = "\x89JPG\r\n\x1a\n";
    assert("Returns 1 for valid signatures", verifyPngSignature(validPngSignature) == 1);
    assert("Returns 0 for invalid signatures", verifyPngSignature(invalidPngSignature) == 0);
}

void test_getChunkInfo() {
    const char chunkInfo[8] = "\0\0\0\x0DIHDR";
    u_int32_t size;
    char type[5];
    getChunkInfo(chunkInfo, &size, type);
    assert("Returns the correct size", size == 13);
    assert("Returns correct header type", strcmp(type, "IHDR") == 0);
}

int main() {
    initSuite("loadPng", &setup, &teardown);
    addTest(test_verifyPngSignature);
    addTest(test_getChunkInfo);
    runTests();
    return 0;
}