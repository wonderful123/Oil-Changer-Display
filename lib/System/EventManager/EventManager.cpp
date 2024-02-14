// EventManager.cpp
#include <algorithm>

#include "EventManager.h"

EventManager& EventManager::getInstance() {
  static EventManager instance;
  return instance;
}

void EventManager::subscribe(IEventListener* listener) {
  listeners.push_back(listener);
}

void EventManager::unsubscribe(IEventListener* listener) {
  listeners.erase(std::remove(listeners.begin(), listeners.end(), listener),
                  listeners.end());
}

void EventManager::notify(const std::string& message) {
  for (auto& listener : listeners) {
    listener->onEvent(message);
  }
}
