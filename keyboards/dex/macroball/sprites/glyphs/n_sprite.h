const char n_diffuse[] PROGMEM = {
0xFF, 0xFF, 0x0E, 0x0E, 0x3C, 0x38, 0xFF, 0xFF};

sprite_t n_sprite = {
  .size = { .x = 8, .y = 8 },
  .diffuse = n_diffuse
};

glyph_t n_glyph = {
  .value = 'n',
  .sprite = &n_sprite
};
