const char c_diffuse[] PROGMEM = {
0x3C, 0x7E, 0xE7, 0xC3, 0x81, 0xC3, 0xC3, 0x42};

sprite_t c_sprite = {
  .size = { .x = 8, .y = 8 },
  .diffuse = c_diffuse
};

glyph_t c_glyph = {
  .value = 'c',
  .sprite = &c_sprite
};
