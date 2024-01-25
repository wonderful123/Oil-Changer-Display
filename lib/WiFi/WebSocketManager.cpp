// WebSocketManager.cpp
#include "WebSocketManager.h"

WebSocketManager::WebSocketManager() : _ws(new AsyncWebSocket("/ws")) {}

void WebSocketManager::initialize(AsyncWebServer* server) {
  _ws->onEvent([this](AsyncWebSocket* server, AsyncWebSocketClient* client,
                      AwsEventType type, void* arg, uint8_t* data, size_t len) {
    this->onWebSocketEvent(server, client, type, arg, data, len);
  });
  server->addHandler(_ws.get());
}

void WebSocketManager::send(const std::string& message) {
  if (_ws) {
    _ws->textAll(message.c_str());
  }
}

void WebSocketManager::sendToClient(uint32_t clientId,
                                    const std::string& message) {
  auto client = _ws->client(clientId);
  if (client) {
    client->text(message.c_str());
  }
}

void WebSocketManager::onWebSocketEvent(AsyncWebSocket* server,
                                        AsyncWebSocketClient* client,
                                        AwsEventType type, void* arg,
                                        uint8_t* data, size_t len) {
  switch (type) {
    case WS_EVT_CONNECT:
      Serial.printf("ws[%s][%u] connect\n", server->url(), client->id());
      client->printf("Hello Client %u :)", client->id());
      client->ping();
      break;
    case WS_EVT_DISCONNECT:
      Serial.printf("ws[%s][%u] disconnect\n", server->url(), client->id());
      break;
    case WS_EVT_ERROR:
      Serial.printf("ws[%s][%u] error(%u): %s\n", server->url(), client->id(),
                    *((uint16_t*)arg), (char*)data);
      break;
    case WS_EVT_PONG:
      Serial.printf("ws[%s][%u] pong[%u]: %s\n", server->url(), client->id(),
                    len, (len) ? (char*)data : "");
      break;
    case WS_EVT_DATA:
      handleWebSocketData(server, client, static_cast<AwsFrameInfo*>(arg), data,
                          len);
      break;
  }
}

void WebSocketManager::handleWebSocketData(AsyncWebSocket* server,
                                           AsyncWebSocketClient* client,
                                           AwsFrameInfo* info, uint8_t* data,
                                           size_t len) {
  // Handle WebSocket data event
  // This function should parse the data and respond appropriately
  // ...
}