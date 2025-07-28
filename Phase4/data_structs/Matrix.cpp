#include "Matrix.hpp"

void multiplyMatrices(int la, int ca, const float* A,
                     int lb, int cb, const float* B,
                     float* R, int* lr, int* cr) {
    if (ca == lb) {
        if (lr) *lr = la;
        if (cr) *cr = cb;
        
        for(int i = 0; i < la; i++) {
            for(int j = 0; j < cb; j++) {
                R[i*cb + j] = 0;
                for(int k = 0; k < ca; k++) {
                    R[i*cb + j] += A[i*ca + k] * B[k*cb + j];
                }
            }
        }
    }
}

void buildRotMatrix(const float *x, const float *y, const float *z, float *m) {
    m[0] = x[0]; m[1] = y[0]; m[2] = z[0]; m[3] = 0;
    
    m[4] = x[1]; m[5] = y[1]; m[6] = z[1]; m[7] = 0;
    
    m[8] = x[2]; m[9] = y[2]; m[10] = z[2]; m[11] = 0;
    
    m[12] = 0; m[13] = 0; m[14] = 0; m[15] = 1;
}

void cross(const float a[3], const float b[3], float res[3]) {
    res[0] = a[1]*b[2] - a[2]*b[1];
    res[1] = a[2]*b[0] - a[0]*b[2];
    res[2] = a[0]*b[1] - a[1]*b[0];
}


void normalizeVector(float v[3]) {
    float len = sqrt(v[0]*v[0] + v[1]*v[1] + v[2]*v[2]);
    if(len > 0.0001f) {
        v[0] /= len;
        v[1] /= len;
        v[2] /= len;
    }
}


float length(const float *a) {
    return sqrt(a[0]*a[0] + a[1]*a[1] + a[2]*a[2]);
}

void getGlobalCatmullRomPoint(float gt, std::vector<std::vector<float>> controlPoints, float *pos, float *deriv) {
    int pointCount = controlPoints.size();
    float t = gt * pointCount;
    int index = floor(t);
    t = t - index;

    int indices[4];
    indices[0] = (index + pointCount-1) % pointCount;    
    indices[1] = (indices[0]+1) % pointCount;
    indices[2] = (indices[1]+1) % pointCount;
    indices[3] = (indices[2]+1) % pointCount;

    float T[4] = { t*t*t, t*t, t, 1 };
    float M[16] = { -0.5f, 1.5f, -1.5f, 0.5f,
                     1.0f, -2.5f, 2.0f, -0.5f,
                     -0.5f, 0.0f, 0.5f, 0.0f,
                     0.0f, 1.0f, 0.0f, 0.0f };

    for(int i = 0; i < 3; i++) {
        float P[4] = {
            controlPoints[indices[0]][i],
            controlPoints[indices[1]][i],
            controlPoints[indices[2]][i],
            controlPoints[indices[3]][i]
        };

        float A[4];
        multiplyMatrices(1, 4, T, 4, 4, M, A);
        
        if(pos) pos[i] = A[0]*P[0] + A[1]*P[1] + A[2]*P[2] + A[3]*P[3];
        
        if(deriv) {
            float dT[4] = { 3*t*t, 2*t, 1, 0 };
            multiplyMatrices(1, 4, dT, 4, 4, M, A);
            deriv[i] = A[0]*P[0] + A[1]*P[1] + A[2]*P[2] + A[3]*P[3];
        }
    }
}