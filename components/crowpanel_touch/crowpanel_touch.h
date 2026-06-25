#include "esphome.h"

class CrowPanelTouch : public Component, public Touchscreen {
 public:
  CrowPanelTouch(esphome::i2c::I2CDevice *dev) : dev_(dev) {}

  void setup() override {
    // nothing to initialize
  }

  void loop() override {
    uint8_t buf[5];
    if (dev_->read(buf, 5) != esphome::i2c::ERROR_OK) {
      return;
    }

    // buf[0] = number of touch points (0 or 1)
    if (buf[0] == 0) {
      this->release();
      return;
    }

    // buf[1..2] = X coordinate (little endian)
    // buf[3..4] = Y coordinate (little endian)
    uint16_t x = (uint16_t)buf[1] | ((uint16_t)buf[2] << 8);
    uint16_t y = (uint16_t)buf[3] | ((uint16_t)buf[4] << 8);

    this->touch(x, y);
  }

 protected:
  esphome::i2c::I2CDevice *dev_;
};
