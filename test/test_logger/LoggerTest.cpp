#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <sstream>
#include <string>

#include "Logger.h"

// Global variable for capturing log messages
std::stringstream capturedLog;

void logCallback(Logger::Level level, const std::string &message) {
  capturedLog << message << "\n";
}

class LoggerTest : public ::testing::Test {
 protected:
  void SetUp() override {
    // Clear the captured log
    capturedLog.str("");
    capturedLog.clear();

    // Set logger callback for testing
    Logger::setLogCallback(logCallback);
  }

  void TearDown() override {
    // You can restore the original logger callback here if needed
  }
};

TEST_F(LoggerTest, CallbackInvocationTest) {
  Logger::info("Test message");
  EXPECT_THAT(capturedLog.str(), ::testing::HasSubstr("Test message"));
}

TEST_F(LoggerTest, MessageFormattingTest) {
  Logger::warn("Warning message");

  // Check if the string contains the expected parts
  std::string expectedLevel = "[WARN]";
  std::string expectedMessage = "Warning message";

  std::string actualLog = capturedLog.str();
  std::size_t levelPos = actualLog.find(expectedLevel);
  std::size_t messagePos = actualLog.find(expectedMessage);

  // Ensure the level and message are found and in the correct order
  ASSERT_NE(levelPos, std::string::npos);
  ASSERT_NE(messagePos, std::string::npos);
  EXPECT_GT(messagePos, levelPos);
}

TEST_F(LoggerTest, ThreadSafetyTest) {
  std::thread thread1([] { Logger::info("Message from thread 1"); });
  std::thread thread2([] { Logger::info("Message from thread 2"); });

  thread1.join();
  thread2.join();

  // Validate that both messages are logged without interference
  EXPECT_THAT(capturedLog.str(), ::testing::HasSubstr("Message from thread 1"));
  EXPECT_THAT(capturedLog.str(), ::testing::HasSubstr("Message from thread 2"));
}

TEST_F(LoggerTest, MessageTruncationTest) {
  std::string longMessage(300, 'a');  // Longer than LOGGER_MAX_MESSAGE_LENGTH
  Logger::info(longMessage);

  EXPECT_LT(capturedLog.str().length(), 300);
}
