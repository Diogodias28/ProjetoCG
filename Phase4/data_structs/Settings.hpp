#ifndef SETTINGS
#define SETTINGS
#include "../TinyXML/tinyxml.h"
#include <stdlib.h>
#include "Group.hpp"
#include "Matrix.hpp"
#include "Light.hpp"

typedef struct settings* Settings;

Settings newSettings();

Settings xmlToSettings(const char*);

std::vector<std::string> getPaths(Settings);

void setCamPosition(Settings, float, float, float);

int getHeight(Settings);

int getWidth(Settings);

float getXPosCam(Settings);

float getYPosCam(Settings);

float getZPosCam(Settings);

float getXLookAt(Settings);

float getYLookAt(Settings);

float getZLookAt(Settings);

float getXUp(Settings);

float getYUp(Settings);

float getZUp(Settings);

float getFov(Settings);

float getNear(Settings);

float getFar(Settings);

bool getShowAxes(Settings);

void setShowAxes(Settings, bool);

bool getShowOrbit(Settings);

void setShowOrbit(Settings, bool);

Group getGroup(Settings);

std::vector<Light> getLight(Settings);

#endif // Settings