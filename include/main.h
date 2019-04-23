#pragma once
#include <iostream>
#include <assert.h>
#include <stdlib.h>
#include <unistd.h>
#include <vector>
#include <string.h>
#include <math.h>
#include <functional>

#define TERM_CLS     "\033[2J"
#define TERM_00      "\033[0;0H"
#define RED_TEXT     "\033[31;1m"
#define GREEN_TEXT   "\033[32;1m"
#define YELLOW_TEXT  "\033[33;1m"
#define BLUE_TEXT    "\033[34;1m"
#define PURPLE_TEXT  "\033[35;1m"
#define DEFAULT_TEXT "\033[0m"

#include "Test.h"
#include "ObjectPool.h"
#include "Utils.h"

int ExecuteCpp(const char* text);

#include "ObjectPool.inl"

using std::cout;

