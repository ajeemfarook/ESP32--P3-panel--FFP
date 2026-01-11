#ifndef DRAWING_H
#define DRAWING_H

#include <ESP32-HUB75-MatrixPanel-I2S-DMA.h>
#include "comms.h"

void doAction(const Message& msg, MatrixPanel_I2S_DMA* dma);

void draw(const Message& msg, MatrixPanel_I2S_DMA* dma);
void fill(const Message& msg, MatrixPanel_I2S_DMA* dma);
void brightfield(const Message& msg, MatrixPanel_I2S_DMA* dma);
void darkfield(const Message& msg, MatrixPanel_I2S_DMA* dma);
void phaseTop(const Message& msg, MatrixPanel_I2S_DMA* dma);
void phaseBottom(const Message& msg, MatrixPanel_I2S_DMA* dma);
void phaseRight(const Message& msg, MatrixPanel_I2S_DMA* dma);
void phaseLeft(const Message& msg, MatrixPanel_I2S_DMA* dma);

#endif
