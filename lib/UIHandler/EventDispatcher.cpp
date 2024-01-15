// EventDispatcher.cpp
#include "EventDispatcher.h"

#include "Logger.h"

EventDispatcher::EventDispatcher() {
  // Constructor implementation
}

void EventDispatcher::subscribe(Event event, std::function<void()> callback) {
  // Subscribe to an event with a callback
  _eventHandlers[event] = callback;
}

void EventDispatcher::unsubscribe(Event event) {
  // Unsubscribe from an event
  _eventHandlers.erase(event);
}

void EventDispatcher::dispatch(Event event) {
  // Dispatch an event to its subscribers
  if (_eventHandlers.find(event) != _eventHandlers.end()) {
    _eventHandlers[event]();
  }
}
