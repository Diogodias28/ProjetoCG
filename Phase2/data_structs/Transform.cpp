#include "Transform.hpp"

struct transform{
    char type; //T translation, S scale, R rotation
    Point transformation;
    float angle; 
};

Transform newTransformation(char type, Point transformation, float angle){
    Transform t = (Transform)malloc(sizeof(struct transform));

    t->type = type;
    t->transformation = transformation;
    t->angle = angle;
    
    return t;
}

char getType(Transform t){
    return t->type;
};

Point getTransVal(Transform t){
    return t->transformation;
};

float getAngle(Transform t){
    return t->angle;
};