#include "Light.hpp"

struct light{
    char type; // P = point, D = directional, S = spot, N = null
    Point positions;
    std::vector<float> directions;
    float cutoff;
};

Light makeLight(char type, Point positions, std::vector<float> direction, float cutoff) {
    Light l = new light();

    if (l != NULL) {
        l->type = type;
        l->positions = positions;
        l->directions = direction;
        l->cutoff = cutoff;
    }

    return l;
}

Light createLight() {
    std::vector<float> nullVector = {0.0f,0.0f,0.0f};
    return makeLight ('N', createPoint(), nullVector, 0.0f);
}

char getType(Light l) {
    return l->type;
}

Point getPositions(Light l) {
    return l->positions;
}

std::vector<float> getDirections(Light l) {
    return l->directions;
}

float getCutoff(Light l) {
    return l->cutoff;
}