const char five_diffuse[] PROGMEM = {
0x4F, 0xCF, 0xCF, 0x8D, 0x8D, 0xCD, 0xFD, 0x78};

sprite_t five_sprite = {
  .size = { .x = 8, .y = 8 },
  .diffuse = five_diffuse
};

glyph_t five_glyph = {
  .value = '5',
  .sprite = &five_sprite
};
