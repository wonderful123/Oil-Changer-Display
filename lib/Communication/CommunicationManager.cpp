// CommunicationManager.cpp
#include "CommunicationManager.h"

#include <memory>

#include "Config.h"
#include "ESP32/ESP32Serial.h"
#include "Logger.h"
#include "MessageData.h"
#include "MessageParser.h"

void CommunicationManager::initialize() {
  //_interface = new ESP32Serial(serialConfig);
  //_interface = &Serial;
  //_interface = &HardwareSerial(0);
  // _interface = std::make_shared<ESP32Serial>(serialConfig);

  // TODO: crash when trying to initalize interface
}

MessageData CommunicationManager::processMessage() {
  // Check if data is available on the serial port
  if (!Serial.available()) {
    return MessageData();  // Return empty data if no message is available
  }

  static std::string buffer;  // Buffer to accumulate incoming data
  bool messageComplete = false;

  while (Serial.available()) {
    int byteRead = Serial.read();
    if (byteRead != -1) {
      char charRead = static_cast<char>(byteRead);
      buffer += charRead;
      if (charRead == '>') {
        messageComplete = true;
        break;  // Stop reading when the end of a message is reached
      }
    }
  }

  if (!messageComplete) {
    return MessageData();  // Return empty if the message is not complete
  }

  LOG_DEBUG(buffer);

  // Process the complete message
  MessageData parsedData = parseMessage(buffer);
  buffer.clear();  // Clear the buffer for the next message
  return parsedData;
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