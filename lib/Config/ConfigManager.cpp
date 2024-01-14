// ConfigManager.cpp
#include "ConfigManager.h"

#include "Logger.h"

ConfigManager::ConfigManager() {
  LittleFS.begin();
  _config = JsonDocument();
}

bool ConfigManager::loadConfig(std::string filePath, std::string mode) {
  // Ensure filePath starts with '/'
  if (filePath.front() != '/') {
    filePath = "/" + filePath;
  }

  // Logger::info("[ConfigManager] Listing files on the device:");
  // File root = LittleFS.open("/");
  // if (!root) {
  //   Logger::error("[ConfigManager] Failed to open root directory.");
  // } else if (!root.isDirectory()) {
  //   Logger::error("[ConfigManager] Root is not a directory.");
  // } else {
  //   File file = root.openNextFile();
  //   std::string filename = file.name();
  //   while (file) {
  //     Logger::info("[ConfigManager] File: " + filename);
  //     file.close();
  //     file = root.openNextFile();
  //   }
  // }

  File configFile = LittleFS.open(filePath.c_str(), mode.c_str());
  if (!configFile) {
    Logger::error("[ConfigManager] Failed to open config file: " + filePath);
    return false;
  }
  Logger::info("[ConfigManager] Successfully open config file: " + filePath);

  DeserializationError error = deserializeJson(_config, configFile);
  if (error) {
    Logger::error("[ConfigManager] DeserializeJson failed: " +
                  std::string(error.c_str()));
    return false;
  }
  Logger::info("[ConfigManager] Config file deserialized");

  return true;
}

JsonObject ConfigManager::getDisplayConfig() const {
  JsonObject obj = _config["display"];
  if (obj.isNull()) {
    Logger::error("[ConfigManager] Display configuration is null");
    return JsonObject();  // Return an empty JsonObject
  }
  return obj;
}

JsonObject ConfigManager::getTouchConfig() const {
  JsonObject obj = _config["touch"];
  if (obj.isNull()) {
    Logger::error("[ConfigManager] Touch configuration is null");
    return JsonObject();  // Return an empty JsonObject
  }
  return obj;
}
