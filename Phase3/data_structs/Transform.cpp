#include "Transform.hpp"

struct transform{
    char type; // T=translation, S=scale, R=rotation
    Point transformation;
    float angle;
    float time;
    bool align;
    std::vector<Point> points;
};

Transform newTransformation(char type, Point transformation, float angle, float time, std::vector<Point> points, bool align) {
    Transform t = (Transform)malloc(sizeof(struct transform));
    t->type = type;
    t->transformation = transformation;
    t->angle = angle;
    t->time = time;
    t->points = points;
    t->align = align;
    return t;
}

char getType(Transform t) { 
    return t->type; 
}

Point getTransVal(Transform t) { 
    return t->transformation; 
}

float getAngle(Transform t) { 
    return t->angle; 
}

float getTime(Transform t) { 
    return t->time; 
}

bool getAlign(Transform t) { 
    return t->align; 
}

std::vector<Point> getPoints(Transform t) { 
    return t->points; 
}