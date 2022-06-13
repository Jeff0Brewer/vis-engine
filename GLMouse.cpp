#include "GLMouse.h"

double lastX = 0.0;
double lastY = 0.0;

void mouseRotate(double mouseX, double mouseY, float *matrix) {
    double moveX = mouseX - lastX;
    lastX = mouseX;
    double moveY = mouseY - lastY;
    lastY = mouseY;

    float rotation[16] = {};
    setRotationMatrix(moveX/100.0, 0.0, 0.0, 1.0, rotation);
    float oldMat[16] = {};
    copyMat4(matrix, oldMat);
    multiplyMat4(oldMat, rotation, matrix);


   // find mouse movement
   // determine axis perpendicular to movement
   // rotate matrix about axis relative to movement magnitude

   // functions needed: rotation matrix generation, matrix multiplication
}
