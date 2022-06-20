const char v_diffuse[] PROGMEM = {
0x1F, 0x3F, 0x78, 0xF0, 0xF0, 0x78, 0x3F, 0x1F};

sprite_t v_sprite = {
  .size = { .x = 8, .y = 8 },
  .diffuse = v_diffuse
};

glyph_t v_glyph = {
  .value = 'v',
  .sprite = &v_sprite
};
