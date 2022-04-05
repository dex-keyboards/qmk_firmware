static const char PROGMEM ball_diffuse[] = {
0x00, 0x00, 0x80, 0xF8, 0x18, 0x08, 0x0C, 0x04, 0xE4, 0xE4, 0xCC, 0x08, 0x78, 0xE0, 0x00, 0x00,
0x00, 0x00, 0x01, 0x0F, 0x18, 0x10, 0x20, 0x20, 0x20, 0x20, 0x30, 0x18, 0x0E, 0x03, 0x00, 0x00, };

static const char PROGMEM ball_alpha[] = {
0x00, 0x00, 0x80, 0xF8, 0xF8, 0xF8, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xF8, 0xF8, 0xE0, 0x00, 0x00,
0x00, 0x00, 0x01, 0x0F, 0x1F, 0x1F, 0x3F, 0x3F, 0x3F, 0x3F, 0x3F, 0x1F, 0x0F, 0x03, 0x00, 0x00 };

static sprite_t ball_sprite = {
  .width = 16,
  .height = 16,
  .diffuse = ball_diffuse,
  .alpha = ball_alpha
};