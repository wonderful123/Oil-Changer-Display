#include "DataMessageHandler.h"

#include <algorithm>
#include <cctype>  // For std::isdigit
#include <sstream>

#include "DataTracker.h"
#include "Logger.h"

DataMessageHandler::DataMessageHandler(DataTracker& tracker)
    : _dataTracker(tracker) {}

void DataMessageHandler::handleMessage(const std::string& message) {
  if (message.empty()) return;  // Early return if message is empty

  // Message format is "<IDENTIFIER;key:value;...;CKS:xxx>"
  size_t start = message.find(';') + 1;
  size_t cksStart = message.rfind(";CKS:");
  size_t end = message.find('>', cksStart);

  if (start == std::string::npos || cksStart == std::string::npos ||
      start >= cksStart) {
    LOG_ERROR("Invalid message format.");
    return;
  }

  std::string payload = message.substr(start, cksStart - start);
  std::string checksumStr = message.substr(cksStart + 5, end - (cksStart + 5));

  // Validate the checksum is numerical
  if (!std::all_of(checksumStr.begin(), checksumStr.end(), ::isdigit)) {
    LOG_ERROR("Invalid checksum format.");
    return;
  }

  unsigned int receivedChecksum = std::stoi(checksumStr);
  if (calculateChecksum(payload) != receivedChecksum) {
    LOG_ERROR("Checksum mismatch.");
    return;
  }

  parseAndSetData(payload);
}

void DataMessageHandler::parseAndSetData(const std::string& payload) {
  std::istringstream iss(payload);
  std::string token;
  while (std::getline(iss, token, ';')) {
    auto delimiterPos = token.find(':');
    if (delimiterPos != std::string::npos) {
      std::string key = token.substr(0, delimiterPos);
      std::string value = token.substr(delimiterPos + 1);
      _dataTracker.setData(key, value);
    }
  }
}

unsigned int DataMessageHandler::calculateChecksum(const std::string& payload) {
  unsigned int checksum = 0;
  for (char c : payload) {
    checksum += static_cast<unsigned char>(c);
  }
  return checksum % 256;
}
