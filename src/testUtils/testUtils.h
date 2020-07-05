/**
 * @author nsix
 * @file testUtils.h
 * @brief Mini home-grown testing framework
 */

#ifndef RACING_GAME_TESTUTILS_H
#define RACING_GAME_TESTUTILS_H

#include <stdio.h>
#include <string.h>

/** bump this up if you need more than 100 tests in one test suite */
#define MAX_TEST_FUNCTIONS 100

/** number of tests */
unsigned int testCount = 0;
/** number of failed tests */
unsigned int failCount = 0;
/** number of asserts */
unsigned int assertCount = 0;
/** name of test suite being run */
char suiteName[100];
/** setup funciton to run before each test */
void (*setupFun)();
/** teardown function to run after each test */
void (*tearDownFun)();
/** test function array */
void (*testHolder[MAX_TEST_FUNCTIONS])();

/**
 * @function initSuite
 * @brief sets up the testing suite name, setup functions, teardown functions
 * @param name - name of test suite
 * @param setup -
 */
void initSuite(char *name, void (*setup)(), void (*teardown)()) {
    strcpy(suiteName, name);
    setupFun = setup;
    tearDownFun = teardown;
}

/**
 * @function assert
 * @brief Used to evaluate a condition. Records the result.
 * @param testDescription - A description of the test so you can find it if it fails
 * @param logicalStatement - logical statement that should evaluate to true if the test passed
 */
void assert(char *testDescription, int logicalStatement) {
    assertCount++;
    if (!logicalStatement) {
        printf("%s: FAIL\n", testDescription);
        failCount++;
    }
}

/**
 * @function printResults
 * @brief prints the test results for the current suite
 */
void printResults() {
    printf("\n%s Results\n", suiteName);
    printf("# of Passed Asserts:\t%d\n", assertCount - failCount);
    printf("# of Failed Asserts:\t%d\n", failCount);
    printf("# of Tests:\t%d\n", testCount);
}

/**
 * @function addTest
 * @brief adds a test to the testing suite
 * @param testFun - a void function that will be executed. Function should have no arguments or returns.
 */
void addTest(void (*testFun)()) {
    if (testCount < MAX_TEST_FUNCTIONS) {
        testHolder[testCount] = testFun;
        testCount++;
    } else {
        printf("Error: Too man test functions. Increase MAX_TEST_FUNCTIONS.\n");
    }
}

/**
 * @function runTests
 * @brief Executes each test. setup and teardown are run before and after each test respectively. prints the results
 */
void runTests() {
    printf("Starting %s test suite\n", suiteName);
    for (int i = 0; i < testCount; ++i) {
        setupFun();
        (*testHolder[i])();
        tearDownFun();
    }
    printResults();
}

#endif //RACING_GAME_TESTUTILS_H
