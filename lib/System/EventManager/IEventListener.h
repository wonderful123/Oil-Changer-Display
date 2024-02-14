// IEventListener.h
#pragma once

#include <string>

class IEventListener {
 public:
  virtual ~IEventListener() {}
  virtual void onEvent(const std::string& message) = 0;
};
