#include "scroll_mode.h"

void encoder_update_scroll(uint8_t index, bool clockwise){

    set_scroll_cpi_step(kb_config.scroll_cpi_step + (clockwise ? 1 : -1));
}

void oled_task_scroll(uint32_t time, uint32_t delta){


    oled_write_sprite_string_positioned("scroll", 6, (vec16_t){6, 8}, -1);

    char sscroll[4];
    sprintf(sscroll, "%4d", kb_config.scroll_cpi_step * 100);

    oled_write_sprite_string_positioned(sscroll, 4, (vec16_t){32, 40}, 10);
}

mode_t scroll_mode = (mode_t){ &encoder_update_scroll, &oled_task_scroll };
