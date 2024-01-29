// WebSocketManager.h
#pragma once

#include <AsyncWebSocket.h>

#include <memory>
#include <string>

class WebSocketManager {
 public:
  WebSocketManager();
  void initialize(AsyncWebServer* server);
  void send(const std::string& message);
  void sendToClient(uint32_t clientId, const std::string& message);

 private:
  std::unique_ptr<AsyncWebSocket> _ws;

  void onWebSocketEvent(AsyncWebSocket* server, AsyncWebSocketClient* client,
                        AwsEventType type, void* arg, uint8_t* data,
                        size_t len);
  void handleWebSocketData(AsyncWebSocket* server, AsyncWebSocketClient* client,
                           AwsFrameInfo* info, uint8_t* data, size_t len);
};
