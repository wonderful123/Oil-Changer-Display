// MessageParser.h
#pragma once

#include <string>
#include <utility>

#include "MessageData.h"

class MessageParser {
 public:
  static MessageData parseMessage(const std::string& message);
  static bool validateChecksum(const std::string& payload,
                               const std::string& receivedChecksumStr);
  static bool isValidIdentifier(const std::string& identifier);
  static std::string extractContent(const std::string& message);
  static std::pair<std::string, std::string> extractIdentifierAndPayload(
      const std::string& content);
  static std::pair<std::string, std::string> extractPayloadAndChecksum(
      const std::string& payload);
  static void parsePayloadToData(const std::string& payload, MessageData& data);
};
