#ifndef MODEL
#define MODEL
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

std::vector<Point> getPoints(Model);

void setColor(Model m, float,float,float);

void getColor(Model m, float &, float &, float &);

void addPoint(Model, Point);

std::vector<Point> readFromFile(std::string);

void writeToFile(std::vector<Point>, string);

#endif //MODEL 
