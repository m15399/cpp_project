#include "main.h"

TestCase* testCaseHead = nullptr;
TestCase* testCaseTail = nullptr;

TestCase* failedTestCasesHead = nullptr;
TestCase* failedTestCasesTail = nullptr;

bool lastTestFailed = false;

TestCase::TestCase(
    const char* name,
    TestFunc func) :
    m_name(name),
    m_func(func),
    m_next(nullptr),
    m_nextFail(nullptr){

    // Insert ourself into the list of test cases.
    //
    if (testCaseHead == nullptr) {
        testCaseHead = testCaseTail = this;
    } else {
        testCaseTail->m_next = this;
        testCaseTail = this;
    }
}

void TestCase::Run(){
    lastTestFailed = false;

    // Disable tests that contain "DISABLED_" in their name.
    //
    const char disabledString[] = "DISABLED_";
    if (strstr(m_name, disabledString) != nullptr){
        return;
    }

    printf(GREEN_TEXT "[ TEST: %s ]\n" DEFAULT_TEXT, m_name);

    // Run the test.
    //
    m_func();

    if (lastTestFailed){
        printf(RED_TEXT "[ FAILED ]\n" DEFAULT_TEXT);

        // Insert ourself into the list of failed test cases.
        //
        if (failedTestCasesHead == nullptr) {
            failedTestCasesHead = failedTestCasesTail = this;
        } else {
            failedTestCasesTail->m_nextFail = this;
            failedTestCasesTail = this;
        }

    } else {
        printf(GREEN_TEXT "[ PASSED ]\n" DEFAULT_TEXT);
    }
}

bool RunAllTestCases(){
    bool success = true;
    printf(GREEN_TEXT "\n[ RUNNING TESTS ]\n\n" DEFAULT_TEXT);

    // Run all the tests!
    //
    TestCase* curr = testCaseHead;
    while(curr){
        curr->Run();
        curr = curr->m_next;
    }

    if (failedTestCasesHead == nullptr) {
        printf(GREEN_TEXT "\n[ ALL TESTS PASSED ]\n" DEFAULT_TEXT);

    } else {
        // Print the list of failed test cases.
        //
        printf(RED_TEXT "\n[ TESTS FAILED ]\n" DEFAULT_TEXT);
        TestCase* fail = failedTestCasesHead;
        while(fail) {
            printf("  %s\n", fail->m_name);
            fail = fail->m_next;
        }

        success = false;
    }

    printf("\n");

    return success;
}


void FailTestCase(){
    lastTestFailed = true;
}





