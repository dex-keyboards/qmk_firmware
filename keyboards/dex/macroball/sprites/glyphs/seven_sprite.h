const char seven_diffuse[] PROGMEM = {
0x03, 0x03, 0xF3, 0xF1, 0xFD, 0x1F, 0x0F, 0x03};

sprite_t seven_sprite = {
  .size = { .x = 8, .y = 8 },
  .diffuse = seven_diffuse
};

glyph_t seven_glyph = {
  .value = '7',
  .sprite = &seven_sprite
};
