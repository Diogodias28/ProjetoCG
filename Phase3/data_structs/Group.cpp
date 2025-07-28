#include "Group.hpp"

struct group{
    std::vector<Model> models;
    std::vector<Transform> transformations;
    std::vector<Group> subgroups;
};

Group createGroup(){ //cria grupo vazio
    Group g = new group();

    g->models = std::vector<Model>();
    g->transformations = std::vector<Transform>();
    g->subgroups = std::vector<Group>();

    return g;
}

Group makeGroup(std::vector<Model> models, std::vector<Transform> transformations, std::vector<Group> subgroups){
    Group g = createGroup();

    g->models = models;
    g->transformations = transformations;
    g->subgroups = subgroups;

    return g;
}

std::vector<Model> getModels(Group g){
    return g->models;
};

std::vector<Transform> getTransformations(Group g){
    return g->transformations;
};

std::vector<Group> getSubgroup(Group g){
    return g->subgroups;
};

void initGroupBuffers(Group g) {
    std::vector<Model> models = getModels(g);
    for (Model &model : models) {
        initModelBuffers(model);
    }

    std::vector<Group> subgroups = getSubgroup(g);
    for (Group &subgroup : subgroups) {
        initGroupBuffers(subgroup);
    }
}