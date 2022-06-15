#define CATCH_CONFIG_RUNNER
#include "catch.hpp"
#define TEST true
#define GLFW_INCLUDE_GLCOREARB
#include <GLFW/glfw3.h>

int runCatchTests(int argc, char* const argv[]) {
    return Catch::Session().run(argc, argv);
}
 
int main( int argc, char* const argv[] ) {
    // setup gl context for testing
    GLFWwindow* window;
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

    window = glfwCreateWindow( 1, 1, "test", NULL, NULL );
    if (!window){
         glfwTerminate();
         return -1;
    }
    glfwMakeContextCurrent(window);

    // run tests
    return runCatchTests(argc, argv);
}

