// Config.cpp
#include "Config.h"

HardwarePinConfig serialConfig2({{"RXD", SERIAL_RXD_PIN},
                                 {"TXD", SERIAL_TXD_PIN}},
                                SERIAL_ID, "Serial",
                                {{"uartPort", std::to_string(SERIAL_UART_PORT)},
                                 {"baud", std::to_string(SERIAL_BAUD)}});

HardwarePinConfig serialConfig({{"RXD", 36}, {"TXD", 37}}, "Serial1", "Serial",
                               {{"uartPort", "0"}, {"baud", "115200"}});