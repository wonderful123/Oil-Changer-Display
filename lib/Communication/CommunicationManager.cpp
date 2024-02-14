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

CommunicationManager::CommunicationManager() : _interface(nullptr) {
  buffer.reserve(MAX_MESSAGE_LENGTH);  // Preallocate buffer
}

void CommunicationManager::initialize() {
  //_interface = new ESP32Serial(serialConfig);
  //_interface = &HardwareSerial(0);
  // _interface = &Serial;
  _interface = &Serial;
  _interface->begin(115200);
  // _interface->begin(115200, SERIAL_8N1, 17, 18);
  buffer.clear();

  LOG_INFO("CommunicationManager initialized");
}

MessageType CommunicationManager::detectMessageType(
    const std::string& message) {
  static const std::string deviceIdentifierTag =
      "<" + std::string(DEVICE_IDENTIFIER) + ";";
  if (message.rfind(deviceIdentifierTag, 0) == 0 &&
      message.find("CKS:") != std::string::npos) {
    return MessageType::DataMessage;
  }
  return MessageType::OtherMessage;
}

MessageData CommunicationManager::processMessage() {
  if (!_interface->available() && buffer.empty()) {
    return MessageData();  // Early return if no data and buffer is empty
  }

  // Initialize the start time for timeout check.
  auto startTime = std::chrono::steady_clock::now();

  // Process incoming characters.
  while (_interface->available() > 0) {
    // Check for timeout first to handle it immediately.
    auto currentTime = std::chrono::steady_clock::now();
    if (currentTime - startTime >
        std::chrono::milliseconds(MESSAGE_TIMEOUT_MS)) {
      LOG_DEBUG("Message read timeout");
      buffer.clear();
      return MessageData();
    }

    // Read the next character.
    char charRead = static_cast<char>(_interface->read());

    // Validate the character.
    if (!isValidCharacter(charRead)) {
      buffer.clear();
      return MessageData();  // Clear buffer on invalid character.
    }

    // Check for buffer overflow.
    if (buffer.length() >= MAX_MESSAGE_LENGTH) {
      LOG_DEBUG("Maximum message length exceeded");
      buffer.clear();
      return MessageData();  // Clear buffer if max length exceeded.
    }

    // Append the character to the buffer.
    buffer.push_back(charRead);

    // Check if the message is complete.
    if (isMessageComplete(buffer)) {
      LOG_DEBUG("Complete message read: " + buffer);
      auto parsedData = processMessageType(buffer);
      buffer.clear();
      return parsedData;
    }
  }

  // If the loop exits without finding a complete message, it means there's no
  // more data available.
  LOG_DEBUG("Incomplete message pending, waiting for more data");
  return MessageData();  // Incomplete message or waiting for more.
}

MessageData CommunicationManager::processMessageType(
    const std::string& buffer) {
  MessageType type = detectMessageType(buffer);
  if (type == MessageType::DataMessage) {
    return parseDataMessage(buffer);
  } else {
    processOtherMessage(buffer);
    return MessageData();
  }
}

bool CommunicationManager::isMessageComplete(const std::string& buffer) {
  return !buffer.empty() && buffer.back() == '>';
}

bool CommunicationManager::isValidCharacter(char c) {
  return c >= 32 && c <= 126;
}

MessageData CommunicationManager::parseDataMessage(
    const std::string& receivedMessage) {
  return MessageParser::parseMessage(receivedMessage);
}

void CommunicationManager::processOtherMessage(const std::string& message) {
  LOG_INFO("Processing non-data message: " + message);
  // Add logic for processing other types of messages
}