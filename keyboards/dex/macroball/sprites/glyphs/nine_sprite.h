const char nine_diffuse[] PROGMEM = {
0x0E, 0x9F, 0x9B, 0x99, 0xD9, 0xFB, 0x7F, 0x3E};

sprite_t nine_sprite = {
  .size = { .x = 8, .y = 8 },
  .diffuse = nine_diffuse
};

glyph_t nine_glyph = {
  .value = '9',
  .sprite = &nine_sprite
};
