#pragma once
#include "main.h"

#define TEST_FUNC_NAME(module, name) \
    testCaseFunc_##module##_##name

// Define a new test.
// 
// Usage:
//   TEST(ModuleName, TestName) {
//     ...
//   }
//
#define TEST(module, name) \
    void TEST_FUNC_NAME(module, name)(); \
    TestCase testCaseObject_##module##_##name( \
        #module "_" #name, \
        TEST_FUNC_NAME(module, name)); \
    void TEST_FUNC_NAME(module, name)()

// Fail the current test.
//
#define FAIL_TEST() \
    FailTestCase(); \
    return

#define PRINT_FAIL_CHECK() \
    printf("%s:%d " RED_TEXT "Check failed:\n" DEFAULT_TEXT, __FILE__, __LINE__);

// Check condition 'e' is true.
//
#define ASSERT_TRUE(e) \
    if (!(e)) { \
        PRINT_FAIL_CHECK(); \
        printf("  %s\n", #e); \
        FAIL_TEST(); \
    }

#define ASSERT_CMP(a, cmp, b) \
    if (!((a) cmp (b))) { \
        PRINT_FAIL_CHECK(); \
        printf("  %s " #cmp " %s\n", #a, #b); \
        std::cout << "    Expected " << (a) << "\n"; \
        std::cout << "    To be " #cmp " " << (b) << "\n"; \
        FAIL_TEST(); \
    }

#define ASSERT_EQ(a, b) ASSERT_CMP(a, ==, b)
#define ASSERT_NE(a, b) ASSERT_CMP(a, !=, b)
#define ASSERT_GT(a, b) ASSERT_CMP(a, >, b)
#define ASSERT_GTE(a, b) ASSERT_CMP(a, >=, b)
#define ASSERT_LT(a, b) ASSERT_CMP(a, <, b)
#define ASSERT_LTE(a, b) ASSERT_CMP(a, <=, b)



bool RunAllTestCases();
void FailTestCase();

using TestFunc = void (*)(void);

struct TestCase {
    const char* m_name;
    TestFunc m_func;
    TestCase* m_next;
    TestCase* m_nextFail;

    TestCase(const char* name, TestFunc func);
    void Run();
};


