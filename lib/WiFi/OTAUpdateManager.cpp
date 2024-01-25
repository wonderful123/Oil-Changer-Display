// OTAUpdateManager.cpp
#include <Arduino.h>

#include <functional>

#include "Logger.h"
#include "OTAUpdateManager.h"

void OTAUpdateManager::initialize(std::shared_ptr<AsyncWebServer> webServer) {
  _webServer = webServer;

  _webServer->on("/update", HTTP_GET, [](AsyncWebServerRequest* request) {
    request->send(200, "text/plain", "Hi! This is ElegantOTA AsyncDemo.");
  });

  ElegantOTA.begin(webServer.get());

  // ElegantOTA callbacks
  // Set up ElegantOTA callbacks using std::bind
  ElegantOTA.onStart(std::bind(&OTAUpdateManager::onOTAStart, this));
  ElegantOTA.onProgress(std::bind(&OTAUpdateManager::onOTAProgress, this,
                                  std::placeholders::_1,
                                  std::placeholders::_2));
  ElegantOTA.onEnd(
      std::bind(&OTAUpdateManager::onOTAEnd, this, std::placeholders::_1));

  LOG_INFO("OTA server started");
}

void OTAUpdateManager::update() { ElegantOTA.loop(); }

void OTAUpdateManager::onOTAStart() {
  // Log when OTA has started
  LOG_INFO("OTA update started!");
}

void OTAUpdateManager::onOTAProgress(size_t current, size_t final) {
  // Log every 1 second
  if (millis() - _otaProgressMillis > 1000) {
    _otaProgressMillis = millis();
    Logger::info("OTA Progress Current: " + std::to_string(current) +
                 " bytes, Final: " + std::to_string(final) + " bytes\n");
  }
}

void OTAUpdateManager::onOTAEnd(bool success) {
  // Log when OTA has finished
  if (success) {
    Logger::info("OTA update finished successfully");
  } else {
    Logger::error("There was an error during OTA update");
  }
}