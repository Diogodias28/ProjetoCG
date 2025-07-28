#include "Color.hpp"

struct color{
    RGB diffuse;
    RGB ambient;
    RGB specular;
    RGB emissive;
    float shininess;
};

Color createDefaultColor() {
    RGB diffuse = createRGB(200,200,200);
    RGB ambient = createRGB(50,50,50);
    RGB specular = createRGB(0,0,0);
    RGB emissive = createRGB(0,0,0);
    float shininess = 0.0f;

    return makeColor(diffuse, ambient, specular, emissive, shininess); 
}

Color makeColor (RGB diffuse, RGB ambient, RGB specular, RGB emissive, float shininess) {
    Color c = new color();

    if (c != NULL) {
        c->diffuse = diffuse;
        c->ambient = ambient;
        c->specular = specular;
        c->emissive = emissive;
        c->shininess = shininess;
    }

    return c;
}

RGB createRGB(int r, int g, int b) {
    return {
        normalizeColor(r),
        normalizeColor(g),
        normalizeColor(b)
    };
}

float normalizeColor (int value) {
    return value/ 255.0f;
}

RGB getDiffuse (Color c) {
    return c->diffuse;
}

void setDiffuse (Color c, RGB diffuse) {
    c->diffuse = diffuse;
}

RGB getAmbient (Color c) {
    return c->ambient;
}

void setAmbient (Color c, RGB ambient) {
    c->ambient = ambient;
}

RGB getSpecular (Color c) {
    return c->specular;
}

void setSpecular (Color c, RGB specular) {
    c->specular = specular;
}

RGB getEmissive (Color c) {
    return c->emissive;
}

void setEmissive (Color c, RGB emissive) {
    c->emissive = emissive;
}

float getShininess(Color c) {
    return c->shininess;
}

void setShininess (Color c, float shininess) {
    c->shininess = shininess;
}