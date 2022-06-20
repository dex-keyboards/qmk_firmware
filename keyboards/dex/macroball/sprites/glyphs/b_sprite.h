const char b_diffuse[] PROGMEM = {
0xFF, 0xFF, 0xDB, 0x99, 0x99, 0xDB, 0xFF, 0x7E};

sprite_t b_sprite = {
  .size = { .x = 8, .y = 8 },
  .diffuse = b_diffuse
};

glyph_t b_glyph = {
  .value = 'b',
  .sprite = &b_sprite
};