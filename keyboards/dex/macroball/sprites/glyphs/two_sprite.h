const char two_diffuse[] PROGMEM = {
0xC2, 0xF3, 0xFB, 0xF9, 0xBD, 0xBF, 0x9F, 0x8E};

sprite_t two_sprite = {
  .size = { .x = 8, .y = 8 },
  .diffuse = two_diffuse
};

glyph_t two_glyph = {
  .value = '2',
  .sprite = &two_sprite
};
