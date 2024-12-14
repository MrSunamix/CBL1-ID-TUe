# ESP32-S3 Multi-Sensor Display Controller

## Overview
This project implements a custom ESP32-S3-based board that integrates multiple sensors, display capabilities, and audio output in a battery-powered form factor. The system combines audio processing, color sensing, proximity detection, and a round LCD display to create a versatile embedded platform.

## Features
- **Display**: Adafruit GC9A01A Round LCD Display (240x240 pixels)
- **Sensors**:
  - VEML6040 Color Sensor
  - VCNL4040 Proximity/Distance Sensor
- **Audio**: PAM8302 Mono Audio Amplifier
- **Power Management**:
  - Battery charging module
  - 5V to 3.3V voltage converter
  - Battery monitoring
- **Processing**: ESP32-S3 Microcontroller

## Hardware Requirements
- Custom ESP32-S3 Board (PCB design to be provided)
- Adafruit GC9A01A Round LCD Display
- VEML6040 Color Sensor
- VCNL4040 Proximity/Distance Sensor
- PAM8302 Mono Audio Amplifier
- Battery charging module
- DC-DC converter (5V to 3.3V)
- Various passive components (detailed BOM to be provided)

## Dependencies
The project requires the following libraries:
```cpp
- SPI
- Adafruit_GFX
- Adafruit_GC9A01A
```

## Development Environment
This project is built using PlatformIO. To set up your development environment:

1. Install Visual Studio Code
2. Install PlatformIO IDE extension
3. Clone this repository:
   ```bash
   git clone https://github.com/MrSunamix/CBL1-ID-TUe.git
   ```
4. Open the project in VS Code with PlatformIO
5. Install required dependencies through platformio.ini

### PlatformIO Configuration
```ini
[env:esp32-s3-devkitc-1]
platform = espressif32
board = esp32-s3-devkitc-1-n16r8v
framework = arduino
board_build.arduino.memory_type = qio_opi
board_build.flash_mode = qio
board_build.psram_type = opi
board_upload.flash_size = 16MB
board_upload.maximum_size = 16777216
board_build.extra_flags = 
	-DBOARD_HAS_PSRAM
monitor_speed = 115200
monitor_filters = esp32_exception_decoder
upload_speed = 921600
lib_deps = 
	adafruit/Adafruit GFX Library @ ^1.11.5
	adafruit/Adafruit GC9A01A @ ^1.1.0
```

## Current Implementation
The current codebase includes:
- Display initialization and testing
- SPI communication setup
- Basic hardware abstraction layers
- Power management system
- Audio amplifier control

## Getting Started

### Hardware Setup
*Detailed pinout information will be provided once finalized*

Current pin assignments:
- **Display (SPI)**:
  - DC: GPIO35
  - CS: GPIO10
  - MOSI: GPIO11
  - SCLK: GPIO12
  - RST: GPIO36

### Building and Flashing
1. Open the project in VS Code with PlatformIO
2. Select the appropriate environment in platformio.ini
3. Build the project:
   ```bash
   pio run
   ```
4. Upload to your device:
   ```bash
   pio run --target upload
   ```
   
## Project Structure
```
├── .pio/                    # PlatformIO build directory
│   ├── build/               # Compiled files
│   └── libdeps/             # Project dependencies
├── .vscode/                 # VS Code configuration
│   ├── c_cpp_properties.json
│   ├── extensions.json
│   ├── launch.json
│   └── boards/
│       └── esp32-s3-devkitc-1-m16r8v.json
├── include/                 # Header files
│   └── README              
├── lib/                     # Project libraries
│   ├── bootUp/             # Boot sequence module
│   │   ├── bitmaps.h       # Custom graphics
│   │   ├── bootUp.cpp      # Boot implementation
│   │   └── bootUp.h        # Boot declarations
│   └── testLibrary/        # Testing module
│       ├── testLibrary.cpp # Test implementations
│       ├── testLibrary.h   # Test declarations
│       └── README
├── src/                    # Source files
│   └── main.cpp           # Main application code
├── test/                   # Test files
├── .gitignore             # Git ignore rules
└── platformio.ini         # PlatformIO configuration
```

## Development Status
## Development Status
- ✅ Basic display initialization
- ✅ Boot sequence
- 🚧 Color sensor implementation
- 🚧 Proximity sensor implementation
- 🚧 Audio amplifier control
- 🚧 Battery management
- 🚧 Power optimization
- 🚧 Full sensor integration
- 🚧 User interface implementation

## License
This project is licensed under the MIT License - see the LICENSE file for details.

## Future Plans
- Complete sensor integration
- Implement power management and battery monitoring
- Add documentation for custom PCB assembly (!)
- Optimize power consumption for battery operation

**Note**: This project is under active development. Pin assignments and features may change as development progresses.
