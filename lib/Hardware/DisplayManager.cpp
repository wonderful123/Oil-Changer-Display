// DisplayManager.cpp
#include "DisplayManager.h"

#include <Arduino.h>

#include <functional>

#include "ConfigManager.h"
#include "Logger.h"
#include "TouchScreenManager.h"

Arduino_RGB_Display* DisplayManager::_gfxContext =
    nullptr;  // Initialize static member

void DisplayManager::initialize() {
  ConfigManager configManager;
  if (!configManager.loadConfig("/UIHardwareConfig.json", "r")) {
    Logger::error("Failed to load configuration, using default settings.");
  }

  initializeDisplay(configManager.getDisplayConfig());
  initializeTouchScreen(configManager.getTouchConfig());
  initializeLVGL(configManager.getDisplayConfig());

  ui_init();
  _ui_slider_set_property(ui_Slider_Extract, _UI_SLIDER_PROPERTY_VALUE, 100);
  _ui_slider_set_property(ui_Slider_Fill, _UI_SLIDER_PROPERTY_VALUE, 0);
}

void DisplayManager::update() {
  lv_timer_handler();  // GUI update
}

void DisplayManager::initializeDisplay(const JsonObject& displayConfig) {
  // Check if all necessary display configuration values are present
  if (!displayConfig.containsKey("width") ||
      !displayConfig.containsKey("height") ||
      !displayConfig.containsKey("dePin") ||
      !displayConfig.containsKey("vsyncPin") ||
      !displayConfig.containsKey("hsyncPin") ||
      !displayConfig.containsKey("pclkPin") ||
      !displayConfig.containsKey("rBusPins") ||
      !displayConfig.containsKey("gBusPins") ||
      !displayConfig.containsKey("bBusPins") ||
      !displayConfig.containsKey("hsyncPolarity") ||
      !displayConfig.containsKey("hsyncFrontPorch") ||
      !displayConfig.containsKey("hsyncPulseWidth") ||
      !displayConfig.containsKey("hsyncBackPorch") ||
      !displayConfig.containsKey("vsyncPolarity") ||
      !displayConfig.containsKey("vsyncFrontPorch") ||
      !displayConfig.containsKey("vsyncPulseWidth") ||
      !displayConfig.containsKey("vsyncBackPorch") ||
      !displayConfig.containsKey("pclkActiveNeg") ||
      !displayConfig.containsKey("speedHz") ||
      !displayConfig.containsKey("backlightPin")) {
    Logger::error("[ConfigManager] Missing display configuration keys");
    return;  // Return early if configuration is incomplete
  }

  // Initialize the display bus object with parameters from the
  // configuration
  _rgbPanel = new Arduino_ESP32RGBPanel(
      displayConfig["dePin"], displayConfig["vsyncPin"],
      displayConfig["hsyncPin"], displayConfig["pclkPin"],
      displayConfig["rBusPins"][0], displayConfig["rBusPins"][1],
      displayConfig["rBusPins"][2], displayConfig["rBusPins"][3],
      displayConfig["rBusPins"][4], displayConfig["gBusPins"][0],
      displayConfig["gBusPins"][1], displayConfig["gBusPins"][2],
      displayConfig["gBusPins"][3], displayConfig["gBusPins"][4],
      displayConfig["gBusPins"][5], displayConfig["bBusPins"][0],
      displayConfig["bBusPins"][1], displayConfig["bBusPins"][2],
      displayConfig["bBusPins"][3], displayConfig["bBusPins"][4],
      displayConfig["hsyncPolarity"], displayConfig["hsyncFrontPorch"],
      displayConfig["hsyncPulseWidth"], displayConfig["hsyncBackPorch"],
      displayConfig["vsyncPolarity"], displayConfig["vsyncFrontPorch"],
      displayConfig["vsyncPulseWidth"], displayConfig["vsyncBackPorch"],
      displayConfig["pclkActiveNeg"], displayConfig["speedHz"]);

  // Create the display driver object
  _gfxContext = new Arduino_RGB_Display(displayConfig["width"],
                                        displayConfig["height"], _rgbPanel);

  if (_gfxContext == nullptr) {
    Logger::error("[DisplayManager] Failed to allocate memory for _gfxContext");
    return;
  }

  _gfxContext->begin();
  _gfxContext->fillScreen(BLACK);

  Logger::info("[DisplayManager] Display panel driver created");
}

void DisplayManager::initializeLVGL(const JsonObject& displayConfig) {
  // LVGL initialization
  lv_init();
  // Allocate the buffer in PSRAM
  _buffer = static_cast<lv_color_t*>(
      ps_malloc(doubleBufferSize * sizeof(lv_color_t)));

  lv_disp_draw_buf_init(&_drawBuffer, _buffer, NULL,
                        displayConfig["width"].as<int>() * displayConfig["height"].as<int>());
  // LVGL display driver initialization
  static lv_disp_drv_t disp_drv;
  lv_disp_drv_init(&disp_drv);
  disp_drv.hor_res = displayConfig["width"].as<uint16_t>();
  disp_drv.ver_res = displayConfig["height"].as<uint16_t>();
  disp_drv.flush_cb = disp_flush;
  disp_drv.draw_buf = &_drawBuffer;
  lv_disp_drv_register(&disp_drv);

  // Backlight control
  int backlightPin = displayConfig["backlightPin"];
  pinMode(backlightPin, OUTPUT);
  digitalWrite(backlightPin, HIGH);  // Turn on the backlight

  Logger::info("[DisplayManager] LVGL initialized");
}

void DisplayManager::disp_flush(lv_disp_drv_t* disp_drv, const lv_area_t* area,
                                lv_color_t* color_p) {
  uint32_t w = (area->x2 - area->x1 + 1);
  uint32_t h = (area->y2 - area->y1 + 1);

#if (LV_COLOR_16_SWAP == 0) /* LV_COLOR_16_SWAP is defined in lv_conf.h */
  _gfxContext->draw16bitRGBBitmap(area->x1, area->y1, (uint16_t*)&color_p->full,
                                  w, h);
#else
  _gfxContext->draw16bitBeRGBBitmap(area->x1, area->y1,
                                    (uint16_t*)&color_p->full, w, h);
#endif

  lv_disp_flush_ready(disp_drv);
}

void DisplayManager::initializeTouchScreen(
    const JsonObject& touchScreenConfig) {
  if (!touchScreenConfig) {
    Logger::error("[DisplayManager] Touch screen config not loaded");
    return;
  } else if (_gfxContext == nullptr) {
    Logger::error("[DisplayManager] LVGL gfxContext not initialized");
    return;
  } else {
    _touchScreenManager =
        std::make_shared<TouchScreenManager>(touchScreenConfig, _gfxContext);
  }
}