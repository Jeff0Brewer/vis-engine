#define GL_SILENCE_DEPRECATION
#include "../include/GLShader.h"

#include <stdexcept>
#include <fstream>

std::string readFile(const char *filePath) {
    std::ifstream fileStream(filePath, std::ios::in);
    if(!fileStream.is_open()) {
        throw std::runtime_error(std::string("Could not read file ") + filePath);
        // std::cerr << "Could not read file " << filePath << std::endl;
    }

    std::string content;
    std::string line = "";
    while(!fileStream.eof()) {
        std::getline(fileStream, line);
        content.append(line + "\n");
    }
    fileStream.close();

    return content;
}

GLuint loadShader(const char *source, GLenum type) {
    int success;
    GLuint shader = glCreateShader(type);
    glShaderSource(shader, 1, &source, NULL);
    glCompileShader(shader);
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

    if(!success) {
        int logSize = 512;
        char infoLog[logSize];
        glGetShaderInfoLog(shader, logSize, NULL, infoLog);
        throw std::runtime_error(std::string("Vertex shader compilation failed\n") + infoLog);
        //std::cerr << "Vertex shader compilation failed\n" << infoLog << std::endl;
    }

    return shader;
}

GLuint loadProgram(const char *vertexPath, const char *fragmentPath) {
    std::string vertStr = readFile(vertexPath);
    const char *vertSource = vertStr.c_str();
    GLuint vertShader = loadShader(vertSource, GL_VERTEX_SHADER);

    std::string fragStr = readFile(fragmentPath);
    const char *fragSource = fragStr.c_str();
    GLuint fragShader = loadShader(fragSource, GL_FRAGMENT_SHADER);

    int success;

    GLuint program = glCreateProgram();
    glAttachShader(program, vertShader);
    glAttachShader(program, fragShader);
    glLinkProgram(program);
    glGetProgramiv(program, GL_LINK_STATUS, &success);

    if(!success) {
        int logSize = 512;
        char infoLog[logSize];
        glGetProgramInfoLog(program, logSize, NULL, infoLog);
        throw std::runtime_error(std::string("Shader linking failed\n") + infoLog);
        //std::cerr << "Shader linking failed\n" << infoLog << std::endl;
    }

    glDeleteShader(vertShader);
    glDeleteShader(fragShader);

    return program;
}
