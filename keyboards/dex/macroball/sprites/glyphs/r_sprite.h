const char r_diffuse[] PROGMEM = {
0xFF, 0xFF, 0x33, 0x71, 0xF1, 0xFB, 0xDF, 0x9E};

sprite_t r_sprite = {
  .size = { .x = 8, .y = 8 },
  .diffuse = r_diffuse
};

glyph_t r_glyph = {
  .value = 'r',
  .sprite = &r_sprite
};
