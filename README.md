# CH32V003j4m6 Rotary Encoder Library

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)
[![Platform: CH32V003](https://img.shields.io/badge/Platform-CH32V003-blue.svg)](http://www.wch-ic.com/products/CH32V003.html)

A simple and efficient rotary encoder library for the CH32V003j4m6 microcontroller. This library provides easy-to-use functions for reading rotary encoder position, direction, and button state.

## Features

- Simple initialization and usage
- Reliable position tracking
- Direction detection (clockwise/counterclockwise)
- Button press detection with debouncing
- Minimal CPU usage
- Compact code size

## Hardware Requirements

- CH32V003j4m6 microcontroller
- Rotary encoder with push button (like KY-040)
- Basic passive components (optional pull-up resistors)

## Pin Connections

```
CH32V003j4m6     Rotary Encoder
---------------------------------
PC2          <-> CLK (Encoder A)
PC4          <-> DT  (Encoder B)
PC1          <-> SW  (Switch)
3.3V         <-> VCC (+)
GND          <-> GND (Ground)
```

## Installation

### PlatformIO

1. Add the library to your `platformio.ini`:
```ini
lib_deps =
    https://github.com/shakir-abdo/CH32V003j4m6-rotary-encoder.git
```

### Manual Installation

1. Download the library
2. Copy the contents to your project's lib folder
3. Include the header file in your project

## Usage

### Basic Example

```c
#include "rotary_encoder.h"

int main() {
    SystemInit();
    encoder_init();

    while(1) {
        encoder_update();
        int32_t position = encoder_get_count();
        bool button = encoder_switch_pressed();

        // Use position and button state
        Delay_Ms(1);
    }
}
```

### Complete Example

```c
#include "rotary_encoder.h"
#include <stdio.h>

int main() {
    SystemInit();
    encoder_init();

    int32_t last_count = 0;
    bool last_switch_state = false;

    while(1) {
        encoder_update();

        int32_t current_count = encoder_get_count();
        bool switch_pressed = encoder_switch_pressed();

        // Print when count changes
        if (current_count != last_count) {
            printf("Count: %ld | Direction: %s\n\r",
                   current_count,
                   (current_count > last_count) ? "RIGHT" : "LEFT");
            last_count = current_count;
        }

        // Print when button state changes
        if (switch_pressed != last_switch_state) {
            printf("Button: %s\n\r",
                   switch_pressed ? "PRESSED" : "RELEASED");
            last_switch_state = switch_pressed;
        }

        Delay_Ms(1);
    }
}
```

## API Reference

### Functions

```c
void encoder_init(void);
```
Initializes the rotary encoder pins and hardware.

```c
void encoder_update(void);
```
Updates the encoder state. Should be called regularly in the main loop.

```c
int32_t encoder_get_count(void);
```
Returns the current encoder position.

```c
void encoder_set_count(int32_t value);
```
Sets the encoder position to a specific value.

```c
bool encoder_switch_pressed(void);
```
Returns true if the encoder button is pressed.

## Dependencies

- CH32V003fun framework

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## Author

- [**Shakir Abdo**](https://github.com/shakir-abdo)
