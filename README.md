# Fourier Ptychography LED Illuminator

ESP32 firmware for controlling **64×64 HUB75 LED matrices** in computational microscopy applications. This project generates precise illumination patterns—**brightfield, darkfield, and phase contrast**—for **Fourier Ptychography** via a simple serial command interface with **virtual grid scaling**.

---

## ✨ Features

* **Virtual Grid Scaling**: 8×8, 16×16, 32×32, 64×64 coordinate mapping
* **Pattern Library**:

  * Brightfield
  * Darkfield
  * Phase contrast (top / bottom / left / right)
* **Color Control**: RGB with 0–100% brightness per LED
* **Simple Serial Protocol**: Human‑readable text commands with error feedback
* **Real‑time Control**: <10 ms response for pattern updates
* **Designed for Computational Microscopy & Fourier Ptychography**

---

## 🧰 Hardware Requirements

* ESP32 development board (**ESP32‑WROOM‑32 recommended**)
* 64×64 HUB75 LED matrix (P3 or P4 pitch)
* 5V / 10A power supply (for LED matrix)
* USB cable (ESP32 programming & power)
* Jumper wires (≈20+)

---

## 🔌 HUB75E Critical Connections (64×64 Panels)

> ⚠️ **IMPORTANT:** 64×64 HUB75 panels **require the E address line**. Without it, only half the panel will display.

### HUB75E → ESP32 GPIO Mapping

```
┌─────────┬─────────┐
│ R1 (25) │ G1 (26) │
├─────────┼─────────┤
│ B1 (27) │  GND    │
├─────────┼─────────┤
│ R2 (14) │ G2 (12) │
├─────────┼─────────┤
│ B2 (13) │   E (32)│  ← MUST CONNECT for 64×64
├─────────┼─────────┤
│  A (23) │  B (19) │
├─────────┼─────────┤
│  C (5)  │  D (17) │
├─────────┼─────────┤
│ CLK (16)│ LAT (4) │
├─────────┼─────────┤
│ OE (15) │  GND    │
└─────────┴─────────┘
```

* **COMMON GND:** Connect ESP32 GND to LED matrix GND

---

## ⚡ Power Setup

* **LED Matrix:**

  * Dedicated **5V / 10A** power supply
* **ESP32:**

  * Powered via USB (3.3V logic)
* **Grounding:**

  * ESP32 GND **must** be connected to matrix GND for proper signal reference

> 🔒 Do **NOT** power the LED matrix from the ESP32.

---

## 💻 Software Installation

### 1. Install ESP32 Board Support (Arduino IDE)

**File → Preferences → Additional Boards Manager URLs**

```
https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json
```

**Tools → Board → Boards Manager** → Search **esp32** → Install

---

### 2. Install Required Libraries

**Tools → Manage Libraries**

* **ESP32-HUB75-MatrixPanel-I2S-DMA** (by Marc Merlin)
* **Adafruit GFX Library** (auto-installed dependency)

---

## 📁 Project Structure

Place all files inside a folder named **`led_blink`**:

```
led_blink/
├── led_blink.ino        # Main sketch
├── comms.h
├── comms.cpp
├── drawing.h
├── drawing.cpp
├── panel_config.h
```

---

## ⚙️ Arduino Board Configuration

* **Board:** ESP32 Dev Module
* **Upload Speed:** 921600
* **Flash Mode:** QIO
* **Partition Scheme:** Default 4MB with spiffs
* **Port:** Select your ESP32 COM port

---

## ▶️ Quick Start

1. Connect hardware as per wiring table
2. Upload firmware to ESP32
3. Open **Serial Monitor**

   * Baud rate: **115200**
   * Line ending: **Newline**

---

## 🧪 Basic Serial Commands

```
grid 8                    # Set 8×8 virtual grid (0–7 coordinates)
draw 4 4 100 R           # Red LED at grid center (maps to 32,32)
brightfield 4 4 2 100 G  # Green brightfield circle, radius 2
clear                    # Turn off all LEDs
help                     # Show command reference
```

---

## 🔧 Complete Wiring Example (Code Reference)

```cpp
// ESP32 GPIO → HUB75E Pin Mapping
const int R1_PIN  = 25;
const int G1_PIN  = 26;
const int B1_PIN  = 27;
const int R2_PIN  = 14;
const int G2_PIN  = 12;
const int B2_PIN  = 13;

const int A_PIN   = 23;
const int B_PIN   = 19;
const int C_PIN   = 5;
const int D_PIN   = 17;
const int E_PIN   = 32;   // REQUIRED for 64×64 panels

const int CLK_PIN = 16;
const int LAT_PIN = 4;
const int OE_PIN  = 15;
```

---

## 🧠 Applications

* Fourier Ptychography calibration
* Computational microscopy illumination
* Optical system testing
* Adaptive illumination experiments
* Educational demonstrations

---

## 🛠 Troubleshooting

| Issue                 | Possible Cause              | Solution                  |
| --------------------- | --------------------------- | ------------------------- |
| Half panel displays   | E pin not connected         | Connect GPIO 32 to HUB75E |
| No display            | Insufficient power          | Use dedicated 5V 10A PSU  |
| Wrong colors          | RGB pin mismatch            | Verify R/G/B wiring       |
| Serial not responding | Baud / line ending mismatch | 115200 baud, Newline      |

---

## ⚠️ Important Notes

* **64×64 HUB75 panels REQUIRE the E address line**
* Without E connected, only **32 rows** will refresh
* Always share **common ground** between ESP32 and matrix

---

## 📜 License

MIT License (or specify your preferred license)

---

## 🙌 Acknowledgements

* Marc Merlin – ESP32 HUB75 I2S DMA driver
* Fourier Ptychography research community
* Open-source microscopy developers

---

Happy hacking & clear illumination 🔬✨
