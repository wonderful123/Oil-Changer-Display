// EventDispatcher.h
#pragma once

#include <functional>
#include <map>

enum class Event {
  // Define events
};

class EventDispatcher {
 public:
  EventDispatcher();
  void subscribe(Event event, std::function<void()> callback);
  void unsubscribe(Event event);
  void dispatch(Event event);
  // Other necessary methods

 private:
  std::map<Event, std::function<void()>> _eventHandlers;
};
