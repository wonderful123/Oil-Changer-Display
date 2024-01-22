// UIManager.cpp

#include "UIManager.h"

#include <iomanip>  // For std::setprecision
#include <sstream>  // For std::stringstream

#include "DataTracker.h"
#include "Logger.h"

UIManager::UIManager(std::shared_ptr<DataTracker> dataTracker)
    : _dataTracker(dataTracker) {
  setupUI();
}

// Maps all elements defined the UIInitializer
void UIManager::setupUI() {
  UIInitializer initializer;
  initializer.initialize(uiElements);
}

void UIManager::initialize() {
  // Subscribe to DataTracker changes
  subscribeToDataTracker("FillCapacity", &UIManager::onFillCapacityChange);
  subscribeToDataTracker("AmountFilled", &UIManager::onFillExtractAmountChange);
  subscribeToDataTracker("AmountExtracted",
                         &UIManager::onFillExtractAmountChange);
  subscribeToDataTracker("Voltage", &UIManager::onGenericFloatDataChange);
  subscribeToDataTracker("OilTemperature",
                         &UIManager::onGenericFloatDataChange);
  subscribeToDataTracker("FlowRateExtract",
                         &UIManager::onFlowRateExtractChange);
  subscribeToDataTracker("FlowRateFill", &UIManager::onFlowRateFillChange);
}

void UIManager::registerElement(const std::string& dataKey, lv_obj_t* element) {
  uiElements[dataKey] = element;
}

void UIManager::onGenericFloatDataChange(const std::string& dataKey,
                                         const std::string& value,
                                         int precision) {
  auto formattedValue = floatToString(value, precision);

  // Find the corresponding UI element and update it
  auto uiElementIter = uiElements.find(dataKey);
  if (uiElementIter != uiElements.end()) {
    lv_label_set_text(uiElementIter->second, formattedValue.c_str());
  }
}

void UIManager::onFillCapacityChange(const std::string& key,
                                     const std::string& value) {
  lv_label_set_text(uiElements["ui_Fill_Capacity_Number_1"],
                    floatToString(value).c_str());
  lv_label_set_text(uiElements["ui_Fill_Capacity_Number_2"],
                    floatToString(value).c_str());
}

void UIManager::onFlowRateExtractChange(const std::string& key,
                                        const std::string& value) {
  // Assuming the same UI element is updated for both extract and fill flow
  // rates
  auto formattedValue = floatToString(value);
  if (uiElements.find("FlowRateNumber") != uiElements.end()) {
    lv_label_set_text(uiElements["FlowRateNumber"], formattedValue.c_str());
  }
}

void UIManager::onFlowRateFillChange(const std::string& key,
                                     const std::string& value) {
  // Similar handling as for onFlowRateExtractChange
  auto formattedValue = floatToString(value);
  if (uiElements.find("FlowRateNumber") != uiElements.end()) {
    lv_label_set_text(uiElements["FlowRateNumber"], formattedValue.c_str());
  }
}

void UIManager::onFillExtractAmountChange(const std::string& key,
                                          const std::string& value) {
  float fillCapacity = _dataTracker->getFillCapacity();
  int sliderValue =
      (fillCapacity != 0.0f) ? calculateSliderValue(value, fillCapacity) : 0;

  std::string sliderElementKey =
      (key == "AmountFilled") ? "ui_Slider_Fill" : "ui_Slider_Extract";
  if (uiElements.find(sliderElementKey) != uiElements.end()) {
    lv_slider_set_value(uiElements[sliderElementKey], sliderValue, LV_ANIM_OFF);
  }
}

int UIManager::calculateSliderValue(const std::string& fillAmountStr,
                                    double fillCapacity) {
  double fillAmount = std::stod(fillAmountStr);
  double percentage = (fillAmount / fillCapacity) * 100.0;
  return static_cast<int>(percentage * 10);  // Adjusting to 0-1000 range
}
#include <cerrno>
#include <iostream>

#include "Logger.h"

void UIManager::subscribeToDataTracker(
    const std::string& key,
    void (UIManager::*memberFunction)(const std::string&, const std::string&)) {
  _dataTracker->subscribe(key, [this, memberFunction](const std::string& k,
                                                      const std::string& v) {
    std::cout
        << "UIManager::subscribeToDataTracker - Notification received for key: "
        << k << std::endl;
    if (this) {
      std::cout << "UIManager instance is valid, calling member function"
                << std::endl;
      (this->*memberFunction)(k, v);
    } else {
      std::cerr << "UIManager instance is no longer valid" << std::endl;
    }
  });
}

void UIManager::subscribeToDataTracker(
    const std::string& key,
    void (UIManager::*memberFunction)(const std::string&, const std::string&,
                                      int)) {
  _dataTracker->subscribe(
      key, [this, memberFunction](const std::string& k, const std::string& v) {
        (this->*memberFunction)(k, v, 1);  // Default precision passed here
      });
}

std::string UIManager::floatToString(const std::string& input, int precision) {
  std::stringstream stream;
  // Convert string to float and format it
  float number = std::stof(input);
  stream << std::fixed << std::setprecision(precision) << number;
  // Convert back to string
  return stream.str();
}
