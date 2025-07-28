#ifndef MODEL
#define MODEL

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
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

using namespace std;

typedef struct model* Model;

Model createModel();

Model makeModel(std::vector<Point>,float , float ,float);

//std::vector<Point> getPoints(Model);

void setColor(Model, float,float,float);

void getColor(Model, float &, float &, float &);

float* getVertexB(Model);

GLuint getVertexCount(Model);

GLuint getBuffer_0(Model);

GLuint getBuffer_1(Model);

void initModelBuffers(Model);

//void addPoint(Model, Point);

std::vector<Point> readFromFile(std::string);

void writeToFile(std::vector<Point>, string);

#endif //MODEL 
