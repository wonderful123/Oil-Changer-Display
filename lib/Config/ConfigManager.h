// ConfigManager.h
#pragma once

#include <ArduinoJson.h>
#include <FS.h>
#include <LittleFS.h>

#include <memory>
#include <string>

#include "SpiRamAllocator.h"

constexpr char HARDWARE_CONFIG_FILE[] = "/HardwareConfig.json";
constexpr char WIFI_CONFIG_FILE[] = "/WiFiConfig.json";

class ConfigManager {
 public:
  static ConfigManager& getInstance() {
    static ConfigManager instance;
    return instance;
  }

  bool loadHardwareConfig();
  JsonDocument getDisplayConfig() const;
  JsonDocument getTouchConfig() const;

  bool loadWiFiConfig();
  JsonDocument getWiFiConfig() const;
  JsonDocument getWebServerConfig() const;
  JsonDocument getOTAConfig() const;

  void listFiles();

 private:
  ConfigManager();

  SpiRamAllocator _allocator;
  JsonDocument _hardwareConfig;
  JsonDocument _wifiConfig;

  bool loadConfig(const std::string& filePath, const std::string& mode,
                  JsonDocument& destination);
  JsonDocument getConfigSection(const std::string& sectionName,
                                const JsonDocument& doc) const;
};
