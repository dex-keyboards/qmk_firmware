const char s_diffuse[] PROGMEM = {
0x00, 0xF0, 0xFC, 0xFE, 0xFF, 0x9F, 0x9F, 0xBF, 0xBF, 0x3F, 0x3E, 0x0C, 0xF8, 0xF9, 0xFB, 0xFB,
0xF3, 0xF3, 0xFF, 0xFF, 0x7F, 0x1F, 0x00, 0x00};

const char s_alpha[] PROGMEM = {
0x00, 0xF0, 0xFC, 0xFE, 0xFF, 0x9F, 0x9F, 0xBF, 0xBF, 0x3F, 0x3E, 0x0C, 0xF8, 0xF9, 0xFB, 0xFB,
0xF3, 0xF3, 0xFF, 0xFF, 0x7F, 0x1F, 0x00, 0x00};

sprite_t s_sprite = {
  .size = { .x = 12, .y = 16 },
  .diffuse = s_diffuse,
  .alpha = s_alpha
};

glyph_t s_glyph = {
  .value = 's',
  .sprite = &s_sprite
};
