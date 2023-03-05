/**
 * Created by nsix on 2/20/2021.
 */

#include "testUtils.h"

void setup() {

}

void teardown() {

}

void test_loadFile() {

}

int main() {
    initSuite("glslUtils", &setup, &teardown);
    addTest(test_loadFile);
    runTests();
    return 0;
}