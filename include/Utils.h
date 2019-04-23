#pragma once
#include "main.h"

ssize_t WriteToFile(const char* filename, const char* text);

uint64_t GetMonotonicTimeInNanos();

float Random();

int RandomInt(int min, int max);

