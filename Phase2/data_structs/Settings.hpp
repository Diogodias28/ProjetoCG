#ifndef SETTINGS
#define SETTINGS
#include "../TinyXML/tinyxml.h"
#include <stdlib.h>
#include "Group.hpp"

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

Group getGroup(Settings);

#endif // Settings