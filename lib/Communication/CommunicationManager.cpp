// CommunicationManager.cpp
#include "CommunicationManager.h"

#include <Arduino.h>

#include <chrono>
#include <memory>

#include "Config.h"
#include "ESP32/ESP32Serial.h"
#include "Logger.h"
#include "MessageData.h"
#include "MessageParser.h"

CommunicationManager::CommunicationManager() {
  buffer.reserve(MAX_MESSAGE_LENGTH);
}

void CommunicationManager::initialize() {
  //_interface = new ESP32Serial(serialConfig);
  //_interface = &HardwareSerial(0);
  // TODO: Implement the interface using the abstract class ICommunicationInterface
  _interface = &Serial;
  lastMessageTime =
      std::chrono::steady_clock::now();  // Initialize last message time
}

void CommunicationManager::setDataMessageHandler(
    std::shared_ptr<IMessageHandler> handler) {
  _dataMessageHandler = handler;
}

void CommunicationManager::setLogMessageHandler(
    std::shared_ptr<IMessageHandler> handler) {
  _logMessageHandler = handler;
}

void CommunicationManager::processIncomingData() {
  while (_interface->available() > 0) {
    char charRead = static_cast<char>(_interface->read());
    buffer += charRead;

    if (buffer.length() >= MAX_MESSAGE_LENGTH) {
      handleBufferOverflow();
      continue;
    }

    if (charRead == '\n') {
      processMessage(buffer);
      buffer.clear();  // Clear buffer after processing the message
    } else {
      handleMessageTimeout();
    }
  }
}

void CommunicationManager::handleBufferOverflow() {
  LOG_ERROR("Buffer overflow detected. Clearing buffer.");
  buffer.clear();
}

void CommunicationManager::handleMessageTimeout() {
  auto now = std::chrono::steady_clock::now();
  if (std::chrono::duration_cast<std::chrono::milliseconds>(now -
                                                            lastMessageTime)
          .count() > MESSAGE_TIMEOUT_MS) {
    LOG_ERROR("Message timeout detected. Clearing buffer.");
    buffer.clear();
    lastMessageTime = now;  // Reset the timer
  }
}

bool CommunicationManager::isDataMessage(const std::string& message) const {
  // Check if it starts with <DEVICE_IDENTIFIER;
  std::string startPattern = "<" + std::string(DEVICE_IDENTIFIER) + ";";
  if (message.substr(0, startPattern.length()) != startPattern) {
    return false;
  }

  // Check if it ends with CKS:<number>
  std::size_t cksPos = message.rfind("CKS:");
  if (cksPos == std::string::npos) {
    return false;
  }

  std::size_t numberPos = cksPos + 4;  // CKS: length is 4
  std::size_t endPos = message.find('>', numberPos);
  if (endPos == std::string::npos) {
    return false;
  }

  std::string numberStr = message.substr(numberPos, endPos - numberPos);
  // Check if the substring is a valid number
  return std::all_of(numberStr.begin(), numberStr.end(), ::isdigit);
}

void CommunicationManager::processMessage(const std::string& message) {
  if (isDataMessage(message)) {
    dataMessageHandler.handleMessage(message);
  } else {
    loggerMessageHandler.handleMessage(message);
  }
  lastMessageTime = std::chrono::steady_clock::now();  // Update last message
                                                       // time after processing
}