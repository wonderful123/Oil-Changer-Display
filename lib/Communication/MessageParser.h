// MessageParser.h
#pragma once

#include <string>
#include <unordered_map>

class MessageParser {
 public:
  MessageParser();
  std::unordered_map<std::string, std::string> parseMessage(
      const std::string& message);

 private:
  bool validateChecksum(const std::string& message,
                        const std::string& checksum);
  bool isValidIdentifier(const std::string& identifier);
};
