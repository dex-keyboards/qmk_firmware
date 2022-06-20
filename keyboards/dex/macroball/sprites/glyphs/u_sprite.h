const char u_diffuse[] PROGMEM = {
0x7F, 0xFF, 0xC0, 0x80, 0x80, 0xC0, 0xFF, 0x7F};

sprite_t u_sprite = {
  .size = { .x = 8, .y = 8 },
  .diffuse = u_diffuse
};

glyph_t u_glyph = {
  .value = 'u',
  .sprite = &u_sprite
};
