#include "exception.hpp"

#include <string>
#include <sstream>

using namespace epoxy::exception;

I2CConnectionException::I2CConnectionException(char addr): addr(addr) {

}

const char* I2CConnectionException::what() const throw() {
    std::ostringstream os;
    os << "Could not connect to I2C device at " << std::hex << addr;
    return os.str().c_str();
}