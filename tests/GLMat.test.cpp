#include "catch.hpp"
#include "../include/GLMat.h"

#include <math.h>

TEST_CASE("Cross product of parallel vectors is 0", "[cross]") {
    float a[3] = {1.0f, 0.5f, -0.1f};
    float b[3] = {10.0f, 5.0f, -1.0f};
    float res[3] = {};
    cross(a, b, res);
    for(int i = 0; i < 3; i++) {
        REQUIRE(res[i] == 0);
    }
}

TEST_CASE("Cross product of opposite vectors is 0", "[cross]") {
    float a[3] = {1.0f, 1.0f, 1.0f};
    float b[3] = {-1.0f, -1.0f, -1.0f};
    float res[3] = {};
    cross(a, b, res);
    for(int i = 0; i < 3; i++) {
        REQUIRE(res[i] == 0);
    }
}

TEST_CASE("Normalized vector is of length 1", "[normalize]") {
    float v[3] = {1.0f, 2.0f, -4.0f};
    normalize(v);
    double length = sqrt(v[0]*v[0] + v[1]*v[1] + v[2]*v[2]);

    REQUIRE(length == Approx(1.0));
}

TEST_CASE("Copied matrix is identical", "[copyMat4]") {
    float mat[16] = {0.2f, 0.7f, 0.8f, 0.3f, 0.2f, 0.7f, 0.2f, 0.9f, 0.3f, 0.2f, 0.9f, 0.3f, 0.2f, 1.0f, 0.2f, 0.0f};
    float copy[16] = {};
    copyMat4(mat, copy);
    for(int i = 0; i < 16; i++) {
        REQUIRE(mat[i] == copy[i]);
    }
}

TEST_CASE("Verify identity matrix", "[setIdentityMatrix]") {
    float mat[16] = {};
    setIdentityMatrix(mat);
    for(int i = 0; i < 4; i++) {
        int off = i*4;
        for(int j = 0; j < 4; j++) {
            if (i == j) {
                REQUIRE(mat[off+j] == 1.0f);
            }
            else {
                REQUIRE(mat[off+j] == 0.0f);
            }
        }
    }
}

TEST_CASE("Matrix multiplication with identity is unchanged", "[multiplyMat4]") {
    float id[16] = {
        1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    };
    float mat[16] = {
        0.3f, 0.7f, 0.9f, 0.4f, 
        0.4f, 0.7f, 0.7f, 0.0f, 
        0.9f, 0.4f, 0.8f, 0.3f, 
        0.6f, 0.5f, 0.8f, 0.6f
    };
    float copy[16] = {};
    for (int i = 0; i < 16; i++) {
        copy[i] = mat[i];
    }
    float res[16] = {};
    multiplyMat4(mat, id, res);

    for(int i = 0; i < 16; i++) {
        REQUIRE(res[i] == copy[i]);
    }
}
