// WebSocketManager.h
#pragma once

#include <AsyncWebSocket.h>

#include <memory>
#include <string>

#include "EventManager/EventManager.h"

class WebSocketManager : public IEventListener {
 public:
  WebSocketManager();
  ~WebSocketManager();

  void initialize(AsyncWebServer* server);
  void send(const std::string& message);
  void sendToClient(uint32_t clientId, const std::string& message);

 private:
  std::unique_ptr<AsyncWebSocket> _ws;

  virtual void onEvent(const std::string& message) override;
  void onWebSocketEvent(AsyncWebSocket* server, AsyncWebSocketClient* client,
                        AwsEventType type, void* arg, uint8_t* data,
                        size_t len);
  void handleWebSocketData(AsyncWebSocket* server, AsyncWebSocketClient* client,
                           AwsFrameInfo* info, uint8_t* data, size_t len);
};
