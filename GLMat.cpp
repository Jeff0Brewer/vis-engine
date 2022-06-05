#include "GLMat.h"

#include <math.h>

void setPerspective(const float fov, const float near, const float far, const float aspect, float *matrix){
    const float tfov2= float(tan(fov/2.0f));
    matrix[0] = aspect * tfov2;
    matrix[1] = 0.0f;
    matrix[2] = 0.0f;
    matrix[3] = 0.0f;

    matrix[4] = 0.0f;
    matrix[5] = 1.0f / tfov2;
    matrix[6] = 0.0f;
    matrix[7] = 0.0f;

    matrix[8] = 0.0f;
    matrix[9] = 0.0f;
    matrix[10] = -1.0f * (far + near)/(far - near);
    matrix[11] = -1.0f * (2.0f * far * near)/(far - near);

    matrix[12] = 0.0f;
    matrix[13] = 0.0f;
    matrix[14] = -1.0f;
    matrix[15] = 0.0f;
}
