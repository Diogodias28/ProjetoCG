#include <vector>
#include <fstream>
#include <string>
#include <string.h> 
#include <stdio.h>
#include <cstdlib>
#include <ctime>
#define _USE_MATH_DEFINES
#include <math.h>
#include "../data_structs/Point.hpp"
#include "../data_structs/Model.hpp"

using namespace std;

string fileName;

void genPlane(int length, int divisions){
    std::vector<Point> controlPoints;
    float part = (float)length / divisions;
    float half = length / 2.0f;

    for (int i = 0; i < divisions; i++) {
        for (int j = 0; j < divisions; j++) {
            float x1 = -half + i * part;
            float z1 = -half + j * part;
            float x2 = x1 + part;
            float z2 = z1 + part;

            // Triângulo 1
            controlPoints.push_back(makePoint(x1, 0.0f, z1));
            controlPoints.push_back(makePoint(x1, 0.0f, z2));
            controlPoints.push_back(makePoint(x2, 0.0f, z1));

            // Triângulo 2
            controlPoints.push_back(makePoint(x2, 0.0f, z1));
            controlPoints.push_back(makePoint(x1, 0.0f, z2));
            controlPoints.push_back(makePoint(x2, 0.0f, z2));
        }
    }

    writeToFile(controlPoints, fileName);
}

void genRing(float innerRadius, float outerRadius, int slices) {
    std::vector<Point> controlPoints;

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


        // Triângulo 1 (parte de cima)
        controlPoints.push_back(inner_1);
        controlPoints.push_back(outer_1);
        controlPoints.push_back(outer_2);

        // Triângulo 2 (parte de cima)
        controlPoints.push_back(inner_1);
        controlPoints.push_back(outer_2);
        controlPoints.push_back(inner_2);

        // Triângulo 1 (parte de baixo)
        controlPoints.push_back(inner_1);
        controlPoints.push_back(inner_2);
        controlPoints.push_back(outer_2);

        // Triângulo 2 (parte de baixo) - invertido
        controlPoints.push_back(inner_1);
        controlPoints.push_back(outer_2);
        controlPoints.push_back(outer_1);
    }

    writeToFile(controlPoints, fileName);
}

void genSphere(float radius, int slices, int stacks) {

    std::vector<Point> controlPoints;

    // divide o circulo de 360 graus em slices iguais
    float anglePerSlice = (float)(2 * M_PI) / slices;
    // divide o arco de 180 graus em stacks iguais
    float anglePerStack = (float)M_PI / stacks;

    float alpha, beta;
    Point p1, p2, p3, p4;

    for (int j = 0; j < stacks; j++) {
        // ângulo para a stack atual e seguinte
        beta = j * anglePerStack;
        float nextBeta = (j + 1) * anglePerStack;

        for (int i = 0; i < slices; i++) {
            // ângulo para o slice atual e seguinte
            alpha = i * anglePerSlice;
            float nextAlpha = (i + 1) * anglePerSlice;

            // pontos na stack atual
            p1 = makePoint(radius * sinf(beta) * sinf(alpha), radius * cosf(beta), radius * sinf(beta) * cosf(alpha));
            p2 = makePoint(radius * sinf(beta) * sinf(nextAlpha), radius * cosf(beta), radius * sinf(beta) * cosf(nextAlpha));

            // pontos na próxima stack
            p3 = makePoint(radius * sinf(nextBeta) * sinf(alpha), radius * cosf(nextBeta), radius * sinf(nextBeta) * cosf(alpha));
            p4 = makePoint(radius * sinf(nextBeta) * sinf(nextAlpha), radius * cosf(nextBeta), radius * sinf(nextBeta) * cosf(nextAlpha));

            // Vamos fazer os triângulos
            // triângulo de cima
            controlPoints.push_back(p1);
            controlPoints.push_back(p4);
            controlPoints.push_back(p2);

            // triângulo de baixo
            controlPoints.push_back(p1);
            controlPoints.push_back(p3);
            controlPoints.push_back(p4);
        }
    }
    
    writeToFile(controlPoints, fileName);
}


