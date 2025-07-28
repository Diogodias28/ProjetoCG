#include "../../data_structs/Model.hpp"

float bernstein(int, float);

float bernsteinDerivative(int, float);

Point bezierPatchDU(const std::vector<Point>&, float, float);

Point bezierPatchDV(const std::vector<Point>&, float, float);

Point computeBezierNormal(const std::vector<Point>&, float, float);

Point bezierPatch(const std::vector<Point>&, float, float);

void genPatch(const std::string&, int, std::string);