#include "game_mode.h"

void encoder_update_game(uint8_t index, bool clockwise){

}

void oled_task_game(uint32_t time, uint32_t delta){


    static uint32_t start;

    startCoroutine;

    start = time;

    while(time - start < 100)
    {
        oled_write_sprite_positioned(ball_frame_0_sprite, (vec16_t){ 56, 16 });
        yield;
    }

    start = time;

    while(time - start < 50)
    {
        oled_write_sprite_positioned(ball_frame_1_sprite, (vec16_t){ 56, 16 });
        yield;
    }

    start = time;

    while(time - start < 200)
    {
        oled_write_sprite_positioned(ball_frame_2_sprite, (vec16_t){ 56, 16 });
        yield;
    }

    start = time;

    while(time - start < 50)
    {
        oled_write_sprite_positioned(ball_frame_3_sprite, (vec16_t){ 56, 16 });
        yield;
    }

    start = time;

    while(time - start < 50)
    {
        oled_write_sprite_positioned(ball_frame_4_sprite, (vec16_t){ 56, 16 });
        yield;
    }

    oled_write_sprite_positioned(ball_frame_4_sprite, (vec16_t){ 56, 16 });

    endCoroutine;

}

game_mode = (mode_t){ &encoder_update_game, &oled_task_game };
