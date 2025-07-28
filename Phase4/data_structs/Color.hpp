#ifndef COLOR
#define COLOR

#include <stdlib.h>

struct RGB {
    float r, g, b;
};

typedef struct color* Color;

Color createDefaultColor();

Color makeColor (RGB, RGB, RGB, RGB, float);

RGB createRGB(int, int, int);

float normalizeColor (int);

RGB getDiffuse (Color);

void setDiffuse (Color, RGB );

RGB getAmbient (Color);

void setAmbient (Color, RGB );

RGB getSpecular (Color );

void setSpecular (Color, RGB);

RGB getEmissive (Color);

void setEmissive (Color, RGB); 

float getShininess(Color);

void setShininess (Color, float );


#endif