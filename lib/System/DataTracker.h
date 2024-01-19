// DataTracker.h
#pragma once

#include <functional>
#include <string>
#include <unordered_map>
#include <vector>

class MessageData;

class DataTracker {
 public:
  DataTracker();

  // Specific data fields setters and getters
  void setFillCapacity(float value);
  float getFillCapacity() const;
  void setAmountFilled(float value);
  float getAmountFilled() const;
  void setAmountExtracted(float value);
  float getAmountExtracted() const;
  void setVoltage(float value);
  float getVoltage() const;
  void setOilTemperature(float value);
  float getOilTemperature() const;
  void setFlowRateExtract(float value);
  float getFlowRateExtract() const;
  void setFlowRateFill(float value);
  float getFlowRateFill() const;

  // Generic data functions
  void setData(const std::string& key, const std::string& value);
  std::string getData(const std::string& key) const;
  void updateMessageData(const MessageData& messageData);

  // Observer pattern functions
  using ObserverFunction =
      std::function<void(const std::string&, const std::string&)>;
  void subscribe(const std::string& key, ObserverFunction observer);
  void unsubscribe(const std::string& key, ObserverFunction observer);

 private:
  std::unordered_map<std::string, std::string> data;
  std::unordered_map<std::string, std::vector<ObserverFunction>> observers;

  void notifyObservers(const std::string& key);

  // Specific data fields
  float _fillCapacity;
  float _amountFilled;
  float _amountExtracted;
  float _voltage;
  float _oilTemperature;
  float _flowRateExtract;
  float _flowRateFill;
};