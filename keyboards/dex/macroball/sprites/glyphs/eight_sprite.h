const char eight_diffuse[] PROGMEM = {
0x7E, 0xDF, 0x9F, 0xBD, 0xB9, 0xFB, 0xFE, 0x70};

sprite_t eight_sprite = {
  .size = { .x = 8, .y = 8 },
  .diffuse = eight_diffuse
};

glyph_t eight_glyph = {
  .value = '8',
  .sprite = &eight_sprite
};
