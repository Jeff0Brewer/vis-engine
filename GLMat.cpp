#include "GLMat.h"
#include <math.h>

void cross(const float *a, const float *b, float *out){
    out[0] = a[1]*b[2] - a[2]*b[1];
    out[1] = a[2]*b[0] - a[0]*b[2];
    out[2] = a[0]*b[1] - a[1]*b[0];
}

void normalize(float *v){
    float mag = float(sqrt(v[0]*v[0] + v[1]*v[1] + v[2]*v[2]));
    if(mag == 0.0f)
        return;
    v[0] /= mag;
    v[1] /= mag;
    v[2] /= mag;
}

void initModelMatrix(float *matrix){
    matrix[0] = 1.0f;
    matrix[1] = 0.0f;
    matrix[2] = 0.0f;
    matrix[3] = 0.0f;

    matrix[4] = 0.0f;
    matrix[5] = 1.0f;
    matrix[6] = 0.0f;
    matrix[7] = 0.0f;

    matrix[8] = 0.0f;
    matrix[9] = 0.0f;
    matrix[10] = 1.0f;
    matrix[11] = 0.0f;

    matrix[12] = 0.0f;
    matrix[13] = 0.0f;
    matrix[14] = 0.0f;
    matrix[15] = 1.0f;
}

void setPerspectiveMatrix(const float fov, const float near, const float far, const float aspect, float *matrix){
    const float fovr = float(M_PI/180.0*fov/2.0);
    const float ct = float(cos(fovr)/sin(fovr));
    const float rd = 1.0f/(far - near);

    matrix[0] = ct / aspect;
    matrix[1] = 0.0f;
    matrix[2] = 0.0f;
    matrix[3] = 0.0f;

    matrix[4] = 0.0f;
    matrix[5] = ct;
    matrix[6] = 0.0f;
    matrix[7] = 0.0f;

    matrix[8] = 0.0f;
    matrix[9] = 0.0f;
    matrix[10] = -1.0f * (far + near) * rd;
    matrix[11] = -1.0f;

    matrix[12] = 0.0f;
    matrix[13] = 0.0f;
    matrix[14] = -2.0f*near*far*rd;
    matrix[15] = 0.0f;
}

void setViewMatrix(float *position, float *focus, float *up, float *matrix){
    float forward[3] = {};
    for(int i = 0; i < 3; i++){
        forward[i] = focus[i] - position[i];
    }

    float right[3] = {};
    cross(forward, up, right);

    normalize(right);
    normalize(up);
    normalize(forward);
    
    matrix[0] = right[0];
    matrix[1] = up[0];
    matrix[2] = forward[0];
    matrix[3] = position[0];

    matrix[4] = right[1];
    matrix[5] = up[1];
    matrix[6] = forward[1];
    matrix[7] = position[1];

    matrix[8] = right[2];
    matrix[9] = up[2];
    matrix[10] = forward[2];
    matrix[11] = position[2];

    matrix[12] = 0.0f;
    matrix[13] = 0.0f;
    matrix[14] = 0.0f;
    matrix[15] = 1.0f;
}
