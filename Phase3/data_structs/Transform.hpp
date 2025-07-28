#ifndef TRANSFORM
#define TRANSFORM

#include "Point.hpp"
#include <vector>
#include <stdlib.h>

typedef struct transform* Transform;

Transform newTransformation(char type, Point transformation, float angle, float time = 0, std::vector<Point> points = {}, bool align = false);

char getType(Transform t);

Point getTransVal(Transform t);

float getAngle(Transform t);

float getTime(Transform t);

bool getAlign(Transform t);

std::vector<Point> getPoints(Transform t);

#endif