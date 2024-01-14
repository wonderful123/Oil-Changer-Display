// ESP32FileHandler.cpp

#ifdef PLATFORM_ESP32

#include "ESP32FileHandler.h"

#include <LittleFS.h>

#include "Logger.h"

ESP32FileHandler::ESP32FileHandler() {
  _isFileSystemMounted = LittleFS.begin();
  if (!_isFileSystemMounted) {
    Logger::error("[ESP32FileHandler] File system not mounted");
  }
}

bool ESP32FileHandler::open(const std::string &filePath,
                            const std::string &mode) {
  if (_file) {
    _file.close();  // Close any previously opened file
  }

  _currentFilePath = filePath;  // Store the current file path

  _file = LittleFS.open(filePath.c_str(), mode.c_str());
  if (!_file) {
    Logger::error("[ESP32FileHandler] Unable to open file");
    return false;
  }
  return true;
}

bool ESP32FileHandler::write(const std::string &data) {
  if (!_file) {
    Logger::warn("[ESP32FileHandler] Write attempted on unopened file");
    return false;
  }
  size_t bytesWritten = _file.print(data.c_str());
  if (bytesWritten != data.length()) {
    Logger::error(
        "[ESP32FileHandler] Written file size doesn't match data length");
    return false;
  }
  return true;
}

std::string ESP32FileHandler::read() {
  std::string content;
  if (!_file) {
    Logger::warn("[ESP32FileHandler] Read attempted on unopened file");
    return content;
  }
  while (_file.available()) {
    content += static_cast<char>(_file.read());
  }
  return content;
}

bool ESP32FileHandler::exists(const std::string &filePath) const {
  return LittleFS.exists(filePath.c_str());
}

void ESP32FileHandler::close() {
  if (_file) {
    _file.close();
  }
  _currentFilePath.clear();
}

bool ESP32FileHandler::remove(const std::string &filePath) {
  if (!LittleFS.exists(filePath.c_str())) {
    Logger::warn("[ESP32FileHandler] Attempt to remove non-existing file: " +
                 filePath);
    return false;
  }
  return LittleFS.remove(filePath.c_str());
}

#endif  // PLATFORM_ESP32
