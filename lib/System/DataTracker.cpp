// DataTracker.cpp
#include "DataTracker.h"

#include <algorithm>

#include "Logger.h"
#include "MessageData.h"

DataTracker::DataTracker()
    : _fillCapacity(0.0f),
      _amountFilled(0.0f),
      _amountExtracted(0.0f),
      _voltage(0.0f),
      _oilTemperature(0.0f),
      _flowRateExtract(0.0f),
      _flowRateFill(0.0f) {}

// Specific data field setters
void DataTracker::setFillCapacity(float value) { _fillCapacity = value; }
void DataTracker::setAmountFilled(float value) { _amountFilled = value; }
void DataTracker::setAmountExtracted(float value) { _amountExtracted = value; }
void DataTracker::setVoltage(float value) { _voltage = value; }
void DataTracker::setOilTemperature(float value) { _oilTemperature = value; }
void DataTracker::setFlowRateExtract(float value) { _flowRateExtract = value; }
void DataTracker::setFlowRateFill(float value) { _flowRateFill = value; }

// Specific data field getters
float DataTracker::getFillCapacity() const { return _fillCapacity; }
float DataTracker::getAmountFilled() const { return _amountFilled; }
float DataTracker::getAmountExtracted() const { return _amountExtracted; }
float DataTracker::getVoltage() const { return _voltage; }
float DataTracker::getOilTemperature() const { return _oilTemperature; }
float DataTracker::getFlowRateExtract() const { return _flowRateExtract; }
float DataTracker::getFlowRateFill() const { return _flowRateFill; }

void DataTracker::setData(const std::string& key, const std::string& value) {
  data.emplace(key, value);
  notifyObservers(key);
}

std::string DataTracker::getData(const std::string& key) const {
  auto it = data.find(key);
  return it != data.end() ? it->second : "";
}

void DataTracker::updateMessageData(const MessageData& messageData) {
  for (const auto& keyValue : messageData.data()) {
    LOG_DEBUG(keyValue.first);
    setData(keyValue.first, keyValue.second);
  }
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
  auto it = data.find(key);
  if (it != data.end()) {
    for (const auto& observer : observers[key]) {
      observer(key, it->second);
    }
  }
}