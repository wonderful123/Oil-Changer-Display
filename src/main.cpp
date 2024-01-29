// main.cpp
#include <Arduino.h>

#include <string>

#include "DebugUtils.h"
#include "DisplayManager.h"
#include "Logger.h"
#include "SystemManager.h"
#include "WebServerManager.h"

// Foward declarations
void serialLogCallback(Logger::Level level, const std::string& message);
void initializeLogger();

// Global Objects
DisplayManager displayManager;
SystemManager systemManager;
WebServerManager webServerManager;

void serialLogCallback2(Logger::Level level, const std::string& message) {
  webServerManager.sendWSMessage(message);
  if (!Serial) return;
  Serial.println(message.c_str());
  Serial.flush();
}

void setup() {
  initializeLogger();
  displayManager.initialize();
  systemManager.initialize();
  webServerManager.initialize();

  Logger::setLogCallback(serialLogCallback2);
  DebugUtils::logMemoryUsage();
  Logger::info("[Main] Setup complete");
}

void loop() {
  displayManager.update();
  systemManager.update();
  webServerManager.update();
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
