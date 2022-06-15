#ifndef GLMAT_H
#define GLMAT_H

#include <math.h>

void multiplyMat4(const float *a, const float *b, float *out);

void copyMat4(const float *a, float *out);

void setIdentityMatrix(float *matrix);

void setRotationMatrix(const double angle, const float x, const float y, const float z, float *matrix);

void setPerspectiveMatrix(const float fov, const float near, const float far, const float aspect, float *matrix);

void setViewMatrix(const float *position, const float *focus, float *up, float *right, float *matrix);

#endif
