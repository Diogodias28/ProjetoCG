#ifndef GROUP
#define GROUP
#include <vector>
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <fcntl.h>
#include "Model.hpp"

using namespace std;

typedef struct group* Group;

Group createGroup();

Group makeGroup(std::vector<Model>, std::vector<Transform>, std::vector<Group>);

std::vector<Model> getModels(Group);

std::vector<Transform> getTransformations(Group);

std::vector<Group> getSubgroup(Group);

#endif //GROUP