// UIInitializer.h
#pragma once

#include <map>
#include <string>

#include "Squareline-UI/ui.h"

// Forward declaration of global UI objects
extern lv_obj_t *ui_Slider_Extract;
extern lv_obj_t *ui_Slider_Fill;
extern lv_obj_t *ui_Fill_Capacity_Number_2;
extern lv_obj_t *ui_Fill_Capacity_Number_1;
extern lv_obj_t *ui_Flow_Rate_Number;;
extern lv_obj_t *ui_Battery_Voltage_Number;
extern lv_obj_t *ui_Oil_Temp_Number;
extern lv_obj_t *ui_Amount_Filled_Number;
extern lv_obj_t *ui_Amount_Extracted_Number;
extern lv_obj_t *ui_ETA_Time;
extern lv_obj_t *ui_Run_Time;

class UIInitializer {
 public:
  void initialize(std::map<std::string, lv_obj_t *> &elements);
};
