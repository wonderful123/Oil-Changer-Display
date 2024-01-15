// CommunicationManager.cpp
#include "CommunicationManager.h"

CommunicationManager::CommunicationManager(
    std::shared_ptr<ICommunicationInterface> interface)
    : _interface(interface) {}

void CommunicationManager::initialize() { _interface->begin(); }

std::string CommunicationManager::receiveMessage() {
  std::string receivedMessage;
  while (_interface->available()) {
    int byteRead = _interface->read();
    if (byteRead != -1) {  // Check if a byte is available
      receivedMessage += static_cast<char>(byteRead);
    }
  }
  return receivedMessage;
}