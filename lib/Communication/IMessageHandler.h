#pragma once

#include <string>

class IMessageHandler {
 public:
  virtual ~IMessageHandler() {}
  virtual void handleMessage(const std::string& message) = 0;
};