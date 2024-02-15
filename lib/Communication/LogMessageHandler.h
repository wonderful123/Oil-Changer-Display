// LogMessageHandler.h
#pragma once

#include <string>

#include "IMessageHandler.h"

class LogMessageHandler : public IMessageHandler {
 public:
  void handleMessage(const std::string& message) override;
};