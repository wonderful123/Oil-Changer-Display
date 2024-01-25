// SystemManager.cpp
#include <Arduino.h>

#include <memory>

#include "DataTracker.h"
#include "Logger.h"
#include "MessageData.h"
#include "SystemManager.h"

SystemManager::SystemManager()
    : _dataTracker(std::make_shared<DataTracker>()) {}

void SystemManager::initialize() {
  initializeCommunicationManager();
  _uiManager = std::make_shared<UIManager>(_dataTracker);
  _uiManager->initialize();
}

void SystemManager::initializeCommunicationManager() {
  _communicationManager->initialize();
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
