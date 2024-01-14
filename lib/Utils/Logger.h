// Logger.h
#pragma once

#pragma once

/**
 * @file Logger.h
 * @brief The Logger class provides a logging utility for outputting log
 * messages at different severity levels.
 *
 * The Logger class allows setting a callback function to be called when a log
 * message is issued. It supports logging messages at different severity levels,
 * including DEBUG, INFO, WARN, and ERROR. The log messages are formatted with
 * the log level and color coding, and then passed to the log callback function.
 *
 * The Logger class also provides methods for converting a log level to its
 * string representation and retrieving the ANSI color code for a given log
 * level.
 *
 * Example usage:
 * @code
 * Logger::setLogCallback(myLogCallback);
 * Logger::debug("This is a debug message");
 * Logger::info("This is an info message");
 * Logger::warn("This is a warning message");
 * Logger::error("This is an error message");
 * @endcode
 */

#include <atomic>
#include <mutex>
#include <sstream>
#include <string>

/************************************************
 *  Optional settings
 ***********************************************/

// Uncomment the desired log level for compile-time control
#define LOGGER_LEVEL_DEBUG
// #define LOGGER_LEVEL_INFO
// #define LOGGER_LEVEL_WARN
// #define LOGGER_LEVEL_ERROR

// Uncomment to enable colored log output
#define LOGGER_USE_COLOR

constexpr unsigned int LOGGER_MAX_MESSAGE_LENGTH = 256;

/************************************************
 *  Class definition
 ***********************************************/

/**
 * @class Logger
 * A thread-safe logger class designed for embedded systems.
 * Provides logging functionality with various levels like DEBUG, INFO, etc.
 * Supports compile-time log level control and optional color-coded output.
 *
 * Thread Safety:
 * This class is thread-safe. The internal state is protected using mutexes,
 * and atomic operations ensure consistent behavior in multi-threaded
 * environments.
 *
 * Usage Example:
 * Logger::setLogLevel(Logger::INFO);
 * Logger::info("This is an info message");
 */
class Logger {
 public:
  /**
   * Enum to represent different logging levels.
   */
  enum Level { DEBUG, INFO, WARN, ERROR };

  /**
   * Type definition for log callback function.
   */
  using LogCallback = void (*)(Level, const std::string &);

  /**
   * @brief Sets the callback function used for logging messages.
   *
   * The log callback function is invoked whenever a log message is issued. It
   * takes two parameters: the log level and the message to be logged. The
   * callback function should be implemented by the user and should handle the
   * logging of the message according to the desired behavior, such as writing
   * to a file, printing to the console, or sending the message over a network.
   * The function should have the following signature: \code void
   * logCallback(Logger::Level level, const char *message); \endcode The log
   * level parameter indicates the severity level of the log message, and the
   * message parameter contains the actual log message to be logged. The user
   * can use this information to customize the logging behavior based on the log
   * level, such as filtering out certain levels or applying different
   * formatting based on the severity.
   *
   * @param callback Function pointer to the log handling function. This should
   * be a function that matches the Logger::LogCallback signature.
   *
   * @example
   * Implementation of a log handling function, e.g., write the log message to a
   * file: \code void myLogCallback(Logger::Level level, const char *message) {
   *   std::ofstream logFile("log.txt", std::ios::app);
   *   logFile << "[" << Logger::levelToString(level) << "] " << message <<
   * std::endl; logFile.close();
   * }
   *
   * To set the log callback function, pass the function pointer to the
   * \code
   * setLogCallback method: Logger::setLogCallback(myLogCallback);
   * \endcode
   */
  static void setLogCallback(LogCallback callback);

  /**
   * Logs a message at the specified level.
   * This function checks against the current log level and formats the message.
   *
   * @param level Log level of the message.
   * @param message The message to log.
   */
  static void log(Level level, const std::string &message);

  /**
   * Converts log level enum to a corresponding string.
   *
   * @param level Log level to convert.
   * @return A string representation of the log level.
   */
  static const std::string levelToString(Level level);

  // Logging methods for different levels

  /**
   * Logs a debug message.
   *
   * @param message The debug message to log.
   */
  static void debug(const std::string &message);

  /**
   * Logs an info message.
   *
   * @param message The info message to log.
   */
  static void info(const std::string &message);

  /**
   * Logs a warning message.
   *
   * @param message The warning message to log.
   */
  static void warn(const std::string &message);

  /**
   * Logs an error message.
   *
   * @param message The error message to log.
   */
  static void error(const std::string &message);

 private:
  static LogCallback _log_callback;  ///< Function pointer to the log callback.

  /**
   * Formats a log message with the log level and color coding.
   *
   * @param level The level of the log message.
   * @param message The message to format.
   */
  static std::string formatMessage(Level level, const std::string &message);

  /**
   * Retrieves the ANSI color code for a given log level.
   *
   * @param level The log level.
   * @return ANSI color code as a string.
   */
  static const std::string getColorCodeForLevel(Level level);
};
