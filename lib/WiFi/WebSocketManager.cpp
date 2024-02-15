// WebSocketManager.cpp
#include "WebSocketManager.h"

#include <string>

#include "Logger.h"

WebSocketManager::WebSocketManager() : _ws(new AsyncWebSocket("/ws")) {}

WebSocketManager::~WebSocketManager() {
  EventManager::getInstance().unsubscribe(this);
}

void WebSocketManager::initialize(AsyncWebServer* server) {
  _ws->onEvent([this](AsyncWebSocket* server, AsyncWebSocketClient* client,
                      AwsEventType type, void* arg, uint8_t* data, size_t len) {
    this->onWebSocketEvent(server, client, type, arg, data, len);
  });
  server->addHandler(_ws.get());

  EventManager::getInstance().subscribe(this);
}

void WebSocketManager::onEvent(const std::string& message) { send(message); }

void WebSocketManager::send(const std::string& message) {
  if (_ws) {
    // LOG_INFO("Sending message: " + message);
    _ws->textAll(message.c_str());
    // _ws->printfAll(message.c_str());
    // auto client = _ws->client(1);
    // if (client) {
    //   client->text(message.c_str());
    // }
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
    case WS_EVT_CONNECT: {
      std::ostringstream msg;
      msg << "ws[" << server->url() << "][" << client->id() << "] connect";
      LOG_INFO(msg.str());
      // Assuming you have a way to send messages to the client similar to
      // client->printf()
      std::ostringstream helloMsg;
      helloMsg << "Hello Client " << client->id() << " :)";
      client->printf(helloMsg.str().c_str());  // Make sure you have
      // equivalent functionality
      client->ping();
      break;
    }
    case WS_EVT_DISCONNECT: {
      std::ostringstream msg;
      msg << "ws[" << server->url() << "][" << client->id() << "] disconnect";
      LOG_INFO(msg.str());
      break;
    }
    case WS_EVT_ERROR: {
      std::ostringstream msg;
      msg << "ws[" << server->url() << "][" << client->id() << "] error("
          << *((uint16_t*)arg) << "): " << (char*)data;
      LOG_INFO(msg.str());
      break;
    }
    case WS_EVT_PONG: {
      std::ostringstream msg;
      msg << "ws[" << server->url() << "][" << client->id() << "] pong[" << len
          << "]: " << ((len) ? (char*)data : "");
      LOG_INFO(msg.str());
      break;
    }
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
  LOG_DEBUG("Handle WebSocket data: " + std::string((char*)data, len));
  // Handle WebSocket data event
}