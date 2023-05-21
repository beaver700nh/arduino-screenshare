#include <Arduino.h>
#include <HardwareSerial.h>

#include <MCUFRIEND_kbv/utility/mcufriend_shield.h>

#include "eztft/src/tft.hpp"

#include "xram.hpp"

extern HardwareSerial Serial;

#define WIDTH 480L
#define HEIGHT 320L
#define CHUNK 32L

TftCtrl tft;

void fillChunk(uint8_t *buffer, uint32_t size);
void pushColors_(uint16_t *buffer, uint32_t size);

void setup() {
  Serial.begin(921600);

  xram::init(0x00, 0x01);

  tft.init(0x9486, 1);
}

void loop() {
  volatile uint8_t *buffer = xram::access(0x8000);

  for (uint8_t section = 0; section < 10; ++section) {
    uint16_t y = section * CHUNK;

    fillChunk((uint8_t *) buffer, 2 * WIDTH * CHUNK);
    tft.setAddrWindow(0, y, WIDTH - 1, y + CHUNK - 1);
    pushColors_((uint16_t *) buffer, WIDTH * CHUNK);
  }
}

void fillChunk(uint8_t *buffer, uint32_t size) {
  uint8_t *target = buffer + size;

  while (buffer < target) {
    while (Serial.available() < 32) {
      // wait
    }

    Serial.readBytes(buffer, 32);
    buffer += 32;
  }
}

void pushColors_(uint16_t *buffer, uint32_t size) {
  CS_ACTIVE;
  WriteCmd(0x2C);

  while (size --> 0) {
    uint16_t color = *buffer++;
    write16(color);
  }

  CS_IDLE;
}
