// UIInitializer.cpp
#include "UIInitializer.h"

void UIInitializer::initialize(std::map<std::string, lv_obj_t*>& elements) {
  elements["SliderExtract"] = ui_Slider_Extract;
  elements["SliderFill"] = ui_Slider_Fill;
  elements["FillCapacityNumber2"] = ui_Fill_Capacity_Number_2;
  elements["FillCapacityNumber1"] = ui_Fill_Capacity_Number_1;
  elements["FlowRate"] = ui_Flow_Rate_Number;
  elements["BatteryVoltage"] = ui_Battery_Voltage_Number;
  elements["OilTemp"] = ui_Oil_Temp_Number;
  elements["AmountFilled"] = ui_Amount_Filled_Number;
  elements["AmountExtracted"] = ui_Amount_Extracted_Number;
  elements["ETATime"] = ui_ETA_Time;
  elements["RunTime"] = ui_Run_Time;
}
