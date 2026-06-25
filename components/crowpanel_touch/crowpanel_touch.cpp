#include "crowpanel_touch.h"

using namespace esphome;

CrowPanelTouch *crowpanel_touch_create(i2c::I2CDevice *dev) {
  return new CrowPanelTouch(dev);
}
