#include "../include/GLMat.h"
#include <math.h>

void cross(const float *a, const float *b, float *out) {
    out[0] = a[1]*b[2] - a[2]*b[1];
    out[1] = a[2]*b[0] - a[0]*b[2];
    out[2] = a[0]*b[1] - a[1]*b[0];
}

void normalize(float *v) {
    float mag = float(sqrt(v[0]*v[0] + v[1]*v[1] + v[2]*v[2]));
    if(mag == 0.0f)
        return;
    v[0] /= mag;
    v[1] /= mag;
    v[2] /= mag;
}

void copyMat4(const float *a, float *out) {
    for(int i = 0; i < 16; i++) {
        out[i] = a[i];
    }
}

void multiplyMat4(const float *a, const float *b, float *out) {
    out[0] = a[0]*b[0] + a[1]*b[4] + a[2]*b[8] + a[3]*b[12];
    out[1] = a[0]*b[1] + a[1]*b[5] + a[2]*b[9] + a[3]*b[13];
    out[2] = a[0]*b[2] + a[1]*b[6] + a[2]*b[10] + a[3]*b[14];
    out[3] = a[0]*b[3] + a[1]*b[7] + a[2]*b[11] + a[3]*b[15];
    
    out[4] = a[4]*b[0] + a[5]*b[4] + a[6]*b[8] + a[7]*b[12];
    out[5] = a[4]*b[1] + a[5]*b[5] + a[6]*b[9] + a[7]*b[13];
    out[6] = a[4]*b[2] + a[5]*b[6] + a[6]*b[10] + a[7]*b[14];
    out[7] = a[4]*b[3] + a[5]*b[7] + a[6]*b[11] + a[7]*b[15];
    
    out[8] = a[8]*b[0] + a[9]*b[4] + a[10]*b[8] + a[11]*b[12];
    out[9] = a[8]*b[1] + a[9]*b[5] + a[10]*b[9] + a[11]*b[13];
    out[10] = a[8]*b[2] + a[9]*b[6] + a[10]*b[10] + a[11]*b[14];
    out[11] = a[8]*b[3] + a[9]*b[7] + a[10]*b[11] + a[11]*b[15];
    
    out[12] = a[12]*b[0] + a[13]*b[4] + a[14]*b[8] + a[15]*b[12];
    out[13] = a[12]*b[1] + a[13]*b[5] + a[14]*b[9] + a[15]*b[13];
    out[14] = a[12]*b[2] + a[13]*b[6] + a[14]*b[10] + a[15]*b[14];
    out[15] = a[12]*b[3] + a[13]*b[7] + a[14]*b[11] + a[15]*b[15];
}

void setIdentityMatrix(float *matrix) {
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

void setRotationMatrix(const double angle, const float x, const float y, const float z, float *matrix) {
    float c = float(cos(angle));
    float nc = 1.0f - c;
    float s = float(sin(angle));

    matrix[0] = c + x*x*nc;
    matrix[1] = x*y*nc - z*s;
    matrix[2] = x*z*nc + y*s;
    matrix[3] = 0.0f;

    matrix[4] = y*x*nc + z*s;
    matrix[5] = c + y*y*nc;
    matrix[6] = y*z*nc - x*s;
    matrix[7] = 0.0f;

    matrix[8] = z*x*nc - y*s;
    matrix[9] = z*y*nc + x*s;
    matrix[10] = c + z*z*nc;
    matrix[11] = 0.0f;

    matrix[12] = 0.0f;
    matrix[13] = 0.0f;
    matrix[14] = 0.0f;
    matrix[15] = 1.0f;
}

void setPerspectiveMatrix(const float fov, const float near, const float far, const float aspect, float *matrix) {
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
    matrix[14] = -2.0f * near * far * rd;
    matrix[15] = 0.0f;
}

void setViewMatrix(const float *position, const float *focus, float *up, float *right, float *matrix) {
    float forward[3] = {
        position[0] - focus[0],
        position[1] - focus[1],
        position[2] - focus[2]
    };
    normalize(forward);
    cross(forward, up, right);
    normalize(right);
    cross(right, forward, up);
    
    matrix[0] = right[0];
    matrix[1] = up[0];
    matrix[2] = forward[0];
    matrix[3] = 0.0f;

    matrix[4] = right[1];
    matrix[5] = up[1];
    matrix[6] = forward[1];
    matrix[7] = 0.0f;

    matrix[8] = right[2];
    matrix[9] = up[2];
    matrix[10] = forward[2];
    matrix[11] = 0.0f;

    matrix[12] = -(matrix[0]*position[0] + matrix[4]*position[1] + matrix[8]*position[2]);
    matrix[13] = -(matrix[1]*position[0] + matrix[5]*position[1] + matrix[9]*position[2]);
    matrix[14] = -(matrix[2]*position[0] + matrix[6]*position[1] + matrix[10]*position[2]);
    matrix[15] = 1.0f - (matrix[3]*position[0] + matrix[7]*position[1] + matrix[11]*position[2]);
}
