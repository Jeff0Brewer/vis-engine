#ifndef GLMAT_H
#define GLMAT_H

#include <math.h>

void initModelMatrix(float *matrix);

void setPerspectiveMatrix(const float fov, const float near, const float far, const float aspect, float *matrix);

void setViewMatrix(float *position, float *focus, float *up, float *matrix);

#endif
