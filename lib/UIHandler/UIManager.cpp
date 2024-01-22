// UIManager.cpp

#include "UIManager.h"

#include "DataTracker.h"
#include "Squareline-UI/ui.h"

UIManager::UIManager(std::shared_ptr<DataTracker> dataTracker)
    : _dataTracker(dataTracker) {
  // Subscribe to DataTracker changes
  _dataTracker->subscribe(
      "FillCapacity", [this](const std::string& key, const std::string& value) {
        this->onFillCapacityChanged(key, value);
      });
  _dataTracker->subscribe(
      "AmountFilled", [this](const std::string& key, const std::string& value) {
        this->onAmountChanged(key, value);
      });
  _dataTracker->subscribe("AmountExtracted", [this](const std::string& key,
                                                    const std::string& value) {
    this->onAmountChanged(key, value);
  });
}

void UIManager::onFillCapacityChanged(const std::string& key,
                                      const std::string& value) {
  // Update UI labels for Fill Capacity (2 digits, one as a shadow)
  lv_label_set_text(ui_Fill_Capacity_Number_1, value.c_str());
  lv_label_set_text(ui_Fill_Capacity_Number_2, value.c_str());
}

void UIManager::onAmountChanged(const std::string& key,
                                const std::string& value) {
  // Calculate the slider values as a percentage
  float fillCapacity = _dataTracker->getFillCapacity();
  float amount = std::stof(value);
  int sliderValue = (fillCapacity != 0.0f)
                        ? static_cast<int>((amount / fillCapacity) * 100)
                        : 0;

  if (key == "AmountFilled") {
    lv_slider_set_value(ui_Slider_Fill, sliderValue, LV_ANIM_OFF);
  } else if (key == "AmountExtracted") {
    lv_slider_set_value(ui_Slider_Extract, sliderValue, LV_ANIM_OFF);
  }
}