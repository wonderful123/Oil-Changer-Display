// MessageParser.cpp
#include "MessageParser.h"

#include <sstream>
#include <vector>

#include "Config.h"
#include "Logger.h"

MessageParser::MessageParser() {
  // Constructor implementation (if needed)
}

std::unordered_map<std::string, std::string> MessageParser::parseMessage(
    const std::string& message) {
  std::unordered_map<std::string, std::string> data;

  if (message.empty() || message.front() != '<' || message.back() != '>') {
    Logger::error("[MessageParser] Invalid message format");
    return data;  // Return empty map
  }

  // Remove the enclosing '<' and '>'
  std::string content = message.substr(1, message.length() - 2);

  // Extract the identifier part (e.g., "Display1;")
  size_t idEndPos = content.find(';');
  if (idEndPos == std::string::npos) {
    Logger::error(
        "[MessageParser] Invalid message format - missing identifier");
    return data;
  }
  std::string identifier = content.substr(0, idEndPos + 1);

  if (!isValidIdentifier(identifier)) {
    Logger::error("[MessageParser] Identifier mismatch");
    return std::unordered_map<std::string, std::string>();  // Return empty map
  }

  // Process the payload
  std::string payload = content.substr(idEndPos + 1);
  std::string extractedChecksum;
  size_t lastSemicolonPos = payload.rfind(';');
  if (lastSemicolonPos != std::string::npos) {
    extractedChecksum = payload.substr(lastSemicolonPos + 1);
    payload =
        payload.substr(0, lastSemicolonPos);  // Exclude checksum from payload
  }

  // Validate checksum
  if (!validateChecksum(payload, extractedChecksum)) {
    Logger::error("[MessageParser] Checksum validation failed");
    return std::unordered_map<std::string, std::string>();  // Return empty map
  }

  // Parse payload
  std::stringstream ss(payload);
  std::string token;
  while (getline(ss, token, ';')) {
    size_t delimiterPos = token.find(':');
    if (delimiterPos != std::string::npos) {
      std::string key = token.substr(0, delimiterPos);
      std::string value = token.substr(delimiterPos + 1);
      data[key] = value;
    }
  }

  return data;
}

bool MessageParser::validateChecksum(const std::string& payload,
                                     const std::string& receivedChecksumStr) {
  unsigned int sum = 0;
  for (char c : payload) {
    sum += static_cast<unsigned int>(c);
  }
  unsigned int calculatedChecksum = sum % 256;

  // Convert receivedChecksumStr to an integer
  unsigned int receivedChecksum =
      static_cast<unsigned int>(std::stoi(receivedChecksumStr));

  return calculatedChecksum == receivedChecksum;
}

bool MessageParser::isValidIdentifier(const std::string& identifier) {
  return identifier == DEVICE_IDENTIFIER;
}
