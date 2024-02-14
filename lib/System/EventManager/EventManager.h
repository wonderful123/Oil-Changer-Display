// EventManager.h
#pragma once

#include <algorithm>
#include <memory>
#include <string>
#include <vector>

#include "IEventListener.h"

class EventManager {
 public:
  static EventManager& getInstance();

  void subscribe(IEventListener* listener);
  void unsubscribe(IEventListener* listener);
  void notify(const std::string& message);

 private:
  std::vector<IEventListener*> listeners;

  // Private constructor for singleton
  EventManager() {}

  // Deleting the methods we don't want to accidentally use.
  EventManager(EventManager const&) = delete;
  void operator=(EventManager const&) = delete;
};
