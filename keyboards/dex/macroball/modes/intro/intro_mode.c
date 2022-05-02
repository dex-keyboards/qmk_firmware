#include "intro_mode.h"

void encoder_update_intro(uint8_t index, bool clockwise){

}

void oled_task_intro(uint32_t time, uint32_t delta){


    startCoroutine;

    static uint32_t now = 0;
    int dur = 5000;

    while(now < dur){
        oled_write_sprite_string_positioned("macroball", 8, (vec16_t){ -128 + 128 * now / dur, 0}, -1);
        now += elapsed;
        yield;
    }

    endCoroutine;
}

intro_mode = (mode_t){ &encoder_update_intro, &oled_task_intro };
