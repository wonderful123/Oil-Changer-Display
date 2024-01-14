// ConfigManager.h
#pragma once

#include <ArduinoJson.h>
#include <FS.h>
#include <LittleFS.h>

#include <string>

class ConfigManager {
 public:
  ConfigManager();
  bool loadConfig(std::string filePath, std::string mode);
  JsonObject getDisplayConfig() const;
  JsonObject getTouchConfig() const;

 private:
  mutable JsonDocument _config;  // Make '_config' mutable
};
