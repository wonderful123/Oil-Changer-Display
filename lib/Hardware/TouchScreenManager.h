// TouchScreenManager.h
#pragma once

#include <ArduinoJson.h>
#include <Arduino_GFX_Library.h>
#include <lvgl.h>

#include <memory>

class TouchScreen;

class TouchScreenManager {
 public:
  TouchScreenManager(const JsonObject& touchConfig,
                     Arduino_RGB_Display* gfxContext);
  void readTouchScreen(lv_indev_drv_t* indev_driver, lv_indev_data_t* data);

 private:
  std::shared_ptr<TouchScreen> _touchScreen;
};