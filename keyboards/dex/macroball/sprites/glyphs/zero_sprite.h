const char zero_diffuse[] PROGMEM = {
0x3C, 0x7E, 0xE3, 0xC1, 0x83, 0xC7, 0x7E, 0x3C};

sprite_t zero_sprite = {
  .size = { .x = 8, .y = 8 },
  .diffuse = zero_diffuse,
};

glyph_t zero_glyph = {
  .value = '0',
  .sprite = &zero_sprite
};
