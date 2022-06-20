const char i_diffuse[] PROGMEM = {
0x81, 0x81, 0xFF, 0xFF, 0xFF, 0x81, 0x81};

sprite_t i_sprite = {
  .size = { .x = 7, .y = 8 },
  .diffuse = i_diffuse
};

glyph_t i_glyph = {
  .value = 'i',
  .sprite = &i_sprite
};