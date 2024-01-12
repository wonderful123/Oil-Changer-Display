// ConfigManager.h
#pragma once

#include <ArduinoJson.h>
#include <FS.h>

class ConfigManager {
 public:
  ConfigManager(const String& configFile);
  bool loadConfig();
  JsonObject getDisplayConfig() const;
  JsonObject getTouchConfig() const;

 private:
  DynamicJsonDocument config;
  String configFile;
};