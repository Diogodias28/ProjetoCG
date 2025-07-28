#include "sphere.hpp"
    
void genSphere(float radius, int slices, int stacks, std::string fileName) {

    std::vector<Point> controlPoints;
    std::vector<Point> normals;
    std::vector<Point> texCoords;


    // divide o circulo de 360 graus em slices iguais
    float anglePerSlice = (float)(2 * M_PI) / slices;
    // divide o arco de 180 graus em stacks iguais
    float anglePerStack = (float)M_PI / stacks;

    float alpha, beta;
    Point p1, p2, p3, p4;
    Point n1, n2, n3, n4;
    Point t1, t2, t3, t4;

    for (int j = 0; j < stacks; j++) {
        // ângulo para a stack atual e seguinte
        beta = j * anglePerStack;
        float nextBeta = (j + 1) * anglePerStack;

        float texV = (float)j / stacks;
        float nextTexV = (float)(j + 1) / stacks;

        for (int i = 0; i < slices; i++) {
            // ângulo para o slice atual e seguinte
            alpha = i * anglePerSlice;
            float nextAlpha = (i + 1) * anglePerSlice;

            float texH = (float)i / slices;
            float nextTexH = (float)(i + 1) / slices;
    
            // pontos na stack atual
            p1 = makePoint(radius * sinf(beta) * sinf(alpha), radius * cosf(beta), radius * sinf(beta) * cosf(alpha));
            p2 = makePoint(radius * sinf(beta) * sinf(nextAlpha), radius * cosf(beta), radius * sinf(beta) * cosf(nextAlpha));

            n1 = normalize(p1);
            n2 = normalize(p2);

            t1 = makeTexturePoint(texH, texV);
            t2 = makeTexturePoint(nextTexH, texV); 

            // pontos na próxima stack
            p3 = makePoint(radius * sinf(nextBeta) * sinf(alpha), radius * cosf(nextBeta), radius * sinf(nextBeta) * cosf(alpha));
            p4 = makePoint(radius * sinf(nextBeta) * sinf(nextAlpha), radius * cosf(nextBeta), radius * sinf(nextBeta) * cosf(nextAlpha));

            n3 = normalize(p3);
            n4 = normalize(p4);

            t3 = makeTexturePoint(texH, nextTexV);
            t4 = makeTexturePoint(nextTexH, nextTexV); 


            // triângulo de cima
            controlPoints.push_back(p1);
            controlPoints.push_back(p4);
            controlPoints.push_back(p2);

            normals.push_back(n1);
            normals.push_back(n4);
            normals.push_back(n2);

            texCoords.push_back(t1);
            texCoords.push_back(t4);
            texCoords.push_back(t2);

            // triângulo de baixo
            controlPoints.push_back(p1);
            controlPoints.push_back(p3);
            controlPoints.push_back(p4);

            normals.push_back(n1);
            normals.push_back(n3);
            normals.push_back(n4);

            texCoords.push_back(t1);
            texCoords.push_back(t3);
            texCoords.push_back(t4);
        }
    }
    
    writeToFile(controlPoints, normals, texCoords, fileName);
}
