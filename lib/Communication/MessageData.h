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

  // Utility function to convert MessageData contents to a string
  std::string messageDataToString(const MessageData& messageData) {
    std::stringstream ss;
    for (const auto& pair : messageData.data()) {
      ss << pair.first << ": " << pair.second << "; ";
    }
    std::string result = ss.str();
    // Optionally remove the last semicolon and space if not empty
    if (!result.empty()) {
      result.pop_back();  // Remove last space
      result.pop_back();  // Remove last semicolon
    }
    return result;
  }

 private:
  std::unordered_map<std::string, std::string> _messageData;
};
