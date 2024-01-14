# Oil Change Display Project

## Overview
This document provides an overview of the Oil Change Display project, a component of the larger oil changer system. This project is built on the ESP32 S3 LCD platform, offering a user-friendly display for oil change processes.

## Hardware Specifications
- **Microcontroller:** ESP32 S3
- **Display:** LCD
- **Memory:** 16MB Flash, 8MB PSRAM

## Key Files and Configuration

### `board-esp32s3-16Mb-8MbPSRAM.json`
- **Description:** This is the PlatformIO board configuration file for the ESP32 S3 with 16MB Flash and 8MB PSRAM. It defines the board's specifications and memory layout.
- **Usage:** Copy this file to the appropriate directory in your PlatformIO project to ensure the IDE correctly recognizes the board's configuration.

### `partition-table-16Mb.csv`
- **Description:** Specifies the partition table for the ESP32 S3 with 16MB memory. It details the memory allocation for various components of the system.
- **Usage:** This file is used to configure the memory partitions during the firmware flashing process.

### `data\UIHardwareConfig.json`
- **Description:** Specifies the pins and settings for the display and touchscreen.
- **Usage:** This file is loaded with the config manager using ArduinoJson. The values are then accessed through the display manager and touch screen classes.



# System Components Overview

This document provides an overview of the key components within our system, outlining their responsibilities and roles.

## CommunicationManager

- **Responsibilities**: Manages all communication-related tasks, including sending and receiving messages.
- **Functions**: Handles the formatting and parsing of communication data.

## DataManager

- **Responsibilities**: Manages data storage and retrieval.
- **Functions**: Responsible for loading data from and saving data to various sources, ensuring data integrity and consistency.

## UIManager

- **Responsibilities**: Manages and updates the user interface.
- **Functions**: Coordinates the interaction between different UI elements and ensures the UI reflects the current state of the system.

## ElementController

- **Responsibilities**: Manages individual UI elements.
- **Functions**: Handles the control logic for UI components (e.g., sliders, buttons), ensuring UI elements react appropriately to user interactions and system events.

## EventDispatcher

- **Responsibilities**: Manages event-based communication within the system.
- **Functions**: Responsible for subscribing to, unsubscribing from, and dispatching events, facilitating decoupled communication between different parts of the system.

## ConfigHandler

- **Responsibilities**: Manages the configuration settings of the system.
- **Functions**: Loads and parses configuration files, providing interfaces for accessing and updating configuration data.

## CommandHandler

- **Responsibilities**: Processes and handles incoming commands.
- **Functions**: Deciphers command content and delegates tasks to appropriate system components, ensuring correct execution of commands and handling command-related responses.

## MessageParser

- **Responsibilities**: Parses incoming messages into a usable format.
- **Functions**: Extracts relevant information from messages for further processing and ensures message integrity and validity.

## MessageBuilder

- **Responsibilities**: Constructs messages to be sent from the system.
- **Functions**: Formats data into a predefined message structure, ensuring messages are correctly encoded and ready for transmission.