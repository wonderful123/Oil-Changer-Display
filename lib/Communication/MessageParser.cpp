// MessageParser.cpp
#include <sstream>
#include <vector>

#include "Config.h"
#include "Logger.h"
#include "MessageData.h"
#include "MessageParser.h"

MessageData MessageParser::parseMessage(const std::string& message) {
  MessageData data;

  if (message.empty() || message.front() != '<' || message.back() != '>') {
    LOG_DEBUG("[MessageParser] Message is empty or invalid format");
    return data;
  }

  std::string content = extractContent(message);
  auto result = extractIdentifierAndPayload(content);
  const auto& identifier = result.first;
  const auto& payload = result.second;

  if (!isValidIdentifier(identifier)) {
    Logger::error("[MessageParser] Identifier mismatch");
    return MessageData();
  }

  auto payloadAndChecksum = extractPayloadAndChecksum(payload);
  const auto& parsedPayload = payloadAndChecksum.first;
  const auto& extractedChecksum = payloadAndChecksum.second;

  if (!validateChecksum(parsedPayload, extractedChecksum)) {
    Logger::error("[MessageParser] Checksum validation failed");
    return MessageData();
  }

  parsePayloadToData(parsedPayload, data);

  return data;
}

std::string MessageParser::extractContent(const std::string& message) {
  // Remove the enclosing '<' and '>'
  return message.substr(1, message.length() - 2);
}

std::pair<std::string, std::string> MessageParser::extractIdentifierAndPayload(
    const std::string& content) {
  size_t idEndPos = content.find(';');
  if (idEndPos == std::string::npos) {
    Logger::error(
        "[MessageParser] Invalid message format - missing identifier");
    return {"", ""};
  }
  return {content.substr(0, idEndPos), content.substr(idEndPos + 1)};
}

std::pair<std::string, std::string> MessageParser::extractPayloadAndChecksum(
    const std::string& payload) {
  size_t cksTagPos = payload.rfind(";CKS:");
  if (cksTagPos == std::string::npos) {
    Logger::error("[MessageParser] Invalid message format - missing checksum");
    return {"", ""};
  }
  return {payload.substr(0, cksTagPos),
          payload.substr(cksTagPos + 5)};  // 5 is the length of ";CKS:"
}

void MessageParser::parsePayloadToData(const std::string& payload,
                                       MessageData& data) {
  std::stringstream ss(payload);
  std::string token;
  while (std::getline(ss, token, ';')) {
    size_t delimiterPos = token.find(':');
    if (delimiterPos != std::string::npos) {
      std::string key = token.substr(0, delimiterPos);
      std::string value = token.substr(delimiterPos + 1);
      data.data()[key] = value;
    }
  }
}

bool MessageParser::validateChecksum(const std::string& payload,
                                     const std::string& receivedChecksumStr) {
  unsigned int sum = 0;
  for (char c : payload) {
    sum += static_cast<unsigned int>(c);
  }
  unsigned int calculatedChecksum = sum % 256;

  unsigned int receivedChecksum =
      static_cast<unsigned int>(std::stoi(receivedChecksumStr));
  if (calculatedChecksum != receivedChecksum) {
    LOG_ERROR(
        "Checksum error. Calculated: " + std::to_string(calculatedChecksum) +
        ", Expected: " + std::to_string(receivedChecksum));
    return false;
  }

  return true;
}

bool MessageParser::isValidIdentifier(const std::string& identifier) {
  return identifier == DEVICE_IDENTIFIER;
}