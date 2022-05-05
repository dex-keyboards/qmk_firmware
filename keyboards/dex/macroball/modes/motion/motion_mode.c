#include "motion_mode.h"
#include <stdio.h>

void encoder_update_motion(uint8_t index, bool clockwise){

    set_motion_cpi_step(get_motion_cpi_step() + (clockwise ? 1 : -1));
}

void oled_task_motion(uint32_t time, uint32_t delta){

    oled_write_sprite_string_positioned("motion", 6, (vec16_t){6, 8}, -1);

    char scpi[5];
    sprintf(scpi, "%5d", get_motion_cpi_step() * CPI_STEP);

    oled_write_sprite_string_positioned(scpi, 5, (vec16_t){32, 40}, 10);
}

mode_t motion_mode = (mode_t){ &encoder_update_motion, &oled_task_motion };
