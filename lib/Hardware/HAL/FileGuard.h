// FileGuard.h
#pragma once

#include <string>

#include "IFileHandler.h"

class FileGuard {
 public:
  explicit FileGuard(IFileHandler *handler, const std::string &path,
                     const std::string &mode)
      : _fileHandler(handler), _isOpen(handler->open(path, mode)) {}

  ~FileGuard() {
    if (_isOpen) _fileHandler->close();
  }

  bool isOpen() const { return _isOpen; }
  std::string read() { return _fileHandler->read(); }

 private:
  IFileHandler *_fileHandler;
  bool _isOpen;
};