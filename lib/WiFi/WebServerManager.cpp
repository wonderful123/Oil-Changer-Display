// WebServerManager.cpp
#include <ArduinoJson.h>
#include <ESPmDNS.h>

#include "ConfigManager.h"
#include "Logger.h"
#include "WebServerManager.h"

WebServerManager::WebServerManager() : _dnsServer() {}

void WebServerManager::initialize() {
  // Load configuration from non-volatile storage
  loadConfig();

  // Initialize Async WiFi Manager with callback
  _wifiManager = std::unique_ptr<ESPAsync_WiFiManager>(
      new ESPAsync_WiFiManager(_server.get(), &_dnsServer, _hostname.c_str()));
  _wifiManager->setConfigPortalTimeout(180);  // Set timeout for config portal
  _wifiManager->autoConnect(
      "OilChangerDisplay");  // This will block until connected to WiFi

  startWebServer(_port);
  startWebSocket(_server);
  startmDNS(_hostname);
  _server->begin();
}

void WebServerManager::loadConfig() {
  LOG_INFO("Configuring WebServer...");
  auto configManager = ConfigManager::getInstance();

  auto webServerConfig = configManager.getWebServerConfig();
  _port = webServerConfig["port"];
  _hostname = webServerConfig["hostname"].as<std::string>();
}

void WebServerManager::update() {}

void WebServerManager::startWebServer(int port) {
  _server = std::make_shared<AsyncWebServer>(port);
  _server->serveStatic("/", LittleFS, "/www/").setDefaultFile("index.html");

  // Handling not found with custom 404 page
  _server->onNotFound([](AsyncWebServerRequest* request) {
    request->send(404, "text/html", "404: Not Found");
  });

  LOG_INFO("Started WebServer on port " + std::to_string(_port));
}

void WebServerManager::startmDNS(std::string hostname) {
  if (!MDNS.begin(hostname.c_str())) {
    LOG_ERROR("Error setting up MDNS responder!");
  }
  MDNS.addService("http", "tcp", 80);
  LOG_INFO("mDNS server set up on hostname: http://" + hostname + ".local");
}

void WebServerManager::startWebSocket(std::shared_ptr<AsyncWebServer> server) {
  _wsManager = std::unique_ptr<WebSocketManager>(new WebSocketManager());
  _wsManager->initialize(server.get());
}

void WebServerManager::sendWSMessage(const std::string& message) {
  if (_wsManager) {  // Check if _wsManager is initialized
    _wsManager->send(message);
  } else {
    LOG_ERROR("WebsocketManager not initialized");
  }
}

void WebServerManager::serveStaticFiles(AsyncWebServerRequest* request) {
  String path = request->url();
  String mimeType = getMimeType(path);
  if (LittleFS.exists(path)) {
    request->send(LittleFS, path, mimeType);
  } else {
    request->send(404, "text/plain", "Not found");
  }
}

const char* WebServerManager::getMimeType(const String& path) {
  if (path.endsWith(".html"))
    return "text/html";
  else if (path.endsWith(".css"))
    return "text/css";
  else if (path.endsWith(".js"))
    return "application/javascript";
  else if (path.endsWith(".json"))
    return "application/json";
  else if (path.endsWith(".png"))
    return "image/png";
  else if (path.endsWith(".jpg"))
    return "image/jpeg";
  else if (path.endsWith(".gif"))
    return "image/gif";
  // add more MIME types as needed
  return "text/plain";
}