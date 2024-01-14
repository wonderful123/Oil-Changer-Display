#pragma once
#include <string>

class CommunicationManager {
 public:
  CommunicationManager();
  void sendMessage(const std::string& message);
  std::string receiveMessage();
  // Other necessary methods

 private:
  // Internal data structures and methods
};
