// WebServerManager.cpp
#include <ArduinoJson.h>
#include <ESPmDNS.h>
#include <WiFi.h>

#include "ConfigManager.h"
#include "Logger.h"
#include "WebServerManager.h"

void WebServerManager::initialize() {
  WiFi.mode(WIFI_STA);
  loadConfig();
  connectToWifi(_ssid, _password);
  startWebServer(_port);
  _wsManager.initialize(_server.get());
  startmDNS(_hostname);
  startOTA();
  _server->begin();
}

void WebServerManager::loadConfig() {
  LOG_INFO("Configuring WebServer...");
  auto configManager = ConfigManager::getInstance();

  auto webServerConfig = configManager.getWebServerConfig();
  _port = webServerConfig["port"];
  _hostname = webServerConfig["hostname"].as<std::string>();

  auto wifiConfig = configManager.getWiFiConfig();
  _ssid = wifiConfig["ssid"].as<std::string>();
  _password = wifiConfig["password"].as<std::string>();
}

void WebServerManager::update() { _otaUpdateManager.update(); }

void WebServerManager::startWebServer(int port) {
  _server = std::make_shared<AsyncWebServer>(port);
  _server->serveStatic("/", LittleFS, "/www/");

  _server->on("/", HTTP_GET, [this](AsyncWebServerRequest* request) {
    request->send(LittleFS, "/index.html", "text/html");
  });

  // Generic handler for all other files
  _server->onNotFound(
      [this](AsyncWebServerRequest* request) { serveStaticFiles(request); });
  LOG_INFO("Started WebServer on port: " + std::to_string(_port));
}

void WebServerManager::startmDNS(std::string hostname) {
  if (!MDNS.begin(hostname.c_str())) {
    LOG_ERROR("Error setting up MDNS responder!");
  }
  MDNS.addService("http", "tcp", 80);
  LOG_INFO("mDNS server set up on hostname: http://" + hostname + ".local");
}

void WebServerManager::connectToWifi(std::string ssid, std::string password) {
  _wifiManager = std::unique_ptr<AsyncWiFiManager>(
      new AsyncWiFiManager(_server.get(), _dnsServer.get()));
  _wifiManager->autoConnect("Oil Change Display");

  WiFi.mode(WIFI_STA);  // Optional
  WiFi.begin(ssid.c_str(), password.c_str());
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(100);
  }

  Serial.println("\nConnected to the WiFi network");
  Serial.print("Local ESP32 IP: ");
  Serial.println(WiFi.localIP());
}

void WebServerManager::startOTA() { _otaUpdateManager.initialize(_server); }

void WebServerManager::sendWSMessage(const std::string& message) {
  _wsManager.send(message);
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