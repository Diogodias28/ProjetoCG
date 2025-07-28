#ifndef TRANSFORM
#define TRANSFORM
#include <vector>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include "Point.hpp"


using namespace std;

typedef struct transform* Transform;

Transform newTransformation(char, Point, float);

char getType(Transform);

Point getTransVal(Transform);

float getAngle(Transform);

#endif //TRANSFORM