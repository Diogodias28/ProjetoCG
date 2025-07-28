#include "Model.hpp"

struct model{
    std::vector<Point> points;
    float colorR, colorG, colorB;
};

Model createModel(){
    Model m = new model();
    if(!m){
        std::cerr << "Failed to allocate memory for model" << std::endl;
        exit(1);
    }

    m->points = std::vector<Point>();
    m->colorR = 1.0f;
    m->colorG = 0.6f;
    m->colorB = 0.7f;

    return m;
}

Model makeModel(std::vector<Point> points, float r, float g, float b){
    Model m = new model();
    for(int i=0; i<points.size(); i++){
        addPoint(m, points[i]);
    }

    m->colorR = r;
    m->colorG = g;
    m->colorB = b;

    return m;
}

std::vector<Point> getPoints(Model m){
    return m->points;
}

void setColor(Model m, float r, float g, float b) {
    m->colorR = r;
    m->colorG = g;
    m->colorB = b;
}

void getColor(Model m, float &r, float &g, float &b) {
    r = m->colorR;
    g = m->colorG;
    b = m->colorB;
}

void addPoint(Model m, Point p){
    if(m!=nullptr){
        m->points.push_back(p);
    } else{
        std::cerr << "Error: Model pointer is null!" << std::endl;
    }
}

std::vector<Point> readFromFile(std::string fileName) {
    std::vector<Point> points;
    std::string line;

    fileName = "../3d/" + fileName;
    std::ifstream file(fileName);

    if (file.is_open()) {
        std::getline(file, line); // Read the first line (number of points), but ignore it

        while (std::getline(file, line)) {
            std::istringstream iss(line);
            std::string xStr, yStr, zStr;

            if (std::getline(iss, xStr, ',') && 
                std::getline(iss, yStr, ',') && 
                std::getline(iss, zStr, ',')) {
                
                float x = std::stof(xStr);
                float y = std::stof(yStr);
                float z = std::stof(zStr);

                points.push_back(makePoint(x, y, z));
            }
        }
        file.close();
    } else {
        std::cerr << "Unable to open file: " << fileName << std::endl;
    }

    return points;
}

void writeToFile(std::vector<Point> controlPoints, string fileName) {
    fileName = "../3d/" + fileName;
    std::ofstream file(fileName);

    if (!file.is_open()) {
        printf("Error opening file: %s\n", fileName.c_str());
        return;
    }

    // Number of control points
    file << controlPoints.size() << std::endl;

    // Write control points
    file << std::fixed << std::setprecision(6);
    for (int i = 0; i<controlPoints.size(); i++) {
        file << getX(controlPoints[i]) << ", " << getY(controlPoints[i]) << ", " << getZ(controlPoints[i]) << std::endl;
    }

    file.close();
}
