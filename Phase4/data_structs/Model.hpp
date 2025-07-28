#ifndef MODEL
#define MODEL

#ifdef __APPLE__
#include <GLUT/glut.h>
#include </opt/homebrew/include/IL/il.h>
#else
#include <GL/glut.h>
#include <IL/il.h>
#endif

#include <vector>
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <fcntl.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <iomanip>
#include "Transform.hpp"
#include "Color.hpp"

using namespace std;

typedef struct model* Model;

Model createModel();

Model makeModel(std::vector<Point>, std::vector<Point>, std::vector<Point>,Color, std::string);

//std::vector<Point> getPoints(Model);

void setColor(Model, Color);

Color getColor(Model);

float* getVertexB(Model);

float* normals(Model);

float* texCoords(Model);

GLuint getVertexCount(Model);

GLuint getBuffer_0(Model);

GLuint getBuffer_1(Model);

GLuint getBuffer_2(Model);

std::string getTextureFile(Model);

void initModelBuffers(Model);

//void addPoint(Model, Point);

std::vector<std::vector<Point>> readFromFile(std::string);

void writeToFile(std::vector<Point>, std::vector<Point>, std::vector<Point>, string);

int loadTexture(Model);

#endif //MODEL 
