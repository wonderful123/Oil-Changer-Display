// CommunicationManager.h
#pragma once

#include <chrono>
#include <memory>
#include <string>

#include "Config.h"
#include "DataMessageHandler.h"
#include "ESP32/ESP32Serial.h"
#include "HAL/ICommunicationInterface.h"
#include "LogMessageHandler.h"

class MessageData;

enum class MessageType { DataMessage, OtherMessage };

class CommunicationManager {
 public:
  CommunicationManager();
  void initialize();
  void processIncomingData();

  void setDataMessageHandler(std::shared_ptr<IMessageHandler> handler);
  void setLogMessageHandler(std::shared_ptr<IMessageHandler> handler);

 private:
  // ICommunicationInterface* _interface;
  // std::shared_ptr<ICommunicationInterface> _interface;
  HardwareSerial* _interface = nullptr;

  std::string _buffer;
  std::chrono::steady_clock::time_point _lastMessageTime;
  static constexpr unsigned long MESSAGE_TIMEOUT_MS = 500;
  static constexpr size_t MAX_MESSAGE_LENGTH = 256;

  std::shared_ptr<IMessageHandler> _dataMessageHandler;
  std::shared_ptr<IMessageHandler> _logMessageHandler;

  bool isDataMessage(const std::string& message) const;
  void handleBufferOverflow();
  void handleMessageTimeout();
  void processMessage(const std::string& message);
};
