/* Ask for an OpenGL Core Context */
#define GLFW_INCLUDE_GLCOREARB
#include "GLShader.h"
#include "GLMat.h"
#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>

float randf(){
    return static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
}

int main(int argc, char** argv){
    srand(time(NULL));

    GLFWwindow* window;

    /* Initialize the library */
    if ( !glfwInit() ){
         return -1;
    }

#ifdef __APPLE__
    /* We need to explicitly ask for a 3.2 context on OS X */
    glfwWindowHint (GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint (GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint (GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint (GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#endif

    /* Create a windowed mode window and its OpenGL context */
    const int windowWidth = 1280;
    const int windowHeight = 720;
    window = glfwCreateWindow( windowWidth, windowHeight, "vis", NULL, NULL );
    if (!window){
         glfwTerminate();
         return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    GLuint shaderProgram = loadProgram("./shaders/defVert.glsl", "./shaders/defFrag.glsl");
    glEnable(GL_PROGRAM_POINT_SIZE);

    int numVertex = 1000;
    float verts [3*numVertex];
    for(int i = 0; i < numVertex; i++){
        const int off = i*3;
        verts[off] = randf()*2.0f - 1.0f;
        verts[off+1] = randf()*2.0f - 1.0f;
        verts[off+2] = randf()*2.0f - 1.0f;
    }
    
    GLuint VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    GLuint VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glUseProgram(shaderProgram);
    GLint uModelMatrix = glGetUniformLocation(shaderProgram, "modelMatrix");
    GLint uViewMatrix = glGetUniformLocation(shaderProgram, "viewMatrix");
    GLint uProjMatrix = glGetUniformLocation(shaderProgram, "projMatrix");

    float modelMatrix[16] = {};
    initModelMatrix(modelMatrix);
    glUniformMatrix4fv(uModelMatrix, 1, false, modelMatrix);

    float viewMatrix[16] = {};
    float camPosition[3] = {0.0f, 8.0f, 0.0f};
    float camFocus[3] = {0.0f, 0.0f, 0.0f};
    float camUp[3] = {0.0f, 0.0f, 1.0f};
    setViewMatrix(camPosition, camFocus, camUp, viewMatrix);
    glUniformMatrix4fv(uViewMatrix, 1, false, viewMatrix);


    float projMatrix[16] = {};
    setPerspectiveMatrix(80.0, 0.1, 1000.0, float(windowWidth) / float(windowHeight), projMatrix);
    glUniformMatrix4fv(uProjMatrix, 1, false, projMatrix);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window)){
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glDrawArrays(GL_POINTS, 0, numVertex);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();

    return 0;
}
