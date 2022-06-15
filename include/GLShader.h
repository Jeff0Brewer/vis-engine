#ifndef GLSHADER_H
#define GLSHADER_H
#define GL_SILENCE_DEPRECATION
#include <GLFW/glfw3.h>
#include <string>

std::string readFile(const char *filePath);

GLuint loadShader(const char *source, GLenum type);

GLuint loadProgram(const char *vertexPath, const char *fragmentPath);

#endif
