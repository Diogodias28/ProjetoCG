#include "Point.hpp"

struct point {
    float x, y, z;
};

Point createPoint() {
    return makePoint(0.0f, 0.0f, 0.0f);
}

Point makePoint(float x, float y, float z){
    Point p = new point();

    if (p != NULL) {
        p->x = x;
        p->y = y;
        p->z = z;
    }

    return p;
}

void deletePoint(Point p) {
    if (p) {
        delete p;
    }
}

Point createTexturePoint() {
    return makeTexturePoint(0.0f, 0.0f);
}

Point makeTexturePoint(float x, float y){
    Point p = new point();

    if (p != NULL) {
        p->x = x;
        p->y = y;
    }

    return p;
}

float getX(Point p){
    return p->x;
}

void setX(Point p, float xS){
    p->x = xS;
}

float getY(Point p){
    return p->y;
}

void setY(Point p, float yS){
    p->y = yS;
}

float getZ(Point p){
    return p->z;
}

void setZ(Point p, float zS){
    p->z = zS;
}

Point crossProduct(Point a, Point b) {
    float x = getY(a) * getZ(b) - getZ(a) * getY(b);
    float y = getZ(a) * getX(b) - getX(a) * getZ(b);
    float z = getX(a) * getY(b) - getY(a) * getX(b);

    return makePoint(x, y, z);
}

Point subtractPoints(Point a, Point b) {
    return makePoint(getX(a)-getX(b), getY(a)-getY(b), getZ(a)-getZ(b));
}

Point getCatmullRomPoint(float t, Point p0, Point p1, Point p2, Point p3) {
    float t2 = t * t;
    float t3 = t2 * t;
    
    return makePoint(
        0.5f * ((2*getX(p1)) + (-getX(p0)+getX(p2))*t +
                (2*getX(p0)-5*getX(p1)+4*getX(p2)-getX(p3))*t2 +
                (-getX(p0)+3*getX(p1)-3*getX(p2)+getX(p3))*t3),
        
        0.5f * ((2*getY(p1)) + (-getY(p0)+getY(p2))*t +
                (2*getY(p0)-5*getY(p1)+4*getY(p2)-getY(p3))*t2 +
                (-getY(p0)+3*getY(p1)-3*getY(p2)+getY(p3))*t3),
        
        0.5f * ((2*getZ(p1)) + (-getZ(p0)+getZ(p2))*t +
                (2*getZ(p0)-5*getZ(p1)+4*getZ(p2)-getZ(p3))*t2 +
                (-getZ(p0)+3*getZ(p1)-3*getZ(p2)+getZ(p3))*t3)
    );
}

void buildRotMatrix(Point x, Point y, Point z, Point w, float *m) {
    m[0] = getX(x); m[4] = getX(y); m[8]  = getX(z); m[12] = getX(w);
    m[1] = getY(x); m[5] = getY(y); m[9]  = getY(z); m[13] = getY(w);
    m[2] = getZ(x); m[6] = getZ(y); m[10] = getZ(z); m[14] = getZ(w);
    m[3] = 0;       m[7] = 0;       m[11] = 0;       m[15] = 1;
} 

Point normalize(Point p) {
    float x = getX(p);
    float y = getY(p);
    float z = getZ(p);
    float length = std::sqrt(x * x + y * y + z * z);
    if (length != 0.0f) {
        x /= length;
        y /= length;
        z /= length;
    }
    
    return makePoint(x, y, z);
}