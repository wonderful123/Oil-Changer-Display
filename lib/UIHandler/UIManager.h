// UIManager.h
#pragma once

#include <memory>

#include "DataTracker.h"

class UIManager {
 public:
  UIManager(std::shared_ptr<DataTracker> dataTracker);

  // Observer methods
  void onFillCapacityChanged(const std::string& key, const std::string& value);
  void onAmountChanged(const std::string& key, const std::string& value);

 private:
  std::shared_ptr<DataTracker> _dataTracker;
};
