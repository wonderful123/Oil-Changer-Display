// SystemManager.h
#pragma once

#include <memory>

#include "CommandHandler.h"
#include "CommunicationManager.h"
#include "DataTracker.h"
#include "EventDispatcher.h"
#include "MessageParser.h"
#include "UIManager.h"

class MessageData;

class SystemManager {
 public:
  void initialize();
  void update();

 private:
  std::unique_ptr<CommunicationManager> _communicationManager;
  std::unique_ptr<UIManager> _uiManager;
  std::unique_ptr<EventDispatcher> _eventDispatcher;
  std::unique_ptr<CommandHandler> _commandHandler;
  std::unique_ptr<DataTracker> _dataTracker;

  void initializeCommunicationManager();
  void processMessageData(MessageData message);
  void updateUI();
  bool isCommandMessage(const MessageData& data);
  void updateSystemData(const MessageData& data);
};
