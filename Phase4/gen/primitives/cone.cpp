#include "cone.hpp"

void genCone(const float radius, const float height, const size_t slices, const size_t stacks, std::string fileName) {
    
    std::vector<Point> controlPoints;
    std::vector<Point> normals;
    std::vector<Point> texCoords;

    const float alpha = (float) 2 * M_PI / slices;
    const float heightPerStack = (float) height / stacks;

    float hypotenuse = sqrt(radius*radius + height * height);

    float cosTheta = radius / hypotenuse;
    float sinTheta = height / hypotenuse;  


    for (int slice = 0; slice < slices; slice++) {
        for (int stack = 0; stack < stacks; stack++) {

            // points
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

            // normals
            float currAlpha = alpha * slice;
            float nextAlpha = alpha * (slice + 1);

            Point n1 = makePoint(sin(currAlpha) * cosTheta, sinTheta, cos(currAlpha) * cosTheta);
            Point n2 = makePoint(sin(nextAlpha) * cosTheta, sinTheta, cos(nextAlpha) * cosTheta);

            normals.push_back(n1);
            normals.push_back(n1);
            normals.push_back(n2);

            normals.push_back(n1);
            normals.push_back(n2);
            normals.push_back(n2);

            // textures
            float sl1 = (float) slice / slices;
            float sl2 = (float) (slice + 1) / slices;
            float st1 = 1.0f - (float) stack / stacks;
            float st2 = 1.0f - (float) (stack + 1) / stacks;

            texCoords.push_back(makeTexturePoint(sl1, st2));
            texCoords.push_back(makeTexturePoint(sl1, st1));
            texCoords.push_back(makeTexturePoint(sl2, st1));

            texCoords.push_back(makeTexturePoint(sl1, st2));
            texCoords.push_back(makeTexturePoint(sl2, st1));
            texCoords.push_back(makeTexturePoint(sl2, st2));
        }

        const Point base_middle = createPoint();
        const Point base_bottom_left = makePoint(radius * sin(slice * alpha), 0.0f, radius * cos(slice * alpha));
        const Point base_bottom_right = makePoint(radius * sin((slice + 1) * alpha), 0.0f, radius * cos((slice + 1) * alpha));

        controlPoints.push_back(base_middle);
        controlPoints.push_back(base_bottom_right);
        controlPoints.push_back(base_bottom_left);

        texCoords.push_back(makeTexturePoint(0.5f, 0.5f));
        texCoords.push_back(makeTexturePoint(0.5f + 0.5f * sin((slice + 1) * alpha), 0.5f + 0.5f * cos((slice + 1) * alpha)));
        texCoords.push_back(makeTexturePoint(0.5f + 0.5f * sin(slice * alpha), 0.5f + 0.5f * cos(slice * alpha)));

        Point nB = makePoint(0, -1, 0);
        normals.push_back(nB);
        normals.push_back(nB);
        normals.push_back(nB);
    }

    writeToFile(controlPoints, normals, texCoords, fileName);
}
