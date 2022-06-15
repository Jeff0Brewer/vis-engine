#include "catch.hpp"
#include "../include/GLShader.h"

TEST_CASE("Reading invalid file returns empty string", "[readFile]") {
    std::string empty = "";
    REQUIRE_THROWS(readFile(""));
}

TEST_CASE("Shaders can be read from file and loaded", "[readFile][loadShader]") {
    const char *path = "./tests/shaders/testVert.glsl";
    std::string shaderString = readFile(path);
    REQUIRE(shaderString.length() > 0);

    SECTION("Compile valid shader from string") {
        const char *shaderSource = shaderString.c_str();
        REQUIRE_NOTHROW(loadShader(shaderSource, GL_VERTEX_SHADER));
    }
}

TEST_CASE("Program loaded with valid shaders links properly", "[loadProgram]") {
    REQUIRE_NOTHROW(loadProgram("./tests/shaders/testVert.glsl", "./tests/shaders/testFrag.glsl"));
}
