#include "Model.hpp"

struct model{
    //std::vector<Point> points;
    Color color;
    std::string textureFile;
    float* vertexB;
    float* normals;
    float* texCoords;
    GLuint vertexCount;
    GLuint buffer[3];
    bool buffersInitialized; // Track estado OpenGL
};

Model createModel(){
    Model m = new model();
    if(!m){
        std::cerr << "Failed to allocate memory for model" << std::endl;
        exit(1);
    }

    //m->points = std::vector<Point>();
    m->color = createDefaultColor();
    m->textureFile = nullptr;
    m->vertexB = nullptr;
    m->vertexCount = 0;
    m->vertexB = nullptr;
    m->normals = nullptr;
    m->texCoords = nullptr;
    m->buffersInitialized = false;

    return m;
}

Model makeModel(std::vector<Point> points, std::vector<Point> normals, std::vector<Point> texCoords, Color color, std::string textureFile){
    Model m = new model();

    m->vertexB = (float *)malloc(points.size() * 3 * sizeof(float));
    m->normals = (float *)malloc(points.size() * 3 * sizeof(float));
	m->texCoords = (float *)malloc(points.size() * 2 * sizeof(float));

    for(int i=0; i<points.size(); i++){
        m->vertexB[i*3 + 0] = getX(points[i]);
		m->vertexB[i*3 + 1] = getY(points[i]);
		m->vertexB[i*3 + 2] = getZ(points[i]);
    }

    for(int i=0; i<normals.size(); i++){
        m->normals[i*3 + 0] = getX(normals[i]);
		m->normals[i*3 + 1] = getY(normals[i]);
		m->normals[i*3 + 2] = getZ(normals[i]);
    }

    for(int i=0; i<texCoords.size(); i++){
        m->texCoords[i*2 + 0] = getX(texCoords[i]);
		m->texCoords[i*2 + 1] = getY(texCoords[i]);
    }

    m->vertexCount = points.size();

    m->color = color;
    if(!textureFile.empty()){
        m->textureFile = textureFile;
    }else {
        m->textureFile = "";
    }

    return m;
}


void initModelBuffers(Model m) {
    if (!m->buffersInitialized && m->vertexB) {
        glGenBuffers(3, m->buffer);
        glBindBuffer(GL_ARRAY_BUFFER, m->buffer[0]);
        glBufferData(GL_ARRAY_BUFFER, 
                    sizeof(float) * m->vertexCount * 3,
                    m->vertexB, 
                    GL_STATIC_DRAW);
                    
        glBindBuffer(GL_ARRAY_BUFFER, m->buffer[1]);
        glBufferData(GL_ARRAY_BUFFER, 
                    sizeof(float) * m->vertexCount * 3, //trocar vertexCount por outra coisa?
                    m->normals,
                    GL_STATIC_DRAW);

        glBindBuffer(GL_ARRAY_BUFFER, m->buffer[2]);
        glBufferData(GL_ARRAY_BUFFER,
                    sizeof(float) * m->vertexCount * 2, //trocar vertexCount por outra coisa?
                    m->texCoords,
                    GL_STATIC_DRAW);
        
        // Free CPU memory after uploading to GPU
        free(m->vertexB);
        free(m->normals);
        free(m->texCoords);

        m->vertexB = nullptr;
        
        m->buffersInitialized = true;
    }
}

void setColor(Model m, Color c) {
    m->color = c;
}

Color getColor(Model m) {
    return(m->color);
}

float* normals(Model m){
    return m->normals;
}

float* texCoords(Model m){
    return m->texCoords;
}

float* getVertexB(Model m){
    return m->vertexB;
}

GLuint getVertexCount(Model m){
    return m->vertexCount;
}

GLuint getBuffer_0(Model m){
    return m->buffer[0];
}

GLuint getBuffer_1(Model m){
    return m->buffer[1];
}

GLuint getBuffer_2(Model m){
    return m->buffer[2];
}

