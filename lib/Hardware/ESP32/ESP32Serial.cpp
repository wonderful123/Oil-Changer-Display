// ESP32Serial.cpp

#ifdef PLATFORM_ESP32

#include "ESP32Serial.h"

#include <sstream>

#include "Logger.h"

ESP32Serial::ESP32Serial(const HardwarePinConfig &config)
    : ISerial(config),  // Pass config to the ISerial constructor
      _serial(determineUartPort(config)),
      _rxPin(-1),
      _txPin(-1),
      _uartPort(0),
      _baudRate(9600) {
  // Extract RX and TX pins from the configuration
  auto rxIt = config.pins.find("RXD");
  if (rxIt != config.pins.end()) {
    _rxPin = rxIt->second;
  }

  auto txIt = config.pins.find("TXD");
  if (txIt != config.pins.end()) {
    _txPin = txIt->second;
  }

  // Extract baud rate from the configuration
  auto baudIt = config.options.find("baud");
  if (baudIt != config.options.end()) {
    std::istringstream ss(baudIt->second);
    if (!(ss >> _baudRate)) {
      _baudRate = 9600;  // Default to 9600 if conversion fails
    }
  }

  // Initialize the Serial with extracted configurations
  initializeSerial();
  setInitialized(true);
}

void ESP32Serial::begin() { initializeSerial(); }

void ESP32Serial::initializeSerial() {
  if (_rxPin != -1 && _txPin != -1) {
    _serial.begin(_baudRate, SERIAL_8N1, _rxPin, _txPin);
  } else {
    // Handle error if pins are not set
    Logger::error("[ESP32Serial] Pins are incorrect");
  }
}

void ESP32Serial::end() { _serial.end(); }

void ESP32Serial::write(const std::string &message) {
  _serial.print(message.c_str());
}

int ESP32Serial::read() { return _serial.read(); }

int ESP32Serial::available() { return _serial.available(); }

void ESP32Serial::flush() { _serial.flush(); }

int ESP32Serial::determineUartPort(const HardwarePinConfig &config) {
  int uartPort = 0;  // Default to UART0
  auto portIt = config.options.find("uartPort");
  if (portIt != config.options.end()) {
    char *end;
    long portNum = strtol(portIt->second.c_str(), &end, 10);
    if (*end == '\0' && portNum >= 0 && portNum <= 2) {
      uartPort = static_cast<int>(portNum);
    } else {
      Logger::error("[ESP32Serial] Invalid UART port number");
    }
  }
  return uartPort;
}

#endif  // PLATFORM_ESP32
