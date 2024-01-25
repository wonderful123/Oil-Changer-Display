// OTAUpdateManager.h
#pragma once

#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <ElegantOTA.h>

#include <memory>

class OTAUpdateManager {
 public:
  void initialize(std::shared_ptr<AsyncWebServer> webServer);
  void update();

 private:
  std::shared_ptr<AsyncWebServer> _webServer;
  unsigned long _otaProgressMillis = 0;

  void onOTAStart();
  void onOTAProgress(size_t current, size_t final);
  void onOTAEnd(bool success);
};