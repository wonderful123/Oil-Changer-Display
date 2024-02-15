// LogMessageHandler.cpp
#include "LogMessageHandler.h"

#include "EventManager/EventManager.h"

void LogMessageHandler::handleMessage(const std::string& message) {
  EventManager::getInstance().notify(message);
}