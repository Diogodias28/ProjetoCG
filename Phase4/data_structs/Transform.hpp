#ifndef TRANSFORM
#define TRANSFORM

#include "Point.hpp"
#include <vector>
#include <stdlib.h>

typedef struct transform* Transform;

Transform newTransformation(char type, Point transformation, float angle, float time = 0, std::vector<Point> points = {}, bool align = false);

char getType(Transform);

Point getTransVal(Transform);

float getAngle(Transform);

float getTime(Transform);

bool getAlign(Transform);

std::vector<Point> getPoints(Transform);

#endif