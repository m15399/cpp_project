#include "main.h"

ssize_t WriteToFile(const char* filename, const char* text){
    FILE* f = fopen(filename, "w");
    ssize_t bytesWritten = fprintf(f, "%s", text);
    fclose(f);
    return bytesWritten;
}

uint64_t GetMonotonicTimeInNanos(){
    struct timespec t;
    clock_gettime(CLOCK_MONOTONIC, &t);
    uint64_t nanos = t.tv_sec * 1000000000lu + t.tv_nsec;
    return nanos;
}

float Random(){
    float r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
    return r;
}

int RandomInt(int min, int max){
    return min + round(Random() * (max-min));
}

