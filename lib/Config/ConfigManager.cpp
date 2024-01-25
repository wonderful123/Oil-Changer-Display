// ConfigManager.cpp
#include "ConfigManager.h"
#include "Logger.h"

ConfigManager::ConfigManager()
    : _hardwareConfig(&_allocator), _wifiConfig(&_allocator) {
  LittleFS.begin();

  if (!loadHardwareConfig()) {
    LOG_ERROR("Failed to load hardware config");
  }

  if (!loadWiFiConfig()) {
    LOG_ERROR("Failed to load wifi config");
  }
}

bool ConfigManager::loadHardwareConfig() {
  return loadConfig(HARDWARE_CONFIG_FILE, "r", _hardwareConfig);
}

bool ConfigManager::loadWiFiConfig() {
  return loadConfig(WIFI_CONFIG_FILE, "r", _wifiConfig);
}

bool ConfigManager::loadConfig(const std::string& filePath,
                               const std::string& mode,
                               JsonDocument& destination) {
  std::string path = filePath;
  if (path.front() != '/') {
    path = "/" + path;
  }

  File configFile = LittleFS.open(path.c_str(), mode.c_str());
  if (!configFile) {
    LOG_ERROR("Failed to open config file: " + path);
    return false;
  }
  LOG_INFO("Successfully opened config file: " + path);

  DeserializationError error = deserializeJson(destination, configFile);
  if (error) {
    LOG_ERROR("DeserializeJson failed: " + std::string(error.c_str()));
    return false;
  }
  LOG_INFO("Config file deserialized");

  return true;
}

JsonDocument ConfigManager::getConfigSection(const std::string& sectionName,
                                             const JsonDocument& doc) const {
  JsonDocument tempDoc;
  tempDoc.set(doc[sectionName]);
  if (tempDoc.isNull()) {
    LOG_WARN(sectionName + " config is empty");
  }
  return tempDoc;
}

JsonDocument ConfigManager::getDisplayConfig() const {
  return getConfigSection("display", _hardwareConfig);
}

JsonDocument ConfigManager::getTouchConfig() const {
  return getConfigSection("touch", _hardwareConfig);
}

JsonDocument ConfigManager::getWiFiConfig() const {
  return getConfigSection("wifi", _wifiConfig);
}

JsonDocument ConfigManager::getWebServerConfig() const {
  return getConfigSection("webServer", _wifiConfig);
}

JsonDocument ConfigManager::getOTAConfig() const {
  return getConfigSection("ota", _wifiConfig);
}

void ConfigManager::listFiles() {
  LOG_INFO("Listing files on the device:");
  File root = LittleFS.open("/");
  if (!root) {
    LOG_ERROR("Failed to open root directory.");
  } else if (!root.isDirectory()) {
    LOG_ERROR("Root is not a directory.");
  } else {
    File file = root.openNextFile();
    while (file) {
      LOG_INFO("File: " + std::string(file.name()));
      file.close();
      file = root.openNextFile();
    }
  }
}
