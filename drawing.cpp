#include "drawing.h"
#include "panel_config.h" // Provides PANEL_WIDTH & PANEL_HEIGHT

// ================= COLOR UTILITY =================
uint16_t getColor(char c, int brightnessPercent) {
    // Clamp brightness 0–100
    int b = constrain(brightnessPercent, 0, 100);
    uint8_t value = map(b, 0, 100, 0, 255);  // Scale to 0–255

    switch (c) {
        case 'R': return ((value & 0xF8) << 8);       // Red
        case 'G': return ((value & 0xFC) << 3);       // Green
        case 'B': return (value >> 3);                // Blue
        default:  return ((value & 0xFC) << 3);      // Default Green
    }
}

// ================= UTILITY FUNCTIONS =================
// Clip radius so it doesn't exceed panel boundaries
inline int clipRadius(int r, int x, int y) {
    int maxR = min(x, y);
    return (r > maxR) ? maxR : r;
}

// ================= DISPATCH =================
void doAction(const Message& msg, MatrixPanel_I2S_DMA* dma) {
    switch (msg.cmd) {
        case Command::draw:        draw(msg, dma); break;
        case Command::fill:        fill(msg, dma); break;
        case Command::brightfield: brightfield(msg, dma); break;
        case Command::darkfield:   darkfield(msg, dma); break;
        case Command::phaseTop:    phaseTop(msg, dma); break;
        case Command::phaseBottom: phaseBottom(msg, dma); break;
        case Command::phaseRight:  phaseRight(msg, dma); break;
        case Command::phaseLeft:   phaseLeft(msg, dma); break;
        default: break;
    }
}

// ================= DRAWING FUNCTIONS =================
void draw(const Message& msg, MatrixPanel_I2S_DMA* dma) {
    dma->clearScreen();
    uint16_t color = getColor(msg.color, msg.state);
    dma->drawPixel(msg.x, msg.y, color);
}

void fill(const Message& msg, MatrixPanel_I2S_DMA* dma) {
    dma->clearScreen();
    uint16_t color = getColor(msg.color, msg.state);
    dma->fillScreen(color);
}

void brightfield(const Message& msg, MatrixPanel_I2S_DMA* dma) {
    dma->clearScreen();
    int x = PANEL_WIDTH / 2;
    int y = PANEL_HEIGHT / 2;
    int r = clipRadius(msg.r, x, y);
    uint16_t color = getColor(msg.color, msg.state);
    dma->fillCircle(x, y, r, color);
}

void darkfield(const Message& msg, MatrixPanel_I2S_DMA* dma) {
    dma->clearScreen();
    int x = PANEL_WIDTH / 2;
    int y = PANEL_HEIGHT / 2;
    int r = clipRadius(msg.r, x, y);
    uint16_t color = getColor(msg.color, msg.state);
    dma->fillScreen(color);       // bright background (user color)
    dma->fillCircle(x, y, r, 0);  // dark circle
}

void phaseTop(const Message& msg, MatrixPanel_I2S_DMA* dma) {
    dma->clearScreen();
    int x = PANEL_WIDTH / 2;
    int y = PANEL_HEIGHT / 2;
    int r = clipRadius(msg.r, x, y);
    uint16_t color = getColor(msg.color, msg.state);
    dma->fillCircle(x, y, r, color);
    dma->fillRect(x - r, y, r * 2 + 1, r + 1, 0);
}

void phaseBottom(const Message& msg, MatrixPanel_I2S_DMA* dma) {
    dma->clearScreen();
    int x = PANEL_WIDTH / 2;
    int y = PANEL_HEIGHT / 2;
    int r = clipRadius(msg.r, x, y);
    uint16_t color = getColor(msg.color, msg.state);
    dma->fillCircle(x, y, r, color);
    dma->fillRect(x - r, y - r, r * 2 + 1, r + 1, 0);
}

void phaseRight(const Message& msg, MatrixPanel_I2S_DMA* dma) {
    dma->clearScreen();
    int x = PANEL_WIDTH / 2;
    int y = PANEL_HEIGHT / 2;
    int r = clipRadius(msg.r, x, y);
    uint16_t color = getColor(msg.color, msg.state);
    dma->fillCircle(x, y, r, color);
    dma->fillRect(x - r, y - r, r + 1, r * 2 + 1, 0);
}

void phaseLeft(const Message& msg, MatrixPanel_I2S_DMA* dma) {
    dma->clearScreen();
    int x = PANEL_WIDTH / 2;
    int y = PANEL_HEIGHT / 2;
    int r = clipRadius(msg.r, x, y);
    uint16_t color = getColor(msg.color, msg.state);
    dma->fillCircle(x, y, r, color);
    dma->fillRect(x, y - r, r + 1, r * 2 + 1, 0);
}

// ================= PATTERN DRAW =================
void drawPattern(const int pattern[8][8], MatrixPanel_I2S_DMA* dma, char colorChar, int brightness) {
    dma->clearScreen();

    int P_width  = 8;
    int P_height = 8;

    // Compute top-left corner to center the pattern
    int startX = (PANEL_WIDTH  - P_width)  / 2;
    int startY = (PANEL_HEIGHT - P_height) / 2;

    // Get color with brightness
    uint16_t color = getColor(colorChar, brightness);

    // Draw each pixel
    for (int i = 0; i < P_height; i++) {
        for (int j = 0; j < P_width; j++) {
            if (pattern[i][j] != 0) {
                dma->drawPixel(startX + j, startY + i, color);
            }
        }
    }
}