const char one_diffuse[] PROGMEM = {
0x80, 0x82, 0xFF, 0xFF, 0xFF, 0x80, 0x80};

sprite_t one_sprite = {
  .size = { .x = 7, .y = 8 },
  .diffuse = one_diffuse
};

glyph_t one_glyph = {
  .value = '1',
  .sprite = &one_sprite
};
