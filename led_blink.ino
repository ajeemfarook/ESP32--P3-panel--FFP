#include <ESP32-HUB75-MatrixPanel-I2S-DMA.h>
#include "comms.h"
#include "drawing.h"

// ================= PANEL CONFIG =================
#define PANEL_WIDTH   64
#define PANEL_HEIGHT  64
#define PANELS_NUMBER 1

#define PIN_E 32   // VERY IMPORTANT for 64x64

MatrixPanel_I2S_DMA *dma_display = nullptr;

// ================= SERIAL COMMUNICATION =================
String serialInput = "";
bool messageReceived = false;

void setup() {
  Serial.begin(115200);
  Serial.println("64x64 HUB75 LED Matrix Controller");
  Serial.println("Commands: draw, fill, brightfield, darkfield, phaseTop, phaseBottom, phaseRight, phaseLeft, help");

  // ================= MATRIX CONFIG =================
  HUB75_I2S_CFG mxconfig(
    PANEL_WIDTH,
    PANEL_HEIGHT,
    PANELS_NUMBER
  );

  // ===== CRITICAL SETTINGS =====
  mxconfig.gpio.e  = PIN_E;                 // REQUIRED for 64x64
  mxconfig.driver = HUB75_I2S_CFG::FM6126A;
  mxconfig.clkphase = false;

  // Optional but recommended
  mxconfig.i2sspeed = HUB75_I2S_CFG::HZ_10M;

  dma_display = new MatrixPanel_I2S_DMA(mxconfig);

  if (!dma_display->begin()) {
    Serial.println("Matrix init failed!");
    while (1);
  }

  dma_display->setBrightness8(255);
  dma_display->clearScreen();

  Serial.println("Matrix ready - waiting for commands...");
  Serial.println("Example: draw 32 32 100 R\\n");
  Serial.println("         brightfield 32 32 20 100 G\\n");
  Serial.println("         phaseTop 32 32 25 100 B\\n");
}

void loop() {
  // Read serial input
  if (readStringUntil(serialInput, LINE_TERMINATOR, CHAR_LIMIT)) {
    Message msg;
    messageInit(msg);
    
    // Parse the message
    parseMessage(serialInput, msg);
    
    if (msg.is_valid) {
      // Execute the command
      if (msg.cmd == Command::help) {
        printHelp();
      } else {
        doAction(msg, dma_display);
        Serial.print("Executed: ");
        printCommand(msg);
      }
    } else {
      Serial.print("Error: ");
      Serial.println(msg.error_msg);
    }
    
    // Clear input for next message
    serialInput = "";
  }
}

// ================= HELPER FUNCTIONS =================
void printHelp() {
  Serial.println("\n=== LED Matrix Controller Commands ===");
  Serial.println("draw x y brightness [color]");
  Serial.println("  Draws a single pixel at (x,y)");
  Serial.println("  Example: draw 32 32 100 R");
  
  Serial.println("\nfill brightness [color]");
  Serial.println("  Fills entire screen with color");
  Serial.println("  Example: fill 50 G");
  
  Serial.println("\nbrightfield x y radius brightness [color]");
  Serial.println("  Draws a filled circle (brightfield)");
  Serial.println("  Example: brightfield 32 32 20 100 B");
  
  Serial.println("\ndarkfield x y radius brightness [color]");
  Serial.println("  Draws a darkfield pattern (circle cutout)");
  Serial.println("  Example: darkfield 32 32 25 100 G");
  
  Serial.println("\nphaseTop x y radius brightness [color]");
  Serial.println("  Draws top-phase contrast pattern");
  Serial.println("  Example: phaseTop 32 32 30 100 R");
  
  Serial.println("\nphaseBottom x y radius brightness [color]");
  Serial.println("  Draws bottom-phase contrast pattern");
  
  Serial.println("\nphaseRight x y radius brightness [color]");
  Serial.println("  Draws right-phase contrast pattern");
  
  Serial.println("\nphaseLeft x y radius brightness [color]");
  Serial.println("  Draws left-phase contrast pattern");
  
  Serial.println("\nhelp");
  Serial.println("  Shows this help message");
  
  Serial.println("\n=== Notes ===");
  Serial.println("x: 0-63, y: 0-63, radius: 0-31, brightness: 0-100%");
  Serial.println("color: R (Red), G (Green), B (Blue) - optional, defaults to Green");
  Serial.println("All commands must end with newline (\\n)");
}

void printCommand(const Message& msg) {
  switch (msg.cmd) {
    case Command::draw:
      Serial.print("draw ");
      Serial.print(msg.x);
      Serial.print(" ");
      Serial.print(msg.y);
      Serial.print(" ");
      Serial.print(msg.state);
      Serial.print(" ");
      Serial.println(msg.color);
      break;
      
    case Command::fill:
      Serial.print("fill ");
      Serial.print(msg.state);
      Serial.print(" ");
      Serial.println(msg.color);
      break;
      
    case Command::brightfield:
      Serial.print("brightfield ");
      Serial.print(msg.x);
      Serial.print(" ");
      Serial.print(msg.y);
      Serial.print(" ");
      Serial.print(msg.r);
      Serial.print(" ");
      Serial.print(msg.state);
      Serial.print(" ");
      Serial.println(msg.color);
      break;
      
    case Command::darkfield:
      Serial.print("darkfield ");
      Serial.print(msg.x);
      Serial.print(" ");
      Serial.print(msg.y);
      Serial.print(" ");
      Serial.print(msg.r);
      Serial.print(" ");
      Serial.print(msg.state);
      Serial.print(" ");
      Serial.println(msg.color);
      break;
      
    case Command::phaseTop:
      Serial.print("phaseTop ");
      Serial.print(msg.x);
      Serial.print(" ");
      Serial.print(msg.y);
      Serial.print(" ");
      Serial.print(msg.r);
      Serial.print(" ");
      Serial.print(msg.state);
      Serial.print(" ");
      Serial.println(msg.color);
      break;
      
    case Command::phaseBottom:
      Serial.print("phaseBottom ");
      Serial.print(msg.x);
      Serial.print(" ");
      Serial.print(msg.y);
      Serial.print(" ");
      Serial.print(msg.r);
      Serial.print(" ");
      Serial.print(msg.state);
      Serial.print(" ");
      Serial.println(msg.color);
      break;
      
    case Command::phaseRight:
      Serial.print("phaseRight ");
      Serial.print(msg.x);
      Serial.print(" ");
      Serial.print(msg.y);
      Serial.print(" ");
      Serial.print(msg.r);
      Serial.print(" ");
      Serial.print(msg.state);
      Serial.print(" ");
      Serial.println(msg.color);
      break;
      
    case Command::phaseLeft:
      Serial.print("phaseLeft ");
      Serial.print(msg.x);
      Serial.print(" ");
      Serial.print(msg.y);
      Serial.print(" ");
      Serial.print(msg.r);
      Serial.print(" ");
      Serial.print(msg.state);
      Serial.print(" ");
      Serial.println(msg.color);
      break;
      
    default:
      break;
  }
}