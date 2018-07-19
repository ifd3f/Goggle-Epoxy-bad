#pragma once

#include <exception>


namespace epoxy {
    namespace exception {

        class I2CConnectionException : public std::exception {
            char addr;
        public:
            I2CConnectionException(char addr);
            const char* what() const throw() override;
        };
    }  
} 
