#include "volume_mode.h"

void encoder_update_volume(uint8_t index, bool clockwise){

    if (clockwise)
        tap_code(KC_VOLD);
    else
        tap_code(KC_VOLU);
}

void oled_task_volume(uint32_t time, uint32_t delta){

    oled_write_sprite_string_positioned("volume", 6, (vec16_t){32, 8}, -1);
}

volume_mode = (mode_t){ &encoder_update_volume, &oled_task_volume };
