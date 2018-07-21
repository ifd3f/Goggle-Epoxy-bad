#include "hardware.hpp"


// TODO: CHANGE ADDRS AND PIN NUMBERS
Hardware::Hardware() {
    screen = new devices::SSD1306(0x30);
    acc = new devices::LSM303DLHCAcc(0x30, LSM303_ACC_8G);
    gyro = new devices::L3GD20(0x30, L3GD20_500);
    mag = new devices::LSM303DLHCMag(0x30, LSM303_MAG_81);
    encoder = new devices::GPIOQuadEncoder(ENCODER_ID, 10, 10);
    alt = new devices::MPL3115A2(0x30);
    bar = alt;
    thm = alt;
    btnH = new devices::GPIOButton(BTN_H_ID, 10);
    btnX = new devices::GPIOButton(BTN_X_ID, 10);
    btnY = new devices::GPIOButton(BTN_Y_ID, 10);
    btnZ = new devices::GPIOButton(BTN_Z_ID, 10);
}

Hardware::~Hardware() {
    delete screen;
    delete acc;
    delete mag;
    delete encoder;
    delete btnH;
    delete btnX;
    delete btnY;
    delete btnZ;
}