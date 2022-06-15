#include "catch.hpp"
#include "../include/GLMouse.h"

TEST_CASE("Mouse movement with no mousedown causes no rotation", "[mouseRotate]") {
    float mat[16] = {
        -7.0f, -2.5f, -7.0f, 3.1f, 
        1.3f, 8.2f, -3.8f, -3.1f, 
        7.0f, 9.9f, -9.1f, 4.8f, 
        8.8f, 8.0f, 4.9f, 6.5f
    };
    float copy[16] = {};
    for(int i = 0; i < 16; i++) {
        copy[i] = mat[i];
    }

    float up[3] = { 0.0f, 0.0f, 1.0f };
    float right[3] = { 1.0f, 0.0f, 0.0f};
    mouseRotate(0, 0, false, up, right, mat);
    mouseRotate(10, 50, false, up, right, mat);

    bool same = true;
    for (int i = 0; i < 16; i++) {
        same = same && copy[i] == mat[i];
    }
    REQUIRE(same);
}

TEST_CASE("No mouse movement with mousedown causes no rotation", "[mouseRotate]") {
    float mat[16] = {
        9.8f, 3.3f, -6.7f, -0.5f, 
        -8.6f, 8.6f, 4.8f, 6.6f, 
        -3.8f, 2.6f, -1.9f, 9.5f, 
        -0.3f, 5.2f, -5.9f, 8.2f
    };
    float copy[16] = {};
    for(int i = 0; i < 16; i++) {
        copy[i] = mat[i];
    }

    float up[3] = { 0.0f, 0.0f, 1.0f };
    float right[3] = { 1.0f, 0.0f, 0.0f};
    mouseRotate(0, 0, true, up, right, mat);
    mouseRotate(0, 0, true, up, right, mat);

    bool same = true;
    for (int i = 0; i < 16; i++) {
        same = same && copy[i] == mat[i];
    }
    REQUIRE(same);
}

TEST_CASE("mouse movement with mousedown causes rotation", "[mouseRotate]") {
    float mat[16] = {
        0.8f, -4.1f, 6.4f, -9.1f, 
        -6.8f, -0.8f, -1.2f, -4.5f, 
        -6.7f, 8.5f, -0.8f, 2.9f, 
        4.1f, -0.6f, -5.4f, -4.5f
    };
    float copy[16] = {};
    for(int i = 0; i < 16; i++) {
        copy[i] = mat[i];
    }

    float up[3] = { 0.0f, 0.0f, 1.0f };
    float right[3] = { 1.0f, 0.0f, 0.0f};
    mouseRotate(0, 0, true, up, right, mat);
    mouseRotate(10, 20, true, up, right, mat);

    bool diff = false;
    for (int i = 0; i < 16; i++) {
        diff = diff || copy[i] != mat[i];
    }
    REQUIRE(diff);
}
