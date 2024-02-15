// DataTracker.cpp
#include "DataTracker.h"

#include <algorithm>

DataTracker::DataTracker() { initializeKeyMap(); }

// These map to subscribe events that UIManager subscribes to.
void DataTracker::initializeKeyMap() {
  keyMap = {{"FillCap", "FillCapacity"},
            {"AmtFilled", "AmountFilled"},
            {"AmtExtracted", "AmountExtracted"},
            {"Voltage", "BatteryVoltage"},
            {"Temp", "OilTemp"},
            {"FillRate", "FillRate"},
            {"ExtractRate", "ExtractRate"}};
}

void DataTracker::setData(const std::string& key, const std::string& value) {
  data[key] = value;
  notifyObservers(key);
}

std::string DataTracker::getData(const std::string& key) const {
  auto it = data.find(key);
  return it != data.end() ? it->second : "0";
}

void DataTracker::subscribe(const std::string& key, ObserverFunction observer) {
  observers[key].emplace_back(std::move(observer));
}

void DataTracker::unsubscribe(const std::string& key,
                              ObserverFunction observer) {
  auto it = observers.find(key);
  if (it != observers.end()) {
    auto& obsList = it->second;
    obsList.erase(
        std::remove_if(obsList.begin(), obsList.end(),
                       [&observer](const ObserverFunction& existingObserver) {
                         // Compare observer function address
                         return &observer == &existingObserver;
                       }),
        obsList.end());
  }
}

void DataTracker::notifyObservers(const std::string& key) {
  auto it = observers.find(key);
  if (it != observers.end()) {
    auto observersCopy = it->second;
    for (const auto& observer : observersCopy) {
      observer(key, data[key]);
    }
  }
}
