#include "motion_mode.h"

void encoder_update_motion(uint8_t index, bool clockwise){

    set_motion_cpi_step(get_motion_cpi_step() + (clockwise ? 1 : -1));
}

void oled_task_motion(uint32_t time, uint32_t delta){

    oled_write_sprite_string_positioned("motion", 6, (vec16_t){32, 8}, -1);

    const char* motion_str = get_u16_str(get_motion_cpi_step() * CPI_STEP, ' ');

    oled_write_sprite_string_positioned((char*)motion_str, 5, (vec16_t){32, 40}, 10);
}

mode_t motion_mode = (mode_t){ &encoder_update_motion, &oled_task_motion };
