const char four_diffuse[] PROGMEM = {
0x38, 0x3C, 0x3E, 0x37, 0xFF, 0xFF, 0xFF, 0x30};

sprite_t four_sprite = {
  .size = { .x = 8, .y = 8 },
  .diffuse = four_diffuse
};

glyph_t four_glyph = {
  .value = '4',
  .sprite = &four_sprite
};