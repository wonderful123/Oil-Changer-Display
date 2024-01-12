// The LVGL_Arduino demo from lvgl v8 modified to run on the
// Sunton ESP32-4827S043C (480 * 272 TFT LED display) board.

// There has been discussion on the display timing parameter values
// to use for horizontal and vertical SYNC, FP, PW and BP to prevent
// flickering and tearing.
// Refer to: https://github.com/moononournation/Arduino_GFX/discussions/291
//
// The "best" values seem to differ depending on the versions of the
// arduino-esp32 core, LVGL, and Arduino_GFX_Library used.
//
// The values in this sketch work when using:
//  - Arduino IDE v 2.1.1
//  - arduino-esp32 core v2.0.11
//  - lvgl at version 8.3.7
//  - GFX Library for Arduino at version 1.3.7
//  - TAMC_GT911 at version 1.0.2
//
// Refer also to:
// https://forum.lvgl.io/t/how-to-setup-the-lvgl-library-for-esp32-s3-wroom-1-with-tft-display-800-480/12302/11?u=xylopyrographer
//
// For the touch panel: the ESP32-4827S043C does not have a connection to
// the INT pin of the GT911 touch panel controller (more on this following).
// However the TAMC_GT911 library requires that an INT pin number be provided.
// Pin 18 can be used but so doing prevents that pin from being used on the
// I/O expansion connectors for other purposes.
//
// The other option is to provide an out of range value for INT such as 99
// or, as is done below, -1. This will compile but a run time error occurs
// (can be seen on the serial monitor). This does not seem to affect anything
// and allows GPIO 18 to be used for other purposes, but knowingly generating
// errors in code should be avoided.
//
// The real solution would be to modify the TAMC_GT911 library so "-1" as
// the INT parameter means "don't use any GPIO pin for INT". Or you could
// modify the TAMC_GT911.cpp library file to comment out the lines where the
// INT pin is assigned and toggled (as I did). Note that the interrupt
// handling code in the TAMC_GT911.cpp file has already ben commented out so
// assigning a GPIPO pin for that purpose in the library is moot.
//
// FWIW, the lvgl library only polls the touch panel so a touch pad interrupt
// handler function is not needed.
//
// Back to the ESP32-4827S043C board. Out of the box there is no connection
// to the GT911 INT pin. But, if you install a jumper at the location of R17
// that would connect INT to GPIO 18. If you don't need that pin for I/O
// expansion and you use a library other than TAMC_GT911 that supports touch
// panel interrupts that is an option.
//
// Side note: By changing DIS_WIDTH_PX and DIS_HEIGHT_PX and the values for
// display timing (all the #define values for the horizontal and vertical SYNC,
// FP, PW and BP), this sketch should work on the ESP32-8048S043C (same board
// with an 800 * 480 IPS LED panel and capacitive touch panel). Be aware that
// different hardware revisions of that board use different pin assignments
// for the touch panel and the back light enable so check that too.

// An interesting resource for these boards is:
//      https://macsbug.wordpress.com/2022/11/29/esp32-8048s043/

#include <Arduino.h>
#include <Arduino_GFX_Library.h>
#include <demos/lv_demos.h>
#include <lvgl.h>

#include <memory>
#include <string>

#include "ConfigManager.h"
#include "TouchScreen.h"
#include "ui.h"

// Assuming SPIFFS is initialized earlier in your code
ConfigManager configManager("/config.json");

#define LV_CONF_INCLUDE_SIMPLE 1
#define LV_USE_DEMO_WIDGETS 1
//=================== Start Display Config ====================
// Set the parameters below to match those of the display.
// The ones below are specific to the TFT LCD display of the ESP32-4827S043C
// and using the versions of the libraries and arduino-esp32 core noted above.
#define DIS_WIDTH_PX 480  /* width of the display, pixels */
#define DIS_HEIGHT_PX 272 /* height of the display, pixels */
#define DIS_DE 40         /* GPIO pin connected to DE */
#define DIS_VSYNC 41      /* GPIO pin connected to VSYNC */
#define DIS_HSYNC 39      /* GPIO pin connected to HSYNC */
#define DIS_PCLK 42       /* GPIO pin connected to PCLK */
#define DIS_R_BUS \
  45, 48, 47, 21, \
      14 /* R0...R4: GPIO pins connected to the RED colour channel */
