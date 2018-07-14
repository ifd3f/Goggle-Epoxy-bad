#include "motion.hpp"

#include <Eigen/Geometry>

using namespace epoxy::motion;

Eigen::Quaterniond Gyro::getDeltaQuaternion(double dt) {
    Eigen::Quaterniond q(1, getX() * dt / 2, getY() * dt / 2, getZ() * dt / 2);
    q.normalize();
    return q;
}

Eigen::Vector3d VectorOutput::getVector() {
    return Eigen::Vector3d(getX(), getY(), getZ());
}

Eigen::Quaterniond getOrientation(Eigen::Vector3d down, Eigen::Vector3d north) {
    down.normalize();
    north.normalize();
    Eigen::Vector3d west = down.cross(north);
    west.normalize();

    Eigen::Matrix3d real_to_funky(3, 3);
    real_to_funky << north, west, -down;
    auto funky_to_real = real_to_funky.inverse();

    return Eigen::Quaterniond(funky_to_real);
}

OrientationIntegrator::OrientationIntegrator(Gyro *gyro, VectorOutput *accel, VectorOutput *mag, double compensation):
    gyro(gyro), accel(accel), mag(mag), compensation(compensation) {

}

void OrientationIntegrator::calibrate() {

}

void OrientationIntegrator::update(double dt) {
    auto dr = gyro->getDeltaQuaternion(dt);
    auto a_hat = getOrientation(accel->getVector(), mag->getVector());

    state = (state * dr).slerp(compensation, a_hat);
}