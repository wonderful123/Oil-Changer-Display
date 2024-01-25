// WebServerManager.h
#pragma once

#include <AsyncTCP.h>
#include <AsyncUDP.h>
#include <AsyncWebSocket.h>
#include <DNSServer.h>
#include <ESPAsyncWebServer.h>
#include <ESPAsyncWiFiManager.h>
#include <WiFi.h>

#include <memory>
#include <string>

#include "OTAUpdateManager.h"
#include "WebSocketManager.h"

class WebServerManager {
 public:
  void initialize();
  void update();  // Call in main loop
  void sendWSMessage(const std::string& message);

 private:
  std::shared_ptr<AsyncWebServer> _server;
  std::unique_ptr<DNSServer> _dnsServer;  // needed by ESPAsyncWifiManager
  std::unique_ptr<AsyncWiFiManager> _wifiManager;

  OTAUpdateManager _otaUpdateManager;
  WebSocketManager _wsManager;

  int _port = 80;
  std::string _ssid;
  std::string _password;
  std::string _hostname;
  std::string _httpUsername;
  std::string _httpPassword;

  void loadConfig();
  void startWebServer(int port);
  void startmDNS(std::string hostname);
  void connectToWifi(std::string ssid, std::string password);
  void startOTA();

  void serveStaticFiles(AsyncWebServerRequest* request);
  const char* getMimeType(const String& path);
};
