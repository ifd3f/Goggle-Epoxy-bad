cmake_minimum_required(VERSION 3.10.0)
project(GoggleEpoxy)

SET(CMAKE_SYSTEM_NAME Linux)
SET(CMAKE_SYSTEM_VERSION 1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pedantic -Wextra -Wno-unused-parameter -DBOOST_LOG_DYN_LINK")

set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)
#find_package(Boost 1.58.0 REQUIRED COMPONENTS date_time)

include_directories(
        ./src/
        #${Boost_INCLUDE_DIRS}
        /usr/local/include/
        /usr/include/
        /usr/include/eigen3/
        /usr/include/pango-1.0/
        /usr/include/cairo/
        /usr/include/freetype2/)

link_directories(
        /usr/local/lib/
        /usr/lib
        /usr/lib/x86_64-linux-gnu)

link_libraries(
        #${Boost_LIBRARIES}
        cairo
        pango
        freetype
        crypt
        wiringPi)

add_executable(GoggleEpoxy
        src/devices/gpiobtn.cpp
        src/devices/gpiobtn.hpp
        src/devices/l3gd20.cpp
        src/devices/l3gd20.hpp
        src/devices/lsm303.cpp
        src/devices/lsm303.hpp
        src/devices/mpl3115a2.cpp
        src/devices/mpl3115a2.hpp
        src/devices/ssd1306.cpp
        src/devices/ssd1306.hpp
        src/activity.cpp
        src/activity.hpp
        src/context.cpp
        src/context.hpp
        src/exception.cpp
        src/exception.hpp
        src/hardware.cpp
        src/hardware.hpp
        src/input.cpp
        src/input.hpp
        src/main.cpp
        src/motion.cpp
        src/motion.hpp
        src/scheduler.cpp
        src/scheduler.hpp
        src/util/util.cpp
        src/util/util.hpp
        src/weather.hpp src/activities/blank.cpp src/activities/blank.hpp src/activities/Home_Sensors.cpp src/activities/Home_Sensors.hpp src/Assets.cpp src/Assets.hpp)

add_executable(Test
        src/test.cpp
        src/devices/ssd1306.hpp
        src/devices/ssd1306.cpp)
