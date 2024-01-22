// CommunicationManager.h
#pragma once

#include <memory>
#include <string>

#include "ESP32/ESP32Serial.h"
#include "HAL/ICommunicationInterface.h"
class MessageData;

class CommunicationManager {
 public:
  void initialize();
  MessageData processMessage();

 private:
  ICommunicationInterface* _interface;
   std::shared_ptr<ICommunicationInterface> _interface;
  //  HardwareSerial* _interface;
  // TODO: Not sure if pointer or smart pointer
  MessageData parseMessage(const std::string& receivedMessage);
};
