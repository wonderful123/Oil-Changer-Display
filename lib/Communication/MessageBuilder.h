// MessageBuilder.h
#pragma once

#include <string>

// MessageBuilder: Constructs messages in the required format. The buildMessage
// method encapsulates the payload in the protocol-specific message structure.

class MessageBuilder {
 public:
  MessageBuilder();
  std::string buildMessage(const std::string& payload);

 private:
  unsigned int calculateChecksum(const std::string& payload);
};
