/**
 * Created by nsix on 7/5/2020.
 */

#include "testUtils.h"

void setup() {

}

void teardown() {

}

void test_createShader() {

}

void test_createShaderFromFile() {

}

void test_linkProgram() {

}

int main() {
    initSuite("glslUtils", &setup, &teardown);
    addTest(test_createShader);
    addTest(test_createShaderFromFile);
    addTest(test_linkProgram);
    runTests();
    return 0;
}