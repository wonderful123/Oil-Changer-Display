// Logger.cpp
#include "Logger.h"

#include <cstdio>
#include <cstring>
#include <mutex>

// Initialize static members
Logger::LogCallback Logger::_log_callback = nullptr;

/**
 * Sets the callback function used for logging.
 *
 * @param callback The function to be called when a log message is issued.
 */
void Logger::setLogCallback(LogCallback callback) { _log_callback = callback; }

/**
 * Logs a message at the specified level. If the message level is at or above
 * the current log level, the message is formatted and passed to the log
 * callback.
 *
 * @param level The severity level of the message.
 * @param message The message to log.
 */
void Logger::log(Level level, const std::string &message) {
#if defined(LOGGER_LEVEL_DEBUG) || defined(LOGGER_LEVEL_INFO) || \
    defined(LOGGER_LEVEL_WARN) || defined(LOGGER_LEVEL_ERROR)
  {
    formatMessage(level, message);

    if (_log_callback) {
      _log_callback(level, message);
    }
  }
#endif
}

/**
 * Converts a log level to its string representation.
 *
 * @param level The log level to convert.
 * @return String representation of the log level.
 */
const std::string Logger::levelToString(Level level) {
  switch (level) {
    case DEBUG:
      return "DEBUG";
    case INFO:
      return "INFO";
    case WARN:
      return "WARN";
    case ERROR:
      return "ERROR";
    default:
      return "UNKNOWN";
  }
}

/**
 * Retrieves the ANSI color code for a given log level. This is dependent
 * on LOGGER_USE_COLOR being defined.
 *
 * @param level The log level.
 * @return The ANSI color code as a string.
 */
const std::string Logger::getColorCodeForLevel(Level level) {
#ifdef LOGGER_USE_COLOR
  switch (level) {
    case DEBUG:
      return "\033[34m";  // Blue for DEBUG
    case INFO:
      return "\033[32m";  // Green for INFO
    case WARN:
      return "\033[33m";  // Yellow for WARN
    case ERROR:
      return "\033[31m";  // Red for ERROR
    default:
      return "\033[0m";  // Default color
  }
#else
  return "";
#endif
}

/**
 * Formats the log message by appending the log level and color coding to it.
 *
 * @param level The level of the log message.
 * @param message The message to format.
 */
std::string Logger::formatMessage(Level level, const std::string &message) {
  std::ostringstream formattedMessage;

  const std::string colorCode = getColorCodeForLevel(level);
  const std::string levelStr = levelToString(level);
  const std::string standardColor = "\033[0m";

  formattedMessage << colorCode << "[" << levelStr << "]"
#ifdef LOGGER_USE_COLOR
                   << standardColor
#endif
                   << " " << message;

  return formattedMessage.str();
}

// Logging methods
// Each method checks if the corresponding log level is enabled before logging.

void Logger::debug(const std::string &message) {
#if defined(LOGGER_LEVEL_DEBUG)
  log(DEBUG, message);
#endif
}

void Logger::info(const std::string &message) {
#if defined(LOGGER_LEVEL_DEBUG) || defined(LOGGER_LEVEL_INFO)
  log(INFO, message);
#endif
}

void Logger::warn(const std::string &message) {
#if defined(LOGGER_LEVEL_DEBUG) || defined(LOGGER_LEVEL_INFO) || \
    defined(LOGGER_LEVEL_WARN)
  log(WARN, message);
#endif
}

void Logger::error(const std::string &message) {
#if defined(LOGGER_LEVEL_DEBUG) || defined(LOGGER_LEVEL_INFO) || \
    defined(LOGGER_LEVEL_WARN) || defined(LOGGER_LEVEL_ERROR)
  log(ERROR, message);
#endif
}
