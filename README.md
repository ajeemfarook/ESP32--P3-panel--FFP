Fourier Ptychography LED Illuminator
ESP32 firmware for controlling 64x64 HUB75 LED matrices in computational microscopy applications. Generates precise illumination patterns (brightfield, darkfield, phase contrast) for Fourier Ptychography via serial commands with virtual grid scaling.

Quick Start
Hardware Requirements
ESP32 development board (ESP32-WROOM-32 recommended)

64x64 HUB75 LED matrix (P3 or P4 pitch)

5V/10A power supply for LED matrix

USB cable for ESP32 programming/power

Connecting wires (20+ jumper wires)

Critical Connections for HUB75E
text
HUB75E Pinout → ESP32 GPIO
┌─────────┬─────────┐
│ R1 (25) │ G1 (26) │
├─────────┼─────────┤
│ B1 (27) │  GND    │
├─────────┼─────────┤
│ R2 (14) │ G2 (12) │
├─────────┼─────────┤
│ B2 (13) │   E (32)│  ← MUST CONNECT for 64x64!
├─────────┼─────────┤
│  A (23) │  B (19) │
├─────────┼─────────┤
│  C (5)  │  D (17) │
├─────────┼─────────┤
│ CLK (16)│ LAT (4) │
├─────────┼─────────┤
│ OE (15) │  GND    │
└─────────┴─────────┘

COMMON GND: Connect ESP32 GND to matrix GND
Power Setup
LED Matrix: Dedicated 5V 10A power supply to matrix

ESP32: USB power (3.3V) - keep SEPARATE from matrix power

Ground: Connect ESP32 GND to matrix GND for signal reference

Software Installation
Install ESP32 board support in Arduino IDE:

File → Preferences → Additional Boards Manager URLs:

text
https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json
Tools → Board → Boards Manager → Search "esp32" → Install

Install Required Libraries (Tools → Manage Libraries):

ESP32-HUB75-MatrixPanel-I2S-DMA by Marc Merlin

Adafruit GFX Library (usually auto-installs)

Project Structure: Place all 6 files in a folder named led_blink:

led_blink.ino (main sketch)

comms.h, comms.cpp

drawing.h, drawing.cpp

panel_config.h

Board Configuration:

Board: ESP32 Dev Module

Upload Speed: 921600

Flash Mode: QIO

Partition Scheme: Default 4MB with spiffs

Port: Select your ESP32 COM port

Basic Usage (Serial Monitor, 115200 baud)
text
grid 8                    # Set 8x8 virtual grid (0-7 coordinates)
draw 4 4 100 R           # Red pixel at center (maps to 32,32 on 64x64)
brightfield 4 4 2 100 G  # Green circle, radius 2 in 8x8 grid
clear                    # Turn off all LEDs
help                     # Show command reference
Complete Wiring Example
cpp
// ESP32 GPIO → HUB75E Pin Mapping
// Using default library pins for 64x64
const int R1_PIN = 25;
const int G1_PIN = 26;
const int B1_PIN = 27;
const int R2_PIN = 14;
const int G2_PIN = 12;
const int B2_PIN = 13;
const int A_PIN = 23;
const int B_PIN = 19;
const int C_PIN = 5;
const int D_PIN = 17;
const int E_PIN = 32;  // CRITICAL for 64x64!
const int CLK_PIN = 16;
const int LAT_PIN = 4;
const int OE_PIN = 15;
Features
Virtual Grid Scaling: 8x8, 16x16, 32x32, 64x64 coordinate mapping

Pattern Library: Brightfield, darkfield, phase contrast (top/bottom/left/right)

Color Control: RGB with 0-100% brightness per LED

Simple Serial Protocol: Text commands with error feedback

Real-time Control: <10ms response for pattern changes

Troubleshooting
Half panel displays: Check E pin (GPIO 32) connection

No display: Verify 5V 10A power to matrix

Wrong colors: Check RGB pin assignments

Serial not responding: Confirm 115200 baud, Newline ending

Applications
Fourier Ptychography calibration

Computational microscopy illumination

Optical system testing

Educational demonstrations

Note: 64x64 panels REQUIRE the E address line (GPIO 32). Without it, only 32 rows will display.
