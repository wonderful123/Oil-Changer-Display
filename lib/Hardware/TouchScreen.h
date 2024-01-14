// TouchScreen.h
#pragma once

#include <Arduino_GFX_Library.h>
#include <SPI.h>
#include <XPT2046_Touchscreen.h>

class TouchScreen {
 public:
  // Constructor: Initialize with the display context
  explicit TouchScreen(Arduino_RGB_Display *gfxContext)
      : ts(TOUCH_XPT2046_CS, TOUCH_XPT2046_INT), gfx(gfxContext) {
    ts.setRotation(TOUCH_XPT2046_ROTATION);
  }

  // Initialize the touch screen
  void initialize() {
    SPI.begin(TOUCH_XPT2046_SCK, TOUCH_XPT2046_MISO, TOUCH_XPT2046_MOSI,
              TOUCH_XPT2046_CS);
    ts.begin();
  }

  // Check if the screen is touched
  bool isTouched() {
    if (ts.touched()) {
      TS_Point p = ts.getPoint();
      updateTouchCoordinates(p);
      return true;
    }
    return false;
  }

  // Get the last touch coordinates
  void getLastTouch(int &x, int &y) const {
    x = touch_last_x;
    y = touch_last_y;
  }

 private:
  // Update the last touch coordinates
  void updateTouchCoordinates(const TS_Point &p) {
#if defined(TOUCH_SWAP_XY)
    touch_last_x = map(p.y, TOUCH_MAP_X1, TOUCH_MAP_X2, 0, gfx->width() - 1);
    touch_last_y = map(p.x, TOUCH_MAP_Y1, TOUCH_MAP_Y2, 0, gfx->height() - 1);
#else
    touch_last_x = map(p.x, TOUCH_MAP_X1, TOUCH_MAP_X2, 0, gfx->width() - 1);
    touch_last_y = map(p.y, TOUCH_MAP_Y1, TOUCH_MAP_Y2, 0, gfx->height() - 1);
#endif
  }

  Arduino_RGB_Display *gfx;
  XPT2046_Touchscreen ts;
  mutable int touch_last_x = 0;
  mutable int touch_last_y = 0;

  // Touch configuration constants
  static constexpr int TOUCH_XPT2046_SCK = 12;
  static constexpr int TOUCH_XPT2046_MISO = 13;
  static constexpr int TOUCH_XPT2046_MOSI = 11;
  static constexpr int TOUCH_XPT2046_CS = 38;
  static constexpr int TOUCH_XPT2046_INT = 18;
  static constexpr int TOUCH_XPT2046_ROTATION = 0;
  static constexpr int TOUCH_MAP_X1 = 4000;
  static constexpr int TOUCH_MAP_X2 = 100;
  static constexpr int TOUCH_MAP_Y1 = 100;
  static constexpr int TOUCH_MAP_Y2 = 4000;
};
