const char l_diffuse[] PROGMEM = {
0x00, 0xF8, 0xFF, 0xFF, 0xFF, 0x0F, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xF0, 0xF0, 0xF0,
0xF0, 0xF0};

const char l_alpha[] PROGMEM = {
0x00, 0xF8, 0xFF, 0xFF, 0xFF, 0x0F, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xF0, 0xF0, 0xF0,
0xF0, 0xF0};

sprite_t l_sprite = {
  .size = { .x = 9, .y = 16 },
  .diffuse = l_diffuse,
  .alpha = l_alpha
};

glyph_t l_glyph = {
  .value = 'l',
  .sprite = &l_sprite
};
