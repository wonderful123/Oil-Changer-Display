// SystemManager.cpp
#include "SystemManager.h"

#include <Arduino.h>

#include <memory>

#include "DataMessageHandler.h"
#include "DataTracker.h"
#include "LogMessageHandler.h"
#include "Logger.h"

SystemManager::SystemManager()
    : _communicationManager(new CommunicationManager()) {
  _dataTracker = std::make_shared<DataTracker>();
  _uiManager = std::make_shared<UIManager>(_dataTracker);

  setMessageHandlers();
}

void SystemManager::initialize() {
  _communicationManager->initialize();
  _uiManager->initialize();
}

void SystemManager::update() { _communicationManager->processIncomingData(); }

void SystemManager::setMessageHandlers() {
  auto dataMessageHandler = std::make_shared<DataMessageHandler>(*_dataTracker);
  _communicationManager->setDataMessageHandler(dataMessageHandler);
  auto logMessageHandler = std::make_shared<LogMessageHandler>();
  _communicationManager->setLogMessageHandler(logMessageHandler);
}