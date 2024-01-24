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

  // Generic data functions
  void setData(const std::string& key, const std::string& value);
  std::string getData(const std::string& key) const;
  void updateFromMessageData(const MessageData& messageData);

  // Observer pattern functions
  using ObserverFunction =
      std::function<void(const std::string&, const std::string&)>;
  void subscribe(const std::string& key, ObserverFunction observer);
  void unsubscribe(const std::string& key, ObserverFunction observer);

 private:
  std::unordered_map<std::string, std::string> data;
  std::unordered_map<std::string, std::vector<ObserverFunction>> observers;

  std::unordered_map<std::string, std::string> keyMap;
  void initializeKeyMap();

  void notifyObservers(const std::string& key);
};