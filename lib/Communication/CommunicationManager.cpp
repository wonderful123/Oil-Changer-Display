// CommunicationManager.cpp
#include <Arduino.h>

#include <chrono>
#include <memory>

#include "CommunicationManager.h"
#include "Config.h"
#include "ESP32/ESP32Serial.h"
#include "Logger.h"
#include "MessageData.h"
#include "MessageParser.h"

CommunicationManager::CommunicationManager() : _interface(nullptr), buffer("") {}

void CommunicationManager::initialize() {
  //_interface = new ESP32Serial(serialConfig);
  //_interface = &HardwareSerial(0);
  _interface = &Serial1;
  _interface->begin(115200, SERIAL_8N1, 17, 18);
  buffer.clear();

  LOG_INFO("CommunicationManager initialized");
}

MessageType CommunicationManager::detectMessageType(
    const std::string& message) {
  std::string deviceIdentifierTag = "<" + std::string(DEVICE_IDENTIFIER) + ";";
  if (message.rfind(deviceIdentifierTag, 0) == 0 &&
      message.find("CKS:") != std::string::npos) {
    return MessageType::DataMessage;
  }
  return MessageType::OtherMessage;
}

MessageData CommunicationManager::processMessage() {
  if (!_interface->available() && buffer.empty()) {
    return MessageData();  // No new data and no partial message in buffer
  }

  auto startTime = std::chrono::steady_clock::now();

  while (!isMessageComplete(buffer)) {
    if (std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::steady_clock::now() - startTime)
            .count() > MESSAGE_TIMEOUT_MS) {
      LOG_ERROR("Message read timeout");
      buffer.clear();
      return MessageData();
    }

    if (_interface->available()) {
      char charRead = static_cast<char>(_interface->read());
      if (!isValidCharacter(charRead) ||
          buffer.length() >= MAX_MESSAGE_LENGTH) {
        LOG_ERROR("Invalid message");
        buffer.clear();
        return MessageData();
      }
      buffer += charRead;
    }
  }
  LOG_DEBUG("Message read: " + buffer);

  MessageType type = detectMessageType(buffer);
  MessageData parsedData;
  if (type == MessageType::DataMessage) {
    parsedData = parseDataMessage(buffer);
  } else {
    processOtherMessage(buffer);
  }
  buffer.clear();  // Clear buffer after processing
  return parsedData;
}

bool CommunicationManager::isMessageComplete(const std::string& buffer) {
  return !buffer.empty() && buffer.back() == '>';
}

bool CommunicationManager::isValidCharacter(char c) {
  return c >= 32 && c <= 126;
}

MessageData CommunicationManager::parseDataMessage(
    const std::string& receivedMessage) {
  LOG_INFO(receivedMessage);
  return MessageParser::parseMessage(receivedMessage);
}

void CommunicationManager::processOtherMessage(const std::string& message) {
  LOG_INFO("Processing non-data message: " + message);
  // Add logic for processing other types of messages
}