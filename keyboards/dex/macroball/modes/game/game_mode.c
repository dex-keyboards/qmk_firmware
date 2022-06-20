#include "game_mode.h"
#include "../../coroutine.h"
#include "../../sprites/ball_sprite.h"
#include "../../sprites/palm_sprite.h"

void encoder_update_game(uint8_t index, bool clockwise){

}

void oled_task_game(uint32_t time, uint32_t delta){


    oled_write_sprite_positioned(palm_sprite, (vec16_t){ 56, 16 });

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

mode_t game_mode = (mode_t){ &encoder_update_game, &oled_task_game };
