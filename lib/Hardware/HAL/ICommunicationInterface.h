// ICommunicationInterface.h
#pragma once

#include "HardwareComponent.h"
#include "HardwarePinConfig.h"
#include <string>

class ICommunicationInterface : public HardwareComponent {
public:
  explicit ICommunicationInterface(const HardwarePinConfig &config)
      : HardwareComponent(config) {}

  virtual ~ICommunicationInterface() = default;

  // Common communication interface methods
  virtual void begin() = 0;
  virtual void end() = 0;
  virtual int available() = 0;
  virtual int read() = 0;
  virtual void write(const std::string &message) = 0;
};
