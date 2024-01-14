#include "MessageBuilder.h"

#include "Logger.h"

MessageBuilder::MessageBuilder() {
  // Constructor implementation
}

std::string MessageBuilder::buildMessage(const std::string& payload) {
  // Build the message with appropriate format and protocol
  std::string message = "<" + payload + ">";
  // Add any additional formatting or protocol-specific details
  return message;
}