#ifndef POINT
#define POINT
#include <stdlib.h>
#include <math.h>
#include <vector>

typedef struct point *Point;

Point createPoint();

Point makePoint(float, float, float);

float getX(Point);

void setX(Point, float);

float getY(Point);

void setY(Point, float);

float getZ(Point);

void setZ(Point, float);

Point crossProduct(Point, Point);

Point subtractPoints(Point, Point);

Point getCatmullRomPoint(float, Point, Point, Point, Point);

void buildRotMatrix(Point, Point, Point, Point, float*);

#endif // POINT