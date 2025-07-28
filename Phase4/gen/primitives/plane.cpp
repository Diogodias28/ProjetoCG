#include "plane.hpp"

void genPlane(int length, int divisions, std::string fileName){
    std::vector<Point> controlPoints;
    std::vector<Point> normals;
    std::vector<Point> texCoords;
    float part = (float)length / divisions;
    float half = length / 2.0f;

    for (int i = 0; i < divisions; i++) {
        for (int j = 0; j < divisions; j++) {
            float x1 = -half + i * part;
            float z1 = -half + j * part;
            float x2 = x1 + part;
            float z2 = z1 + part;
            float tx1 = (x1 + half) / length;
            float tz1 = (z1 + half) / length;
            float tx2 = (x2 + half) / length;
            float tz2 = (z2 + half) / length;


            // Triângulo 1 (parte de cima)
            controlPoints.push_back(makePoint(x1, 0.0f, z1));
            controlPoints.push_back(makePoint(x1, 0.0f, z2));
            controlPoints.push_back(makePoint(x2, 0.0f, z1));

            texCoords.push_back(makeTexturePoint(tx1, tz1));
            texCoords.push_back(makeTexturePoint(tx1, tz2));
            texCoords.push_back(makeTexturePoint(tx2, tz1));

            // Triângulo 2 (parte de cima)
            controlPoints.push_back(makePoint(x2, 0.0f, z1));
            controlPoints.push_back(makePoint(x1, 0.0f, z2));
            controlPoints.push_back(makePoint(x2, 0.0f, z2));

            texCoords.push_back(makeTexturePoint(tx2, tz1));
            texCoords.push_back(makeTexturePoint(tx1, tz2));
            texCoords.push_back(makeTexturePoint(tx2, tz2));

            for(int k = 0; k < 6; k++){
                normals.push_back(makePoint(0.0f, 1.0f, 0.0f));
            }

            // Triângulo 1 (parte de baixo - invertido)
            controlPoints.push_back(makePoint(x1, 0.0f, z1));
            controlPoints.push_back(makePoint(x2, 0.0f, z1));
            controlPoints.push_back(makePoint(x1, 0.0f, z2));

            texCoords.push_back(makeTexturePoint(tx1, tz1));
            texCoords.push_back(makeTexturePoint(tx2, tz1));
            texCoords.push_back(makeTexturePoint(tx1, tz2));

            // Triângulo 2 (parte de baixo - invertido)
            controlPoints.push_back(makePoint(x2, 0.0f, z1));
            controlPoints.push_back(makePoint(x2, 0.0f, z2));
            controlPoints.push_back(makePoint(x1, 0.0f, z2));

            texCoords.push_back(makeTexturePoint(tx2, tz1));
            texCoords.push_back(makeTexturePoint(tx2, tz2));
            texCoords.push_back(makeTexturePoint(tx1, tz2));
            
            for(int k = 0; k < 6; k++){
                normals.push_back(makePoint(0.0f, -1.0f, 0.0f));
            }
        }
    }

    writeToFile(controlPoints, normals, texCoords, fileName);
}