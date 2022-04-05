#pragma once

#include "progmem.h"

const char palm_diffuse[] PROGMEM = {
0x00, 0x10, 0x1C, 0x9C, 0xDE, 0xDE, 0xDE, 0xFC, 0xFC, 0xF8, 0xF0, 0xE0, 0xF0, 0xF8, 0xFC, 0xFC,
0xDE, 0xDE, 0x9E, 0x0E, 0x0E, 0x0C, 0x00, 0x00, 0x00, 0x7C, 0xFF, 0x3F, 0x0F, 0x07, 0x07, 0x03,
0x7B, 0xF1, 0xC7, 0x0F, 0x3F, 0xFF, 0xFF, 0xE7, 0x07, 0x0F, 0x0F, 0x1F, 0x7E, 0x70, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF0, 0xF7, 0xD6, 0x92, 0xBA, 0xBC, 0x00, 0x00, 0x07, 0x1F,
0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };

const char palm_alpha[] PROGMEM = {
0x00, 0x10, 0x1C, 0x9C, 0xDE, 0xDE, 0xDE, 0xFC, 0xFC, 0xF8, 0xF0, 0xE0, 0xF0, 0xF8, 0xFC, 0xFC,
0xDE, 0xDE, 0x9E, 0x0E, 0x0E, 0x0C, 0x00, 0x00, 0x00, 0x7C, 0xFF, 0x3F, 0x0F, 0x07, 0x07, 0x03,
0x7B, 0xF1, 0xC7, 0x0F, 0x3F, 0xFF, 0xFF, 0xE7, 0x07, 0x0F, 0x0F, 0x1F, 0x7E, 0x70, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF0, 0xF7, 0xD6, 0x92, 0xBA, 0xBC, 0x00, 0x00, 0x07, 0x1F,
0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

sprite_t palm_sprite = {
  .width = 24,
  .height = 24,
  .diffuse = palm_diffuse,
  .alpha = palm_alpha
};