#define DIS_G_BUS  \
  5, 6, 7, 15, 16, \
      4 /* G0...G5: GPIO pins connected to the GREEN colour channel */
#define DIS_B_BUS \
  8, 3, 46, 9, 1 /* B0...B4: GPIO pins connected to the BLUE colour channel */

#define DIS_HS_POL 0 /* hsync polarity */
#define DIS_HS_FP 1  /* hsync front_porch time, ms */
#define DIS_HS_PW 1  /* hsync pulse_width time, ms*/
#define DIS_HS_BP 43 /* hsync back_porch time, ms */

#define DIS_VS_POL 0 /* vsync polarity */
#define DIS_VS_FP 3  /* vsync front_porch time, ms */
#define DIS_VS_PW 1  /* vsync pulse_width time,  ms */
#define DIS_VS_BP 12 /* vsync back_porch time, ms */

#define DIS_PC_A_N 1      /* pclk active neg */
#define DIS_SPEED 9000000 /* prefer speed, Hz */

#define DIS_BL 2 /* GPIO pin connected to the display backlight */
//=================== End Display Config ====================

//=================== Start Touch Config ====================
// Set the parameters below to match those of the display touch panel
// The ones below are specific to the capacitive touch panel of the
// ESP32-4827S043C
#define TOUCH_SDA 19 /* GPIO pin for SDA of the I2C bus */
#define TOUCH_SCL 20 /* GPIO pin for SCL of the I2C bus */
#define TOUCH_INT \
  -1 /* GPIO pin connected to touch panel INT. See the note above. */
#define TOUCH_RST 38 /* GPIO pin connected to touch panel RST */

#define TOUCH_ROTATION ROTATION_NORMAL /* touch panel orientation */
//=================== End Touch Config ====================

static lv_disp_draw_buf_t draw_buf;  // global needed for the lvgl routines
static lv_color_t
    buf[DIS_WIDTH_PX * 10];  // global needed for the lvgl routines

// create a display bus object
Arduino_ESP32RGBPanel* rgbpanel = new Arduino_ESP32RGBPanel(
    DIS_DE, DIS_VSYNC, DIS_HSYNC, DIS_PCLK, DIS_R_BUS, DIS_G_BUS, DIS_B_BUS,
    DIS_HS_POL, DIS_HS_FP, DIS_HS_PW, DIS_HS_BP, DIS_VS_POL, DIS_VS_FP,
    DIS_VS_PW, DIS_VS_BP, DIS_PC_A_N, DIS_SPEED);

// create a display driver object
Arduino_RGB_Display* gfx =
    new Arduino_RGB_Display(DIS_WIDTH_PX, DIS_HEIGHT_PX, rgbpanel);

// create a touch panel driver object
std::shared_ptr<TouchScreen> touchScreen = std::make_shared<TouchScreen>(gfx);

#if LV_USE_LOG != 0 /* LV_USE_LOG is defined in lv_conf.h */
// lvgl debugging serial monitor print function
void my_print(const char* buf) {
  Serial.printf(buf);
  Serial.flush();
}
#endif

// *********** Display drawing function for lvgl ***********
//  - specific to the display panel and the driver (graphics) library being used
void my_disp_flush(lv_disp_drv_t* disp, const lv_area_t* area,
                   lv_color_t* color_p) {
  uint32_t w = (area->x2 - area->x1 + 1);
  uint32_t h = (area->y2 - area->y1 + 1);

#if (LV_COLOR_16_SWAP == 0) /* LV_COLOR_16_SWAP is defined in lv_conf.h */
  gfx->draw16bitRGBBitmap(area->x1, area->y1, (uint16_t*)&color_p->full, w, h);
#else
  gfx->draw16bitBeRGBBitmap(area->x1, area->y1, (uint16_t*)&color_p->full, w,
                            h);
#endif

  lv_disp_flush_ready(disp);
}
// *********** End display drawing function for lvgl ***********

