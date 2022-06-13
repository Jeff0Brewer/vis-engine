#ifndef GLMAT_H
#define GLMAT_H

#include <math.h>

void multiplyMat4(float *a, float *b, float *out);

void copyMat4(float *a, float *out);

void setIdentityMatrix(float *matrix);

void setRotationMatrix(double angle, float x, float y, float z, float *matrix);

void setPerspectiveMatrix(const float fov, const float near, const float far, const float aspect, float *matrix);

void setViewMatrix(float *position, float *focus, float *up, float *right, float *matrix);

#endif
