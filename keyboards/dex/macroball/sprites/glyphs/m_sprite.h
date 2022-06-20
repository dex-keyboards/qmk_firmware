const char m_diffuse[] PROGMEM = {
0xFF, 0xFF, 0x0E, 0x3E, 0x3E, 0x0E, 0xFF, 0xFF};

sprite_t m_sprite = {
  .size = { .x = 8, .y = 8 },
  .diffuse = m_diffuse
};

glyph_t m_glyph = {
  .value = 'm',
  .sprite = &m_sprite
};