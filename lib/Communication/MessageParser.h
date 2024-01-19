// MessageParser.h
#pragma once

#include <string>
#include <unordered_map>

class MessageData;

class MessageParser {
 public:
  static MessageData parseMessage(const std::string& message);

 private:
  static bool validateChecksum(const std::string& message,
                        const std::string& checksum);
  static bool isValidIdentifier(const std::string& identifier);
};
