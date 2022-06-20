const char a_diffuse[] PROGMEM = {
0xFC, 0xFE, 0x37, 0x33, 0x33, 0x37, 0xFE, 0xFC};

sprite_t a_sprite = {
  .size = { .x = 8, .y = 8 },
  .diffuse = a_diffuse
};

glyph_t a_glyph = {
  .value = 'a',
  .sprite = &a_sprite
};