// DisplayManager.h
#pragma once

#include <ArduinoJson.h>
#include <Arduino_GFX_Library.h>
#include <lvgl.h>

#include <memory>

#include "ui.h"

// Forward declarations
class TouchScreenManager;

constexpr int width = 480;
constexpr int height = 272;
constexpr size_t bytesPerPixel = 2;  // 16-bit color depth

constexpr size_t bufferSize = width * height * bytesPerPixel;
constexpr size_t doubleBufferSize = bufferSize * 2;

class DisplayManager {
 public:
  void initialize();
  void update();
  static void disp_flush(lv_disp_drv_t* disp, const lv_area_t* area,
                         lv_color_t* color_p);

 private:
  std::shared_ptr<TouchScreenManager> _touchScreenManager;

  lv_disp_draw_buf_t _drawBuffer;
  // lv_color_t _buffer[BUFFER_SIZE];
  lv_color_t* _buffer;
  static Arduino_RGB_Display* _gfxContext;
  Arduino_ESP32RGBPanel* _rgbPanel;

  void initializeDisplay(const JsonObject& displayConfig);
  void initializeLVGL(const JsonObject& displayConfig);
  void initializeTouchScreen(const JsonObject& touchScreenConfig);
};