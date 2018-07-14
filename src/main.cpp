#include <iostream>
#include <Eigen/Geometry>

int main(int argc, const char *argv[]) {
    Eigen::Vector3d v1(1, 2, 3);
    Eigen::Vector3d v2(4,5,6);
    Eigen::Vector3d v3(7,8,9);

    Eigen::Matrix3d m;
    m << v1, v2, v3;
    std::cout << m << std::endl;
    return 0;
}
