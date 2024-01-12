// TouchScreen.h
#pragma once

/*******************************************************************************
 * Touch libraries:
 * XPT2046: https://github.com/PaulStoffregen/XPT2046_Touchscreen.git
 ******************************************************************************/

#define TOUCH_SDA 19 /* GPIO pin for SDA of the I2C bus */
#define TOUCH_SCL 20 /* GPIO pin for SCL of the I2C bus */
#define TOUCH_INT \
  -1 /* GPIO pin connected to touch panel INT. See the note above. */
#define TOUCH_RST 38 /* GPIO pin connected to touch panel RST */

#define TOUCH_ROTATION ROTATION_NORMAL /* touch panel orientation */

#include <Arduino_GFX_Library.h>
#include <SPI.h>
#include <XPT2046_Touchscreen.h>

class TouchScreen {
 public:
  TouchScreen(Arduino_RGB_Display *gfxContext)
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
#if defined(TOUCH_SWAP_XY)
      touch_last_x = map(p.y, TOUCH_MAP_X1, TOUCH_MAP_X2, 0, gfx->width() - 1);
      touch_last_y = map(p.x, TOUCH_MAP_Y1, TOUCH_MAP_Y2, 0, gfx->height() - 1);
#else
      touch_last_x = map(p.x, TOUCH_MAP_X1, TOUCH_MAP_X2, 0, gfx->width() - 1);
      touch_last_y = map(p.y, TOUCH_MAP_Y1, TOUCH_MAP_Y2, 0, gfx->height() - 1);
#endif
      return true;
    }
    return false;
  }

  // Check if touch has a signal
  bool touchHasSignal() { return ts.tirqTouched(); }

  // Check if touch was released
  bool touchReleased() { return true; }

  // Get the last touch coordinates
  void getLastTouch(int &x, int &y) {
    x = touch_last_x;
    y = touch_last_y;
  }

 private:
  Arduino_RGB_Display *gfx;
  XPT2046_Touchscreen ts;
  int touch_last_x = 0;
  int touch_last_y = 0;

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

// Usage example
// TouchScreen touchScreen;
// touchScreen.initialize();
// if (touchScreen.isTouched()) {
//     int x, y;
//     touchScreen.getLastTouch(x, y);
//     // Do something with x, y
// }
