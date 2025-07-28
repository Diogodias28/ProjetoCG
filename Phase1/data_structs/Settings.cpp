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
    std::vector<std::string> models; // lista com as paths dos ficheiros dos modelos
};

Settings newSettings(){
    Settings newSettings = (Settings)malloc(sizeof(struct settings));
    newSettings->models = std::vector<std::string>();
    if(!newSettings->models.empty()){ // não foi possível criar a lista
        newSettings->models.clear();
    }
    return newSettings;
}

Settings xmlToSettings(const char* filePath){
    Settings result = newSettings();
    if(result != NULL){
        TiXmlDocument doc;
        if(doc.LoadFile(filePath)){
            TiXmlElement* root = doc.FirstChildElement("world"); // todo o conteúdo do ficheiro
            // Obtenção dos dados da câmara
            TiXmlElement* window = root->FirstChildElement("window"); // parâmetros da janela
            TiXmlElement* camera = root->FirstChildElement("camera"); // parâmetros da cầmara
            TiXmlElement* posCamera = camera->FirstChildElement("position"); // posição da câmara
            TiXmlElement* lookAtCamera = camera->FirstChildElement("lookAt"); // lookAt da câmara
            TiXmlElement* upCamera = camera->FirstChildElement("up"); // vetor "up" da câmara
            TiXmlElement* projectionCamera = camera->FirstChildElement("projection"); // projections
            result->window[0] = atoi(window->Attribute("width")); //largura da janela
            result->window[1] = atoi(window->Attribute("height")); //altura da janela
            result->poscam[0] = atof(posCamera->Attribute("x")); // coordenada x da posição da câmara
            result->poscam[1] = atof(posCamera->Attribute("y")); // coordenada y da posição da câmara
            result->poscam[2] = atof(posCamera->Attribute("z")); // coordenada z da posição da câmara
            result->lookAt[0] = atof(lookAtCamera->Attribute("x")); // coordenada x da posição lookAt da câmara
            result->lookAt[1] = atof(lookAtCamera->Attribute("y")); // coordenada y da posição lookAt da câmara
            result->lookAt[2] = atof(lookAtCamera->Attribute("z")); // coordenada z da posição lookAt da câmara
            result->up[0] = atof(upCamera->Attribute("x")); // coordenada x do vetor "up" da câmara
            result->up[1] = atof(upCamera->Attribute("y")); // coordenada y do vetor "up" da câmara
            result->up[2] = atof(upCamera->Attribute("z")); // coordenada z do vetor "up" da câmara
            result->projection[0] = atof(projectionCamera->Attribute("fov")); // parâmetro fov do xml de setiguração
            result->projection[1] = atof(projectionCamera->Attribute("near")); // parâmetro near do xml de setiguração
            result->projection[2] = atof(projectionCamera->Attribute("far")); // parâmetro far do xml de setiguração
            
            TiXmlElement* group = root->FirstChildElement("group"); // obtenção do group do ficheiro de setiguração
            TiXmlElement* models = group->FirstChildElement("models"); // obtenção dos ficheiros dos modelos
            for(TiXmlElement* model = models->FirstChildElement("model"); model; model = model->NextSiblingElement("model")){
                result->models.push_back(model->Attribute("file")); // adicionar o ficheiro do modelo à lista
            }
        } else{
            printf("Error: Could not load XML file %s\n", filePath);
            return NULL;
        }
    }
    return result;
}

std::vector<std::string> getPaths(Settings set){
    return set->models;
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

void deleteSettings(Settings set){
    if(set != NULL){
        if(!set->models.empty()){
            set->models.clear();
        }
        delete set;
    }
}