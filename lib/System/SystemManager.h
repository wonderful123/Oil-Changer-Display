// SystemManager.h
#pragma once

#include <memory>

#include "CommunicationManager.h"
#include "DataTracker.h"
#include "UIManager.h"

class MessageData;

/**
 * @class SystemManager
 *
 * @brief Manages the overall system operations and interactions between various
 * components.
 *
 * SystemManager is the central component of the embedded system application. It
 * orchestrates the interactions between various subsystems, including
 * communication, data tracking, command handling, and user interface
 * management. This class is responsible for initializing these subsystems,
 * processing incoming messages, and ensuring that data is appropriately managed
 * and disseminated throughout the system.
 *
 * Key Responsibilities:
 * - Initializing all subsystems, such as CommunicationManager, UIManager, and
 * DataTracker.
 * - Processing and routing incoming messages from the communication interface.
 * - Determining whether incoming messages are command or data updates and
 * handling them accordingly.
 * - Updating the system data through DataTracker based on the received
 * messages.
 * - Ensuring that the user interface reflects the current state of the system
 * by interacting with UIManager.
 *
 * The SystemManager acts as a conductor, ensuring that each part of the system
 * functions harmoniously and efficiently in response to internal and external
 * events.
 */
class SystemManager {
 public:
  SystemManager();
  void initialize();
  void update();

 private:
  std::unique_ptr<CommunicationManager> _communicationManager;
  std::shared_ptr<UIManager> _uiManager;
  std::shared_ptr<DataTracker> _dataTracker;

  void setMessageHandlers();
};
