// WebServerManager.h
#pragma once

#include <AsyncTCP.h>
#include <AsyncUDP.h>
#include <AsyncWebSocket.h>
#include <ESPAsyncDNSServer.h>
#include <ESPAsyncWebServer.h>

#include <ESPAsync_WiFiManager.hpp>
#include <memory>
#include <string>

#include "WebSocketManager.h"

class WebServerManager {
 public:
  WebServerManager();
  void initialize();
  void update();  // Call in main loop
  void sendWSMessage(const std::string& message);

 private:
  std::shared_ptr<AsyncWebServer> _server;
  AsyncDNSServer _dnsServer;  // needed by ESPAsyncWifiManager
  std::unique_ptr<ESPAsync_WiFiManager> _wifiManager;
  std::unique_ptr<WebSocketManager> _wsManager;

  int _port = 80;
  std::string _hostname;
  std::string _httpUsername;
  std::string _httpPassword;

  void loadConfig();
  void startWebServer(int port);
  void startmDNS(std::string hostname);
  void startWebSocket(std::shared_ptr<AsyncWebServer> server);
  void serveStaticFiles(AsyncWebServerRequest* request);
  const char* getMimeType(const String& path);
};
