// SystemManager.cpp
#include <Arduino.h>

#include <memory>

#include "DataTracker.h"
#include "Logger.h"
#include "MessageData.h"
#include "SystemManager.h"

SystemManager::SystemManager()
    : _communicationManager(new CommunicationManager()) {
  _dataTracker = std::make_shared<DataTracker>();
  _uiManager = std::make_shared<UIManager>(_dataTracker);
}

void SystemManager::initialize() {
  _communicationManager->initialize();
  _uiManager->initialize();
}

void SystemManager::update() {
  auto messageData = _communicationManager->processMessage();
  if (!messageData.empty()) {
    processMessageData(messageData);
  }
}

void SystemManager::processMessageData(MessageData parsedData) {
  // Handle data update message
  updateSystemData(parsedData);
}

void SystemManager::updateSystemData(const MessageData& messageData) {
  _dataTracker->updateFromMessageData(messageData);
}
