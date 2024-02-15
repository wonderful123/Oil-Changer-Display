// DataMessageHandler.h
#pragma once

#include <string>

#include "IMessageHandler.h"

class DataTracker;

class DataMessageHandler : public IMessageHandler {
 public:
  DataMessageHandler(DataTracker& tracker);

  void handleMessage(const std::string& message) override;

  void parseAndSetData(const std::string& payload);

 private:
  DataTracker& _dataTracker;

  unsigned int calculateChecksum(const std::string& payload);
};