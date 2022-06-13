#include "GLMouse.h"
#include <math.h>

double lastX = 0.0;
double lastY = 0.0;
bool lastDown = false;

void mouseRotate(double mouseX, double mouseY, bool mouseDown, float *up, float *right, float *matrix) {
    if (!mouseDown) {
        lastDown = false;
        return;
    }
    if (!lastDown) {
        lastDown = true;
        lastX = mouseX;
        lastY = mouseY;
        return;
    }
    double moveX = mouseX - lastX;
    lastX = mouseX;
    double moveY = mouseY - lastY;
    lastY = mouseY;

    float rotation[16] = {};
    float old[16] = {};
    
    double rotSpeed = .01;
    setRotationMatrix(moveX*rotSpeed, up[0], up[1], up[2], rotation);
    copyMat4(matrix, old);
    multiplyMat4(old, rotation, matrix);

    setRotationMatrix(moveY*rotSpeed, right[0], right[2], right[2], rotation);
    copyMat4(matrix, old);
    multiplyMat4(old, rotation, matrix);
}
