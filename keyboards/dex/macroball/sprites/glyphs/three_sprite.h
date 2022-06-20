const char three_diffuse[] PROGMEM = {
0x40, 0xC1, 0xD9, 0x9D, 0x9F, 0xDF, 0xFB, 0x71};

sprite_t three_sprite = {
  .size = { .x = 8, .y = 8 },
  .diffuse = three_diffuse
};

glyph_t three_glyph = {
  .value = '3',
  .sprite = &three_sprite
};
