#include "Settings.hpp"
#include <vector>
#include <string>

using namespace std;

struct settings{
    // Câmara
    int window[2];
    float poscam[3];
    float lookAt[3];
    float up[3];
    float projection[3]; // fov, near, far
    Group group;
};

Settings newSettings(){
    Settings newSettings = (Settings)malloc(sizeof(struct settings));
    newSettings->group = createGroup();
    return newSettings;
}

Group parseGroup(TiXmlElement* groupElement) {
    std::vector<Model> models = std::vector<Model>();
    std::vector<Transform> transformations = std::vector<Transform>();
    std::vector<Group> subgroups = std::vector<Group>();

    float currentR = 1.0f, currentG = 0.6f, currentB = 0.7f;
    
    // Parsing das transformações
    TiXmlElement* transformElement = groupElement->FirstChildElement("transform");
    if (transformElement) {
        // Processa cada transformação
        for (TiXmlElement* transType = transformElement->FirstChildElement(); 
            transType; 
            transType = transType->NextSiblingElement()) {
            
            Transform transform;
            std::string elementName = transType->Value();
            char type;
            Point point;
            float angle = 0.0f;
            
            if (elementName == "translate") {
                type = 'T';
                point = makePoint(
                    atof(transType->Attribute("x")),
                    atof(transType->Attribute("y")),
                    atof(transType->Attribute("z"))
                );
                transform = newTransformation(type, point, angle);
            }
            else if (elementName == "scale") {
                type = 'S';
                point = makePoint(
                    atof(transType->Attribute("x")),
                    atof(transType->Attribute("y")),
                    atof(transType->Attribute("z"))
                );
                transform = newTransformation(type, point, angle);
            }
            else if (elementName == "rotate") {
                type = 'R';
                point = makePoint(
                    atof(transType->Attribute("x")),
                    atof(transType->Attribute("y")),
                    atof(transType->Attribute("z"))
                );
                angle = atof(transType->Attribute("angle"));
                transform = newTransformation(type, point, angle);
            }
            
            transformations.push_back(transform);
        }
    }
    
    // Parsing dos models
    TiXmlElement* modelsElement = groupElement->FirstChildElement("models");
    if (modelsElement) {
        for (TiXmlElement* modelElement = modelsElement->FirstChildElement();
             modelElement;
             modelElement = modelElement->NextSiblingElement()){

            if (std::string(modelElement->Value()) == "color") {
                // Update cor
                currentR = atof(modelElement->Attribute("r"));
                currentG = atof(modelElement->Attribute("g"));
                currentB = atof(modelElement->Attribute("b"));
            }
            else if (std::string(modelElement->Value()) == "model") {
                const char* filename = modelElement->Attribute("file");
                std::vector<Point> points = readFromFile(filename);
                Model model = makeModel(points, currentR, currentG, currentB);
                models.push_back(model);
            }
        }
    }
    
    // Parsing dos subgrupos
    for (TiXmlElement* subgroupElement = groupElement->FirstChildElement("group");
         subgroupElement;
         subgroupElement = subgroupElement->NextSiblingElement("group")) {
        
        Group subgroup = parseGroup(subgroupElement);
        subgroups.push_back(subgroup);
    }
    
    return makeGroup(models, transformations, subgroups);
}

Settings xmlToSettings(const char* filePath){
    Settings result = newSettings();
    if(result != NULL){
        TiXmlDocument doc;
        if(doc.LoadFile(filePath)){
            TiXmlElement* root = doc.FirstChildElement("world"); // todo o conteúdo do ficheiro
            // Obtenção dos dados da câmara
            TiXmlElement* window = root->FirstChildElement("window"); // parâmetros da janela
            TiXmlElement* camera = root->FirstChildElement("camera"); // parâmetros da câmara
            TiXmlElement* posCamera = camera->FirstChildElement("position"); // posição da câmara
            TiXmlElement* lookAtCamera = camera->FirstChildElement("lookAt"); // lookAt da câmara
            TiXmlElement* upCamera = camera->FirstChildElement("up"); // up da câmara
            TiXmlElement* projectionCamera = camera->FirstChildElement("projection"); // projections
            result->window[0] = atoi(window->Attribute("width")); //largura da janela
            result->window[1] = atoi(window->Attribute("height")); //altura da janela
            result->poscam[0] = atof(posCamera->Attribute("x")); // coordenada x da posição da câmara
            result->poscam[1] = atof(posCamera->Attribute("y")); // coordenada y da posição da câmara
            result->poscam[2] = atof(posCamera->Attribute("z")); // coordenada z da posição da câmara
            result->lookAt[0] = atof(lookAtCamera->Attribute("x")); // coordenada x da posição lookAt da câmara
            result->lookAt[1] = atof(lookAtCamera->Attribute("y")); // coordenada y da posição lookAt da câmara
            result->lookAt[2] = atof(lookAtCamera->Attribute("z")); // coordenada z da posição lookAt da câmara
            result->up[0] = atof(upCamera->Attribute("x")); // coordenada x do up da câmara
            result->up[1] = atof(upCamera->Attribute("y")); // coordenada y do up da câmara
            result->up[2] = atof(upCamera->Attribute("z")); // coordenada z do up da câmara
            result->projection[0] = atof(projectionCamera->Attribute("fov")); // parâmetro fov do xml
            result->projection[1] = atof(projectionCamera->Attribute("near")); // parâmetro near do xml
            result->projection[2] = atof(projectionCamera->Attribute("far")); // parâmetro far do xml 
            
            TiXmlElement* group = root->FirstChildElement("group"); // obtenção do group do ficheiro
            if(group){
                result->group = parseGroup(group);
            }
        } else{
            printf("Error: Could not load XML file %s\n", filePath);
            return NULL;
        }
    }
    return result;
}

void setCamPosition(Settings set, float x, float y, float z){
    set->poscam[0] = x;
    set->poscam[1] = y;
    set->poscam[2] = z;
}

int getHeight(Settings set){
    return set->window[1];
}

int getWidth(Settings set){
    return set->window[0];
}

float getXPosCam(Settings set){
    return set->poscam[0];
}

float getYPosCam(Settings set){
    return set->poscam[1];
}

float getZPosCam(Settings set){
    return set->poscam[2];
}

float getXLookAt(Settings set){
    return set->lookAt[0];
}

float getYLookAt(Settings set){
    return set->lookAt[1];
}

float getZLookAt(Settings set){
    return set->lookAt[2];
}

float getXUp(Settings set){
    return set->up[0];
}

float getYUp(Settings set){
    return set->up[1];
}

float getZUp(Settings set){
    return set->up[2];
}

float getFov(Settings set){
    return set->projection[0];
}

float getNear(Settings set){
    return set->projection[1];
}

float getFar(Settings set){
    return set->projection[2];
}

Group getGroup(Settings set){
    return set->group;
}
