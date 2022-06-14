#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include <math.h>

#include "../src/GLMat.cpp"

TEST_CASE("Normalized vector is of length 1", "[normalize]") {
    float v[3] = {1.0f, 2.0f, -4.0f};
    normalize(v);
    double length = sqrt(v[0]*v[0] + v[1]*v[1] + v[2]*v[2]);

    REQUIRE(length == Approx(1.0));
}
