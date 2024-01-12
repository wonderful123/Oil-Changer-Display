#include "ConfigManager.h"

ConfigManager::ConfigManager(const String& configFile)
    : config(1024), configFile(configFile) {}

bool ConfigManager::loadConfig() {
  File file = SPIFFS.open(configFile, "r");
  if (!file) {
    Serial.println("Failed to open config file");
    return false;
  }

  DeserializationError error = deserializeJson(config, file);
  if (error) {
    Serial.println("Failed to read file, using default configuration");
    return false;
  }

  return true;
}

JsonObject ConfigManager::getDisplayConfig() const { return config["display"]; }

JsonObject ConfigManager::getTouchConfig() const { return config["touch"]; }
