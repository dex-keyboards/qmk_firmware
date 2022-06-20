const char s_diffuse[] PROGMEM = {
0x4E, 0xDF, 0xDB, 0x99, 0x99, 0xDB, 0xFB, 0x72};

sprite_t s_sprite = {
  .size = { .x = 8, .y = 8 },
  .diffuse = s_diffuse
};

glyph_t s_glyph = {
  .value = 's',
  .sprite = &s_sprite
};
