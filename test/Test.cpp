#include "main.h"

TEST(Test, Comparisons){
    ASSERT_EQ(1, 1);
    ASSERT_GT(2, 1);
    ASSERT_LT(1, 2);
    ASSERT_GTE(2, 1);
    ASSERT_GTE(1, 1);
    ASSERT_LTE(1, 2);
    ASSERT_LTE(1, 1);
}

#define cppHead \
    "#include <stdio.h>\n" \

#define cppStart \
    "extern \"C\"\n" \
    "int rrr(){" \
    
#define cppEnd \
    "}" \

TEST(CppExecution, Basic){
    int r;

    r = ExecuteCpp(cppHead cppStart "return 0;" cppEnd);
    ASSERT_EQ(r, 0);
    r = ExecuteCpp(cppHead cppStart "return 1;" cppEnd);
    ASSERT_EQ(r, 1);

    r = ExecuteCpp(cppHead "int RandomInt(int, int);\n" cppStart "return RandomInt(42,42);" cppEnd);
    ASSERT_EQ(r, 42);
}

