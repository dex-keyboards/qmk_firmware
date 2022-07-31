#include "game_mode.h"
#include "../../util/coroutine.h"
#include "../../sprites/ball_sprite.h"
#include "../../sprites/palm_sprite.h"

static vec16_t ball_position = (vec16_t){ 56, 16 };
static vec16_t ball_velocity = (vec16_t){ 0, 0 };

static void bounce_coroutine(uint32_t time, vec16_t offset){

    static uint32_t start;

    startCoroutine;

    start = time;

    while(time - start < 500 && is_zero_vec16(ball_velocity))
    {
        oled_write_sprite_positioned(ball_frame_0_sprite, add_vec16(ball_position, offset));
        yield;
    }

    start = time;

    while(time - start < 400 && is_zero_vec16(ball_velocity))
    {
        oled_write_sprite_positioned(ball_frame_4_sprite, add_vec16(ball_position, offset));
        yield;
    }
    
    if(!is_zero_vec16(ball_velocity)){
        
        start = time;

        while(time - start < 100)
        {
            oled_write_sprite_positioned(ball_frame_0_sprite, add_vec16(ball_position, offset));
            yield;
        }

        start = time;

        while(time - start < 50)
        {
            oled_write_sprite_positioned(ball_frame_1_sprite, add_vec16(ball_position, offset));
            yield;
        }

        start = time;

        while(time - start < 200)
        {
            oled_write_sprite_positioned(ball_frame_2_sprite, add_vec16(ball_position, offset));
            yield;
        }

        start = time;

        while(time - start < 50)
        {
            oled_write_sprite_positioned(ball_frame_3_sprite, add_vec16(ball_position, offset));
            yield;
        }

        start = time;

        while(time - start < 50)
        {
            oled_write_sprite_positioned(ball_frame_4_sprite, add_vec16(ball_position, offset));
            yield;
        }
    }
    
    oled_write_sprite_positioned(ball_frame_0_sprite, add_vec16(ball_position, offset));

    endCoroutine;    
}

void oled_task_game(uint32_t time, uint32_t delta, vec16_t offset){

    ball_position = add_vec16(ball_position, ball_velocity);

    oled_write_sprite_positioned(palm_sprite, add_vec16((vec16_t){ -8, -8 }, offset));
    oled_write_sprite_positioned(palm_sprite, add_vec16((vec16_t){ 16, 8 }, offset));
    oled_write_sprite_positioned(palm_sprite, add_vec16((vec16_t){ 72, 0 }, offset));

    bounce_coroutine(time, offset);
    
    oled_write_sprite_positioned(palm_sprite, add_vec16((vec16_t){ 8, 54 }, offset));
    oled_write_sprite_positioned(palm_sprite, add_vec16((vec16_t){ 96, 32 }, offset));
}

bool process_record_game(uint16_t keycode, keyrecord_t *record){

    if (keycode == keymaps[0][3][4]) {
        if(record->event.pressed)
            ball_velocity.x -= 2;
        else
            ball_velocity.x += 2;

        return false;
    }

    if (keycode == keymaps[0][3][6]) {
        if(record->event.pressed)
            ball_velocity.x += 2;
        else
            ball_velocity.x -= 2;

        return false;
    }

    if (keycode == keymaps[0][3][5]) {
        if(record->event.pressed)
            ball_velocity.y += 1;
        else
            ball_velocity.y -= 1;

        return false;
    }

    if (keycode == keymaps[0][2][5]) {
        if(record->event.pressed)
            ball_velocity.y -= 1;
        else
            ball_velocity.y += 1;

        return false;
    }

    return true;
}

mode_t game_mode = (mode_t){ NULL, &oled_task_game, &process_record_game };
