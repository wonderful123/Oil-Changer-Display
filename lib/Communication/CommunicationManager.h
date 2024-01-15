// CommunicationManager.h
#pragma once

#include <memory>
#include <string>

#include "HAL/ICommunicationInterface.h"

class CommunicationManager {
 public:
  explicit CommunicationManager(
      std::shared_ptr<ICommunicationInterface> interface);
  void initialize();
  std::string receiveMessage();

 private:
  std::shared_ptr<ICommunicationInterface> _interface;
};
