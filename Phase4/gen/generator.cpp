#include "primitives/cone.hpp"
#include "primitives/ring.hpp"
#include "primitives/plane.hpp"
#include "primitives/box.hpp"
#include "primitives/bezierPatches.hpp"
#include "primitives/sphere.hpp"

using namespace std;

int main(int argc, char *argv[]) {
    
    if (argc >= 5) { // no minimo tem sempre 5 argumentos

        // plane
        if(strcmp(argv[1], "plane") == 0) {
            int length = atoi(argv[2]);
            int divisions = atoi(argv[3]);
            std::string fileName = argv[4];
            genPlane(length, divisions, fileName);
        }

        // anel
        else if(strcmp(argv[1], "ring") == 0) {
            float innerRadius = atof(argv[2]);
            float outerRadius = atof(argv[3]);
            int slices = atoi(argv[4]);
            std::string fileName = argv[5];
            genRing(innerRadius, outerRadius, slices, fileName);
        }
        
        // cone
        else if(strcmp(argv[1], "cone") == 0) {
            int radius = atoi(argv[2]);
            int height = atoi(argv[3]);
            int slices = atoi(argv[4]);
            int stacks = atoi(argv[5]);
            std::string fileName = argv[6];
            genCone(radius, height, slices, stacks, fileName);
        }

        // sphere
        else if(strcmp(argv[1], "sphere") == 0) {
            int radius = atoi(argv[2]);
            int slices = atoi(argv[3]);
            int stacks = atoi(argv[4]);
            std::string fileName = argv[5];
            genSphere(radius, slices, stacks, fileName);
        }

        // box
        else if(strcmp(argv[1], "box") == 0) {
            int length = atoi(argv[2]);
            int grid = atoi(argv[3]);
            std::string fileName = argv[4];
            genBox(length, grid, fileName);
        }

        // patch
        else if (strcmp(argv[1], "patch") == 0) {
            std::string patchFile = argv[2];
            int tessellation = atoi(argv[3]);
            std::string fileName = argv[4];
            genPatch(patchFile, tessellation, fileName);
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