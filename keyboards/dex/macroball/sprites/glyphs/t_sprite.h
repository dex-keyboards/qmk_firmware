const char t_diffuse[] PROGMEM = {
0x01, 0x01, 0xFF, 0xFF, 0xFF, 0x01, 0x01};

sprite_t t_sprite = {
  .size = { .x = 7, .y = 8 },
  .diffuse = t_diffuse
};

glyph_t t_glyph = {
  .value = 't',
  .sprite = &t_sprite
};
