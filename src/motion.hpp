#include <Eigen/Geometry>

class Gyro {
    public:
        virtual double getXVel() = 0;
        virtual double getYVel() = 0;
        virtual double getZVel() = 0;

        double getDeltaQuaternion(double dt);        
};