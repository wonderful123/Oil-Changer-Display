// CommunicationManager.cpp
#include "CommunicationManager.h"

#include <memory>

#include "Config.h"
#include "ESP32/ESP32Serial.h"
#include "Logger.h"
#include "MessageData.h"
#include "MessageParser.h"

void CommunicationManager::initialize() {
  _interface = HardwareSerial(0);
  //_interface = Serial;
}

MessageData CommunicationManager::processMessage() {
  std::string receivedMessage;

  while (_interface.available()) {
    int byteRead = _interface.read();
    if (byteRead != -1) {  // Check if a byte is available
      receivedMessage += static_cast<char>(byteRead);
    }
  }

  return parseMessage(receivedMessage);
}

MessageData CommunicationManager::parseMessage(
    const std::string& receivedMessage) {
  // Use MessageParser to parse the received message
  MessageData parsedData = MessageParser::parseMessage(receivedMessage);

  if (parsedData.empty()) {
    // Return empty data if it's not valid
    return MessageData();
  }

  return parsedData;
}