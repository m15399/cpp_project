#include "main.h"

int main(int argc, char** argv){

    bool success = RunAllTestCases();
    if (!success)
        return 1;

    return 0;
}

