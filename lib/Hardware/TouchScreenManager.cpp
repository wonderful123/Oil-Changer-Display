// TouchScreenManager.cpp
#include "TouchScreenManager.h"

#include "TouchScreen.h"

TouchScreenManager::TouchScreenManager(JsonDocument touchConfig,
                                       Arduino_RGB_Display* gfxContext) {
  _touchScreen = std::make_shared<TouchScreen>(gfxContext);
}

void TouchScreenManager::readTouchScreen(lv_indev_drv_t* indev_driver,
                                         lv_indev_data_t* data) {
  if (_touchScreen->isTouched()) {
    data->state = LV_INDEV_STATE_PR;
    // Set the coordinates of the touch
    int touchX, touchY;
    _touchScreen->getLastTouch(touchX, touchY);
    data->point.x = touchX;
    data->point.y = touchY;
    Serial.println(
        ("[Touch] X: " + String(touchX) + " Y: " + String(touchY)).c_str());
  } else
    data->state = LV_INDEV_STATE_REL;
}