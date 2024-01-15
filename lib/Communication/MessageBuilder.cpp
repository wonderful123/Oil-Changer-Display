// MessageBuilder.cpp
#include "MessageBuilder.h"

MessageBuilder::MessageBuilder() {
  // Constructor implementation, if needed
}

std::string MessageBuilder::buildMessage(const std::string& payload) {
  // Calculate checksum
  unsigned int checksum = calculateChecksum(payload);

  // Build the message
  std::string message = "<" + payload + ";" + std::to_string(checksum) + ">";
  return message;
}

unsigned int MessageBuilder::calculateChecksum(const std::string& payload) {
  unsigned int sum = 0;
  for (char c : payload) {
    sum += static_cast<unsigned int>(c);
  }
  return sum % 256;  // Assuming a byte-size checksum
}