// *********** Touch panel functions for lvgl ***********
//  - specific to the touch panel and touch panel driver library being used
//  - these are specific to the GT911 driver used for the ESP32-4827S043C
//    capacitive touch screen

void readTouchScreen(lv_indev_drv_t* indev_driver, lv_indev_data_t* data) {
  if (touchScreen->isTouched()) {
    data->state = LV_INDEV_STATE_PR;
    // Set the coordinates of the touch

    int touchX, touchY;
    touchScreen->getLastTouch(touchX, touchY);
    data->point.x = touchX;
    data->point.y = touchY;
    Serial.println(
        ("[Touch] X: " + String(touchX) + " Y: " + String(touchY)).c_str());
  } else
    data->state = LV_INDEV_STATE_REL;
}
// *********** End Touch panel functions for lvgl ***********

void setup() {
  Serial.begin(115200);
  delay(250);

  gfx->begin();
  gfx->fillScreen(BLACK);

  touchScreen->initialize();

  // ******* Start all the setup and initilization needed for lvgl ******
  lv_init();

#if LV_USE_LOG != \
    0 /* LV_USE_LOG is the debugging print enable, defined in lv_conf.h */
  lv_log_register_print_cb(
      my_print);  // register the print function for debugging
#endif

  lv_disp_draw_buf_init(&draw_buf, buf, NULL, DIS_WIDTH_PX * 10);

  // Initialize the display - for lvgl
  static lv_disp_drv_t disp_drv;
  lv_disp_drv_init(&disp_drv);

  // Ensure the following lines match the display resolution
  disp_drv.hor_res = DIS_WIDTH_PX;
  disp_drv.ver_res = DIS_HEIGHT_PX;

  disp_drv.flush_cb = my_disp_flush;
  disp_drv.draw_buf = &draw_buf;
  lv_disp_drv_register(&disp_drv);

  // Initialize the (dummy) input device driver
  static lv_indev_drv_t indev_drv;
  lv_indev_drv_init(&indev_drv);  //  Descriptor of a input device driver
  indev_drv.type =
      LV_INDEV_TYPE_POINTER;            //  Touch pad is a pointer-like device
  indev_drv.read_cb = readTouchScreen;  //  Set your driver function
  lv_indev_drv_register(
      &indev_drv);  //  Finally register the driver
  // *********** End all the setup and initilization needed for lvgl ***********

#ifdef DIS_BL
                    // Some hardware versions of the ESP32-8048S043 don't allow
                    // for baclklight control
  // (it's hard wired to always on). Comment out the #define DIS_BL line above
  // if this applies to your board. Otherwise... turn on the display backlight
  pinMode(DIS_BL, OUTPUT);
  digitalWrite(DIS_BL, HIGH);
#endif

  Serial.println("\r\n");
  Serial.println("Everything should now be initilized!");

  ui_init();
  _ui_slider_set_property(ui_Slider_Extract, _UI_SLIDER_PROPERTY_VALUE, 100);
  _ui_slider_set_property(ui_Slider_Fill, _UI_SLIDER_PROPERTY_VALUE, 0);

  Serial.println("Exiting setup()...\r\n");
}

// Check for touch and print the coordinates
void checkTouch() {
  int touchX, touchY;
  if (touchScreen->isTouched()) {
    touchScreen->getLastTouch(touchX, touchY);
    Serial.print("Touch detected at: ");
    Serial.print(touchX);
    Serial.print(", ");
    Serial.println(touchY);
  }
}

void loop() {
  lv_timer_handler();  // GUI update
  checkTouch();
}
