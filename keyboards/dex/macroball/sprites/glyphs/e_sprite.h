const char e_diffuse[] PROGMEM = {
0xFF, 0xFF, 0xDB, 0x99, 0x99, 0x99, 0x99, 0x81};

sprite_t e_sprite = {
  .size = { .x = 8, .y = 8 },
  .diffuse = e_diffuse
};

glyph_t e_glyph = {
  .value = 'e',
  .sprite = &e_sprite
};