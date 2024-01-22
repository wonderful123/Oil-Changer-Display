// UIManager.h
#pragma once

#include <map>
#include <memory>

#include "DataTracker.h"
#include "UIInitializer.h"
#include "ui.h"

class UIManager {
 public:
  explicit UIManager(std::shared_ptr<DataTracker> dataTracker);
  void setupUI();
  void initialize();

 private:
  void onGenericFloatDataChange(const std::string& dataKey,
                                const std::string& value, int precision = 1);

  void onFillCapacityChange(const std::string& key, const std::string& value);
  void onFlowRateExtractChange(const std::string& key,
                               const std::string& value);
  void onFlowRateFillChange(const std::string& key, const std::string& value);

  void onFillExtractAmountChange(const std::string& key,
                                 const std::string& value);

  int calculateSliderValue(const std::string& fillAmountStr,
                           double fillCapacity);
  void subscribeToDataTracker(const std::string& key,
                              void (UIManager::*memberFunction)(
                                  const std::string&, const std::string&));
  void subscribeToDataTracker(const std::string& key,
                              void (UIManager::*memberFunction)(
                                  const std::string&, const std::string&, int));
  void registerElement(const std::string& dataKey, lv_obj_t* element);

  std::string floatToString(const std::string& input, int precision = 1);

  std::shared_ptr<DataTracker> _dataTracker;
  std::map<std::string, lv_obj_t*> uiElements;
};
