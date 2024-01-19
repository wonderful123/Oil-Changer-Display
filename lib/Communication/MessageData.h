// MessageData.h
#pragma once

#include <string>
#include <unordered_map>

class MessageData {
 public:
  const std::unordered_map<std::string, std::string>& data() const { return _messageData; }
  // For non const access
  std::unordered_map<std::string, std::string>& data() { return _messageData; }

  // Overload for accessing elements
  std::string& operator[](const std::string& key) { return _messageData[key]; }

  bool empty() {
    return _messageData.empty();
  }

 private:
  std::unordered_map<std::string, std::string> _messageData;
};
