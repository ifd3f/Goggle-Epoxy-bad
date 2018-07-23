#include <iostream>
#include <Eigen/Geometry>
extern "C" {
#include <cairo.h>
}

#include "context.hpp"

int main(int argc, const char *argv[]) {
    epoxy::Context ctx;
    ctx.run();
    return 0;
}
