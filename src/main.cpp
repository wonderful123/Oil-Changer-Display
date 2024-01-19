// main.cpp
#include <Arduino.h>

#include <memory>
#include <string>

#include "DisplayManager.h"
#include "Logger.h"
#include "SystemManager.h"

// Foward declarations
void serialLogCallback(Logger::Level level, const std::string& message);
void initializeLogger();

// Global Objects
DisplayManager displayManager;
SystemManager systemManager;

void logMemory() {
  log_d("Total heap: %d", ESP.getHeapSize());
  log_d("Free heap: %d", ESP.getFreeHeap());
  log_d("Total PSRAM: %d", ESP.getPsramSize());
  log_d("Free PSRAM: %d", ESP.getFreePsram());
  log_d("Used PSRAM: %d", ESP.getPsramSize() - ESP.getFreePsram());
}

void setup() {
  initializeLogger();
  systemManager.initialize();
  displayManager.initialize();

  logMemory();
  Logger::info("[Main] Setup complete");
}

void loop() {
  systemManager.update();
  displayManager.update();
}

void serialLogCallback(Logger::Level level, const std::string& message) {
  if (!Serial) return;
  Serial.println(message.c_str());
  Serial.flush();
}

void initializeLogger() {
  Serial.begin(115200);
  while (!Serial)
    ;  // Wait for Serial port to connect

  Logger::setLogCallback(serialLogCallback);
  Logger::info(R"(
  ____  _ _________                            ___  _          __         
 / __ \(_) / ___/ /  ___ ____  ___ ____ ____  / _ \(_)__ ___  / /__ ___ __
/ /_/ / / / /__/ _ \/ _ `/ _ \/ _ `/ -_) __/ / // / (_-</ _ \/ / _ `/ // /
\____/_/_/\___/_//_/\_,_/_//_/\_, /\__/_/   /____/_/___/ .__/_/\_,_/\_, / 
                             /___/                    /_/          /___/  
    )");
  Logger::info("[Main] Logger initialized and ready.");
}
