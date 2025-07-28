#include "bezierPatches.hpp"

float bernstein(int i, float t) {
    switch (i) {
        case 0:
        return pow(1 - t, 3);
        case 1:
        return 3 * t * pow(1 - t, 2);
        case 2:
        return 3 * pow(t, 2) * (1 - t);
        case 3:
        return pow(t, 3);
        default:
        return 0;
    }
}

float bernsteinDerivative(int i, float t) {
    switch (i) {
        case 0:
        return -3 * pow(1 - t, 2);
        case 1:
        return 3 * pow(1 - t, 2) - 6 * t * (1 - t);
        case 2:
        return 6 * t * (1 - t) - 3 * pow(t, 2);
        case 3:
        return 3 * pow(t, 2);
        default:
        return 0;
    }
}

Point bezierPatchDU(const std::vector<Point>& patchControlPoints, float u, float v) {
    Point result = createPoint();
    float x = 0.0f, y = 0.0f, z = 0.0f;

    // Combinar as funções de Bernstein para u e v
    for (int i = 0; i < 4; i++) {
        float bu = bernsteinDerivative(i, u);
        for (int j = 0; j < 4; j++) {
            float bv = bernstein(j, v);
            float b = bu * bv;
            
            // Adicionar a contribuição do ponto de controle correspondente
            x += b * getX(patchControlPoints[i * 4 + j]);
            y += b * getY(patchControlPoints[i * 4 + j]);
            z += b * getZ(patchControlPoints[i * 4 + j]);
        }
    }

    setX(result, x);
    setY(result, y);
    setZ(result, z);

    return result;
}

Point bezierPatchDV(const std::vector<Point>& patchControlPoints, float u, float v) {
    Point result = createPoint();
    float x = 0.0f, y = 0.0f, z = 0.0f;

    // Combinar as funções de Bernstein para u e v
    for (int i = 0; i < 4; i++) {
        float bu = bernstein(i, u);
        for (int j = 0; j < 4; j++) {
            float bv = bernsteinDerivative(j, v);
            float b = bu * bv;

            // Adicionar a contribuição do ponto de controle correspondente
            x += b * getX(patchControlPoints[i * 4 + j]);
            y += b * getY(patchControlPoints[i * 4 + j]);
            z += b * getZ(patchControlPoints[i * 4 + j]);
        }
    }
    setX(result, x);
    setY(result, y);
    setZ(result, z);

    return result;
}


Point computeBezierNormal(const std::vector<Point>& patchControlPoints, float u, float v) {
    Point du = bezierPatchDU(patchControlPoints, u, v);
    Point dv = bezierPatchDV(patchControlPoints, u, v);
    Point normal = crossProduct(dv,du);  // Ordem ajustada para a orientação
    float x = getX(normal), y = getY(normal), z = getZ(normal);
    float length = std::sqrt(x * x + y * y + z * z);

    if (length != 0.0f) {
        x /= length;
        y /= length;
        z /= length;
    } else {
        x = 0.0f;
        y = 0.0f;
        z = 1.0f;
    }

    setX(normal, x);
    setY(normal, y);
    setZ(normal, z);

    return normal;
}


Point bezierPatch(const std::vector<Point>& patchControlPoints, float u, float v) {
    Point result = createPoint();
    float x = 0.0f, y = 0.0f, z = 0.0f;

    // Combinar as funções de Bernstein para u e v
    for (int i = 0; i < 4; i++) {
        float bu = bernstein(i, u);
        for (int j = 0; j < 4; j++) {
            float bv = bernstein(j, v);
            float b = bu * bv;

            x += b * getX(patchControlPoints[i * 4 + j]);
            y += b * getY(patchControlPoints[i * 4 + j]);
            z += b * getZ(patchControlPoints[i * 4 + j]);
        }
    }
    setX(result, x);
    setY(result, y);
    setZ(result, z);

    return result;
}


void genPatch(const std::string& patchFile, int tessellation, std::string fileName) {
    std::vector<Point> controlPoints;

    std::ifstream file(patchFile);
    if (!file.is_open()) {
        std::cerr << "Erro ao abrir o arquivo de patches: " << patchFile << std::endl;
        return;
    }

    size_t numPatches;
    file >> numPatches;

    std::vector<std::vector<size_t>> patches;

    for (size_t i = 0; i < numPatches; ++i) {
        std::vector<size_t> patch;
        for (size_t j = 0; j < 16; ++j) {
            size_t idx;
            char virgula;
            file >> idx;
            if (j < 15) file >> virgula; // lê e descarta a vírgula
            patch.push_back(idx);
        }
        patches.push_back(patch);
    }

    size_t numControlPoints;
    file >> numControlPoints;

    for (size_t i = 0; i < numControlPoints; ++i) {
        float x, y, z;
        char virgula;
    
        file >> x >> virgula >> y >> virgula >> z;
        controlPoints.push_back(makePoint(x, y, z));
    }


    file.close();

    // Verificar tesselação
    if (tessellation <= 0) {
        std::cerr << "Tesselação inválida: " << tessellation << std::endl;
        return;
    }

    // Gerar os pontos da superfície a partir dos patches e pontos de controlo
    std::vector<Point> points;
    std::vector<Point> normals;
    std::vector<Point> texCoords;
    
    for (size_t i = 0; i < numPatches; ++i) {
        std::vector<Point> patchControlPoints;
        for (size_t j = 0; j < 16; ++j) {
            patchControlPoints.push_back(controlPoints[patches[i][j]]);
        }

        for (int u = 0; u < tessellation; ++u) {
            for (int v = 0; v < tessellation; ++v) {
                float u1 = (float)(u) / tessellation;
                float v1 = (float)(v) / tessellation;
                float u2 = (float)(u + 1) / tessellation;
                float v2 = (float)(v + 1) / tessellation;

                Point p1 = bezierPatch(patchControlPoints, u1, v1);
                Point p2 = bezierPatch(patchControlPoints, u2, v1);
                Point p3 = bezierPatch(patchControlPoints, u1, v2);
                Point p4 = bezierPatch(patchControlPoints, u2, v2);

                // Adicionar os triângulos
                points.push_back(p1);
                points.push_back(p3);
                points.push_back(p2);

                points.push_back(p2);
                points.push_back(p3);
                points.push_back(p4);

                Point n1 = computeBezierNormal(patchControlPoints, u1, v1);
                Point n2 = computeBezierNormal(patchControlPoints, u2, v1);
                Point n3 = computeBezierNormal(patchControlPoints, u1, v2);
                Point n4 = computeBezierNormal(patchControlPoints, u2, v2);

                normals.push_back(n1);
                normals.push_back(n3);
                normals.push_back(n2);

                normals.push_back(n2);
                normals.push_back(n3);
                normals.push_back(n4);

                texCoords.push_back(makeTexturePoint(u1, v1)); 
                texCoords.push_back(makeTexturePoint(u1, v2)) ; 
                texCoords.push_back(makeTexturePoint(u2, v1)); 

                texCoords.push_back(makeTexturePoint(u2, v1)); 
                texCoords.push_back(makeTexturePoint(u1, v2)); 
                texCoords.push_back(makeTexturePoint(u2, v2)); 

            }
        }
    }

    writeToFile(points, normals, texCoords, fileName);
}
