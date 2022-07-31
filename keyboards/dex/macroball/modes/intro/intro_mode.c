#include "intro_mode.h"
#include "../../util/coroutine.h"

void oled_task_intro(uint32_t time, uint32_t delta, vec16_t offset){

    startCoroutine;

    static uint32_t now = 0;
    int dur = 5000;

    while(now < dur){
        oled_write_sprite_string_positioned("macroball", 9, add_vec16((vec16_t){ -128 + 128 * now / dur, 0}, offset), -1);
        now += delta;
        yield;
    }

    now = 0;

    while(now < 2000){
        oled_write_sprite_string_positioned("macroball", 9, offset, -1);
        now += delta;
        yield;
    }

    now = 0;

    endCoroutine;
}

mode_t intro_mode = (mode_t){ NULL, &oled_task_intro, NULL };
