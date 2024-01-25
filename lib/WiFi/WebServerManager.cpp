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
  WiFi.mode(WIFI_STA);  // Optional
  WiFi.begin(ssid.c_str(), password.c_str());
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(100);
  }

  Serial.println("\nConnected to the WiFi network");
  Serial.print("Local ESP32 IP: ");
  Serial.println(WiFi.localIP());
  // _wifiManager = std::unique_ptr<WiFiManager>(
  //     new WiFiManager(_server.get(), _dnsServer.get()));
  // LOG_INFO("Connecting to SSID: " + ssid);
  // _wifiManager = new ESPAsync_WiFiManager_Lite();
  // _wifiManager->begin();
  // _wifiManager->autoConnect(ssid.c_str(), password.c_str());
}

void WebServerManager::startOTA() { _otaUpdateManager.initialize(_server); }

void WebServerManager::sendWSMessage(const std::string& message) {
  _wsManager.send(message);
}