const char o_diffuse[] PROGMEM = {
0x7E, 0xFF, 0xC3, 0x81, 0x81, 0xC3, 0xFF, 0x7E};

sprite_t o_sprite = {
  .size = { .x = 8, .y = 8 },
  .diffuse = o_diffuse
};

glyph_t o_glyph = {
  .value = 'o',
  .sprite = &o_sprite
};
