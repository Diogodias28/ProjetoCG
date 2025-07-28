#include "ring.hpp"

void genRing(float innerRadius, float outerRadius, int slices, std::string fileName) {
    std::vector<Point> controlPoints;
    std::vector<Point> normals;
    std::vector<Point> texCoords;

    const float alpha = (float) 2 * M_PI / slices;

    for (int slice = 0; slice < slices; slice++) {
        float inner_x1 = innerRadius * sin(slice * alpha);
        float inner_z1 = innerRadius * cos(slice * alpha);
        float inner_x2 = innerRadius * sin((slice + 1) * alpha);
        float inner_z2 = innerRadius * cos((slice + 1) * alpha);

        float outer_x1 = outerRadius * sin(slice * alpha);
        float outer_z1 = outerRadius * cos(slice * alpha);
        float outer_x2 = outerRadius * sin((slice + 1) * alpha);
        float outer_z2 = outerRadius * cos((slice + 1) * alpha);

        Point inner_1 = makePoint(inner_x1, 0.0f, inner_z1);
        Point inner_2 = makePoint(inner_x2, 0.0f, inner_z2);
        Point outer_1 = makePoint(outer_x1, 0.0f, outer_z1);
        Point outer_2 = makePoint(outer_x2, 0.0f, outer_z2);
        
        float texInner = (float)slice / slices;
        float texOuter = (float)(slice + 1) / slices;
        float texLeft = 0.0f;
        float texRight = 1.0f;


        // Triângulo 1 (parte de cima)
        controlPoints.push_back(inner_1);
        controlPoints.push_back(outer_1);
        controlPoints.push_back(outer_2);
        
        texCoords.push_back(makeTexturePoint(texRight, texInner));
        texCoords.push_back(makeTexturePoint(texLeft, texInner));
        texCoords.push_back(makeTexturePoint(texLeft, texOuter));

        // Triângulo 2 (parte de cima)
        controlPoints.push_back(inner_1);
        controlPoints.push_back(outer_2);
        controlPoints.push_back(inner_2);

        texCoords.push_back(makeTexturePoint(texRight, texInner));
        texCoords.push_back(makeTexturePoint(texLeft, texOuter));
        texCoords.push_back(makeTexturePoint(texLeft, texInner));

        for(int k = 0; k < 6; k++){
            normals.push_back(makePoint(0, 1, 0));
        }

        // Triângulo 1 (parte de baixo)
        controlPoints.push_back(inner_1);
        controlPoints.push_back(inner_2);
        controlPoints.push_back(outer_2);

        texCoords.push_back(makeTexturePoint(texLeft, texInner));
        texCoords.push_back(makeTexturePoint(texRight, texInner));
        texCoords.push_back(makeTexturePoint(texRight, texOuter));

        // Triângulo 2 (parte de baixo) - invertido
        controlPoints.push_back(inner_1);
        controlPoints.push_back(outer_2);
        controlPoints.push_back(outer_1);

        texCoords.push_back(makeTexturePoint(texLeft, texInner));
        texCoords.push_back(makeTexturePoint(texRight, texOuter));
        texCoords.push_back(makeTexturePoint(texLeft, texOuter));

        for(int k = 0; k < 6; k++){
            normals.push_back(makePoint(0, -1, 0));
        }
    }

    writeToFile(controlPoints, normals, texCoords, fileName);
}