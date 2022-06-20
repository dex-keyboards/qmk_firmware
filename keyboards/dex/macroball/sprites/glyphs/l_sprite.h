const char l_diffuse[] PROGMEM = {
0xFF, 0xFF, 0xFF, 0x80, 0x80, 0x80, 0x80};

sprite_t l_sprite = {
  .size = { .x = 7, .y = 8 },
  .diffuse = l_diffuse
};

glyph_t l_glyph = {
  .value = 'l',
  .sprite = &l_sprite
};