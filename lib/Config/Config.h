// Config.h
#pragma once

#include "HAL/HardwarePinConfig.h"

// Device Identifier
constexpr char DEVICE_IDENTIFIER[] = "Display1";
constexpr char SERIAL_ID[] = "Serial1";
constexpr int SERIAL_BAUD = 115200;
constexpr int SERIAL_RXD_PIN = 36;
constexpr int SERIAL_TXD_PIN = 37;
constexpr int SERIAL_UART_PORT = 0;

extern HardwarePinConfig serialConfig;