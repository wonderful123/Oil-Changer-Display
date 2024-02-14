// UIManager.cpp

#include <iomanip>  // For std::setprecision
#include <sstream>  // For std::stringstream

#include "DataTracker.h"
#include "Logger.h"
#include "UIManager.h"

UIManager::UIManager(std::shared_ptr<DataTracker> dataTracker)
    : _dataTracker(dataTracker) {}

// Maps all elements defined the UIInitializer
void UIManager::setupUI() {
  UIInitializer initializer;
  initializer.initialize(uiElements);
}

void UIManager::initialize() {
  setupUI();

  // Subscribe to DataTracker changes
  subscribeToDataTracker("AmountFilled", &UIManager::onFillExtractAmountChange);
  subscribeToDataTracker("AmountExtracted",
                         &UIManager::onFillExtractAmountChange);
  subscribeToDataTracker("FillCapacity", &UIManager::onFillCapacityChange);
  subscribeToDataTracker("BatteryVoltage",
                         &UIManager::onGenericFloatDataChange);
  subscribeToDataTracker("OilTemp", &UIManager::onGenericFloatDataChange);
  subscribeToDataTracker("FillRate", &UIManager::onFlowRateExtractChange);
  subscribeToDataTracker("ExtractRate", &UIManager::onFlowRateFillChange);
  LOG_INFO("UIManager initialized");
}

void UIManager::registerElement(const std::string& dataKey, lv_obj_t* element) {
  uiElements[dataKey] = element;
}

void UIManager::onGenericFloatDataChange(const std::string& dataKey,
                                         const std::string& value,
                                         int precision) {
  auto formattedValue = floatStringToCString(value, precision);

  // Find the corresponding UI element and update it
  auto uiElementIter = uiElements.find(dataKey);
  if (uiElementIter != uiElements.end()) {
    lv_label_set_text(uiElementIter->second, formattedValue);
  }
}

void UIManager::onFillCapacityChange(const std::string& key,
                                     const std::string& value) {
  auto text = floatStringToCString(value);
  lv_label_set_text(uiElements["FillCapacityNumber1"], text);
  lv_label_set_text(uiElements["FillCapacityNumber2"], text);
}

void UIManager::onFlowRateExtractChange(const std::string& key,
                                        const std::string& value) {
  // Assuming the same UI element is updated for both extract and fill flow
  // rates
  auto formattedValue = floatStringToCString(value);
  lv_label_set_text(uiElements["FlowRate"], formattedValue);
}

void UIManager::onFlowRateFillChange(const std::string& key,
                                     const std::string& value) {
  auto formattedValue = floatStringToCString(value);
  lv_label_set_text(uiElements["FlowRate"], formattedValue);
}

void UIManager::onFillExtractAmountChange(const std::string& key,
                                          const std::string& value) {
  std::string fillCapacity = _dataTracker->getData("FillCapacity");
  int sliderValue = calculateSliderValue(value, fillCapacity);
  std::string sliderElementKey =
      (key == "AmountFilled") ? "SliderFill" : "SliderExtract";
  if (uiElements.find(sliderElementKey) != uiElements.end()) {
    lv_slider_set_value(uiElements[sliderElementKey], sliderValue, LV_ANIM_OFF);
  }

  lv_label_set_text(uiElements[key], floatStringToCString(value));
}

int UIManager::calculateSliderValue(const std::string& fillAmountStr,
                                    const std::string& fillCapacityStr) {
  double fillAmount = std::stod(fillAmountStr);
  double fillCapacity = std::stod(fillCapacityStr);
  double percentage = (fillAmount / fillCapacity) * 100.0;
  return static_cast<int>(percentage * 10);  // Adjusting to 0-1000 range
}

void UIManager::subscribeToDataTracker(
    const std::string& key,
    void (UIManager::*memberFunction)(const std::string&, const std::string&)) {
  _dataTracker->subscribe(
      key, [this, memberFunction](const std::string& k, const std::string& v) {
        (this->*memberFunction)(k, v);
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

const char* UIManager::floatStringToCString(const std::string& value,
                                            int precision) {
  static char cString[6];  // 5 characters + null terminator
  float floatValue = std::stof(value);
  std::snprintf(cString, sizeof(cString), "%.*f", precision, floatValue);
  return cString;
}
