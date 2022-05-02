#pragma once

#include "../../macroball.h"

void encoder_update_volume(uint8_t index, bool clockwise);

void oled_task_volume(uint32_t time, uint32_t delta);

mode_t volume_mode = (mode_t){ &encoder_update_volume, &oled_task_volume };
