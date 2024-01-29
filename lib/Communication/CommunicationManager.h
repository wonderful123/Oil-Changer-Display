// CommunicationManager.h
#pragma once

#include <memory>
#include <string>

#include "ESP32/ESP32Serial.h"
#include "HAL/ICommunicationInterface.h"
class MessageData;

enum class MessageType { DataMessage, OtherMessage };

class CommunicationManager {
 public:
  static constexpr unsigned long MESSAGE_TIMEOUT_MS = 500;
  static constexpr size_t MAX_MESSAGE_LENGTH = 256;

  CommunicationManager();
  void initialize();
  MessageData processMessage();

 private:
  // ICommunicationInterface* _interface;
  // std::shared_ptr<ICommunicationInterface> _interface;
  HardwareSerial* _interface;
  // TODO: Not sure if pointer or smart pointer

  std::string buffer;
  MessageType detectMessageType(const std::string& message);
  MessageData parseDataMessage(const std::string& receivedMessage);
  void processOtherMessage(const std::string& message);
  bool isMessageComplete(const std::string& buffer);
  bool isValidCharacter(char c);
};
