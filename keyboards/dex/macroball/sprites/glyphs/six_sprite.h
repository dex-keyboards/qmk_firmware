const char six_diffuse[] PROGMEM = {
0x7C, 0xFE, 0xDF, 0x9B, 0x99, 0xD9, 0xF9, 0x70};

sprite_t six_sprite = {
  .size = { .x = 8, .y = 8 },
  .diffuse = six_diffuse
};

glyph_t six_glyph = {
  .value = '6',
  .sprite = &six_sprite
};