std::string getTextureFile(Model m){
    return m->textureFile;
}

std::vector<std::vector<Point>> readFromFile(std::string fileName) {
    std::vector<Point> points, normals, texCoords;
    std::string line;

    fileName = "../3d/" + fileName;
    std::ifstream file(fileName);

    if (file.is_open()) {
        std::getline(file, line); // Lê o número de pontos (ignora-os)

        while (std::getline(file, line)) {
            std::istringstream iss(line);
            std::string xCPstr, yCPstr, zCPstr, xNstr, yNstr, zNstr, xTCstr, yTCstr;

            if (std::getline(iss, xCPstr, ',') && 
                std::getline(iss, yCPstr, ',') && 
                std::getline(iss, zCPstr, ';') &&
                std::getline(iss, xNstr, ',') && 
                std::getline(iss, yNstr, ',') && 
                std::getline(iss, zNstr, ';') &&
                std::getline(iss, xTCstr, ',') && 
                std::getline(iss, yTCstr)){
                
                float xP = std::stof(xCPstr);
                float yP = std::stof(yCPstr);
                float zP = std::stof(zCPstr);
                points.push_back(makePoint(xP, yP, zP));

                float xN = std::stof(xNstr);
                float yN = std::stof(yNstr);
                float zN = std::stof(zNstr);
                normals.push_back(makePoint(xN, yN, zN));

                float xT = std::stof(xTCstr);
                float yT = std::stof(yTCstr);
                texCoords.push_back(makeTexturePoint(xT, yT));
            }
        }
        file.close();
    } else {
        printf("Error opening file: %s\n", fileName.c_str());
    }

    std::vector<std::vector<Point>> res;
    res.push_back(points);
    res.push_back(normals);
    res.push_back(texCoords);


    return res;
}

void writeToFile(std::vector<Point> controlPoints, std::vector<Point> normals, std::vector<Point> texCoords, string fileName) {
    fileName = "../3d/" + fileName;
    std::ofstream file(fileName);

    if (!file.is_open()) {
        printf("Error opening file: %s\n", fileName.c_str());
        return;
    }

    // Número de pontos de controlo
    file << controlPoints.size() << std::endl;

    // Escreve os pontos de controlo no formato "x, y, z"
    file << std::fixed << std::setprecision(6);
    for (int i = 0; i<controlPoints.size(); i++) {
        file << getX(controlPoints[i]) << ", " << getY(controlPoints[i]) << ", " << getZ(controlPoints[i]) << ";" << getX(normals[i]) << ", " << getY(normals[i]) << ", " << getZ(normals[i]) << ";" << getX(texCoords[i]) << ", " << getY(texCoords[i]) << std::endl;
    }

    file.close();
}

int loadTexture(Model m) {
    if (m == nullptr || m->textureFile.empty()) return 0;

    unsigned int t, tw, th;
    unsigned char *texData;
    unsigned int texID;

    std::string fullPath = "../textures/" + m->textureFile;

    ilGenImages(1, &t);
    ilBindImage(t);

    if (ilLoadImage((ILstring)fullPath.c_str()) == IL_FALSE) {
        std::cerr << "ERROR: Failed to load texture: " << fullPath << std::endl;
        ILenum error = ilGetError();
        std::cerr << "DevIL error: " << std::endl;
        ilDeleteImages(1, &t);
        return 0;
    }

    tw = ilGetInteger(IL_IMAGE_WIDTH);
    th = ilGetInteger(IL_IMAGE_HEIGHT);
    ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE);
    texData = ilGetData();

    if (!texData) {
        std::cerr << "ERROR: Failed to load texture: " << m->textureFile << std::endl;
        return 0;
    }

    glGenTextures(1, &texID);
    glBindTexture(GL_TEXTURE_2D, texID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);


    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, tw, th, 0, GL_RGBA, GL_UNSIGNED_BYTE, texData);
    glGenerateMipmap(GL_TEXTURE_2D);

    ilDeleteImages(1, &t);

    return texID;
}