void genBox(int length, int grid) {

    std::vector<Point> controlPoints;
    float part = (float)length / grid; 
    float half = length / 2.0f;

    for (int i = 0; i < grid; i++) {
        for (int j = 0; j < grid; j++) {
            float a = -half + i * part;
            float b = -half + j * part;

            // Front Face
            controlPoints.push_back(makePoint(a + part, b + part, half));
            controlPoints.push_back(makePoint(a, b + part, half));
            controlPoints.push_back(makePoint(a, b, half));

            controlPoints.push_back(makePoint(a + part, b + part, half));
            controlPoints.push_back(makePoint(a, b, half));
            controlPoints.push_back(makePoint(a + part, b, half));

			// Back Face
			controlPoints.push_back(makePoint(a, b, -half));
			controlPoints.push_back(makePoint(a, b + part, -half));
			controlPoints.push_back(makePoint(a + part, b, -half));
	  
			controlPoints.push_back(makePoint(a, b + part, -half));
			controlPoints.push_back(makePoint(a + part, b + part, -half));
			controlPoints.push_back(makePoint(a + part, b, -half));
	  
			// Left Face
			controlPoints.push_back(makePoint(-half, a, b));
			controlPoints.push_back(makePoint(-half, a, b + part));
			controlPoints.push_back(makePoint(-half, a + part, b));
	  
			controlPoints.push_back(makePoint(-half, a, b + part));
			controlPoints.push_back(makePoint(-half, a + part, b + part));
			controlPoints.push_back(makePoint(-half, a + part, b));
	  
			// Right Face done
			controlPoints.push_back(makePoint(half, a + part, b + part));
			controlPoints.push_back(makePoint(half, a, b + part));
			controlPoints.push_back(makePoint(half, a, b));
	  
			controlPoints.push_back(makePoint(half, a + part, b + part));
			controlPoints.push_back(makePoint(half, a, b));
			controlPoints.push_back(makePoint(half, a + part, b));
	  
			// Top Face
			controlPoints.push_back(makePoint(a, half, b));
			controlPoints.push_back(makePoint(a + part, half, b + part));
			controlPoints.push_back(makePoint(a + part, half, b));
	  
			controlPoints.push_back(makePoint(a, half, b));
			controlPoints.push_back(makePoint(a, half, b + part));
			controlPoints.push_back(makePoint(a + part, half, b + part));
	  
			// Bottom Face
			controlPoints.push_back(makePoint(a, -half, b));
			controlPoints.push_back(makePoint(a + part, -half, b));
			controlPoints.push_back(makePoint(a, -half, b + part));
	  
			controlPoints.push_back(makePoint(a, -half, b + part));
			controlPoints.push_back(makePoint(a + part, -half, b));
			controlPoints.push_back(makePoint(a + part, -half, b + part));
			
        }
    }
    writeToFile(controlPoints, fileName);
}

void genCone(const float radius, const float height, const size_t slices, const size_t stacks) {
    
    std::vector<Point> controlPoints;

    const float alpha = (float) 2 * M_PI / slices;
    const float heightPerStack = (float) height / stacks;

    const Point base_middle = createPoint();

    for (int slice = 0; slice < slices; slice++) {
        for (int stack = 0; stack < stacks; stack++) {

            const float currRadius = radius - stack * radius / stacks;
            const float nextRadius = radius - (stack + 1) * radius / stacks;

            const Point bottom_left = makePoint(currRadius * sin(slice * alpha), stack * heightPerStack, currRadius * cos(slice * alpha));
            const Point bottom_right = makePoint(currRadius * sin((slice + 1) * alpha), stack * heightPerStack, currRadius * cos((slice + 1) * alpha));
            const Point top_left = makePoint (nextRadius * sin(slice * alpha), (stack + 1) * heightPerStack,nextRadius * cos(slice * alpha));
            const Point top_right = makePoint(nextRadius * sin((slice + 1) * alpha), (stack + 1) * heightPerStack, nextRadius * cos((slice + 1) * alpha));

            controlPoints.push_back(top_left);
            controlPoints.push_back(bottom_left);
            controlPoints.push_back(bottom_right);

            controlPoints.push_back(top_left);
            controlPoints.push_back(bottom_right);
            controlPoints.push_back(top_right);
        }

        const Point base_bottom_left = makePoint(radius * sin(slice * alpha), 0.0f, radius * cos(slice * alpha));
        const Point base_bottom_right = makePoint(radius * sin((slice + 1) * alpha), 0.0f, radius * cos((slice + 1) * alpha));

        controlPoints.push_back(base_middle);
        controlPoints.push_back(base_bottom_right);
        controlPoints.push_back(base_bottom_left);
    }

    writeToFile(controlPoints, fileName);
}

int main(int argc, char *argv[]) {
    
    if (argc >= 5) { // no minimo tem sempre 5 argumentos

        // plane
        if(strcmp(argv[1], "plane") == 0) {
            int length = atoi(argv[2]);
            int divisions = atoi(argv[3]);
            fileName = argv[4];
            genPlane(length, divisions);
        }

        // anel
        else if(strcmp(argv[1], "ring") == 0) {
            float innerRadius = atof(argv[2]);
            float outerRadius = atof(argv[3]);
            int slices = atoi(argv[4]);
            fileName = argv[5];
            genRing(innerRadius, outerRadius, slices);
        }
        
        // cone
        else if(strcmp(argv[1], "cone") == 0) {
            int radius = atoi(argv[2]);
            int height = atoi(argv[3]);
            int slices = atoi(argv[4]);
            int stacks = atoi(argv[5]);
            fileName = argv[6];
            genCone(radius, height, slices, stacks);
        }

        // sphere
        else if(strcmp(argv[1], "sphere") == 0) {
            int radius = atoi(argv[2]);
            int slices = atoi(argv[3]);
            int stacks = atoi(argv[4]);
            fileName = argv[5];
            genSphere(radius, slices, stacks);
        }

        // box
        else if(strcmp(argv[1], "box") == 0) {
            int length = atoi(argv[2]);
            int grid = atoi(argv[3]);
            fileName = argv[4];
            genBox(length, grid);
        }

        else {
            printf("Figura inválida.");
            return 1;
        }
    }
    
    else {
        printf("Número de argumentos inválido.");
    }

    return 0;
}
