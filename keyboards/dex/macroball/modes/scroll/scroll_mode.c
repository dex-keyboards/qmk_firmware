#include "scroll_mode.h"

void encoder_update_scroll(uint8_t index, bool clockwise){

    set_scroll_cpi_step(get_scroll_cpi_step() + (clockwise ? 1 : -1));
}

void oled_task_scroll(uint32_t time, uint32_t delta){

    oled_write_sprite_string_positioned("scroll", 6, (vec16_t){32, 8}, -1);

    const char* scroll_str = get_u16_str(get_scroll_cpi_step() * 1000, ' ');

    oled_write_sprite_string_positioned((char*)scroll_str, 4, (vec16_t){32, 40}, 10);
}

mode_t scroll_mode = (mode_t){ &encoder_update_scroll, &oled_task_scroll, NULL };
