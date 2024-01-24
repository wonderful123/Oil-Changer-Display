// SystemManager.cpp
#include "SystemManager.h"

#include <Arduino.h>

#include <memory>

#include "DataTracker.h"
#include "Logger.h"
#include "MessageData.h"

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
  // Determine the type of message and handle accordingly
  if (isCommandMessage(parsedData)) {
    // Handle command message
    std::string command =
        parsedData["command"];  // Assuming 'command' is a key in your message
    _commandHandler->executeCommand(command);
  } else {
    // Handle data update message
    updateSystemData(parsedData);
  }
}

bool SystemManager::isCommandMessage(const MessageData& data) {
  return data.data().find("command") != data.data().end();
}

void SystemManager::updateSystemData(const MessageData& messageData) {
  _dataTracker->updateFromMessageData(messageData);
}
