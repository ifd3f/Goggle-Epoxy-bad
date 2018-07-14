/**
 * This library reads motion and performs sensor fusion. Axes are as follows:
 * 
 *  X: North
 *  Y: West
 *  Z: Up
 */

#pragma once

#include <Eigen/Geometry>

#include "scheduler.hpp"

using namespace epoxy;

namespace epoxy {
    namespace motion {
        using namespace epoxy::motion;

        //Eigen::Quaterniond getOrientation(Eigen::Vector3d down, Eigen::Vector3d north);

        class Gyro {
        public:
            virtual double getX() = 0;
            virtual double getY() = 0;
            virtual double getZ() = 0;

            Eigen::Quaterniond getDeltaQuaternion(double dt);        
        };

        class VectorOutput {
        public:
            virtual double getX() = 0;
            virtual double getY() = 0;
            virtual double getZ() = 0;

            Eigen::Vector3d getVector();
        };

        class OrientationIntegrator : public scheduler::Command {
            Gyro *gyro;
            VectorOutput *accel, *mag;
            Eigen::Quaterniond state;
            const double compensation;
        public:
            OrientationIntegrator(Gyro *gyro, VectorOutput *accel, VectorOutput *mag, double compensation);

            void calibrate();
            void update(int dt) override;
        };

    }
}