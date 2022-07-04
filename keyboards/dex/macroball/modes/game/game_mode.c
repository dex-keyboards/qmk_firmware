#include "game_mode.h"
#include "../../coroutine.h"
#include "../../sprites/ball_sprite.h"
#include "../../sprites/palm_sprite.h"

static vec16_t ball_position = (vec16_t){ 56, 16 };
static vec16_t ball_velocity = (vec16_t){ 0, 0 };

void oled_task_game(uint32_t time, uint32_t delta, vec16_t offset){

    ball_position = add_vec16(ball_position, ball_velocity);

    oled_write_sprite_positioned(palm_sprite, add_vec16((vec16_t){ 56, 16 }, offset));

    static uint32_t start;

    startCoroutine;

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

    oled_write_sprite_positioned(ball_frame_4_sprite, add_vec16(ball_position, offset));

    endCoroutine;
}

// static uvec8_t left_key = (uvec8_t){ 3, 4};
// static uvec8_t right_key = (uvec8_t){ 3, 6};
// static uvec8_t down_key = (uvec8_t){ 3, 5};
// static uvec8_t up_key = (uvec8_t){ 2, 5};

// static bool matrix_is_on_key(uvec8_t* key){
//     return matrix_is_on((*key).x, (*key).y);
// }

bool process_record_game(uint16_t keycode, keyrecord_t *record){

    if (keycode == keymaps[0][3][4]) {
        if(record->event.pressed)
            ball_velocity.x -= 1;
        else
            ball_velocity.x += 1;

        return false;
    }

    if (keycode == keymaps[0][3][6]) {
        if(record->event.pressed)
            ball_velocity.x += 1;
        else
            ball_velocity.x -= 1;

        return false;
    }
    

    // if(matrix_is_on_key(&left_key)){
    //     ball_position.x -= 1;
    // }

    // if(matrix_is_on_key(&right_key)){
    //     ball_position.x += 1;
    // }

    // if(matrix_is_on_key(&down_key)){
    //     ball_position.y -= 1;
    // }

    // if(matrix_is_on_key(&up_key)){
    //     ball_position.y += 1;
    // }

    return true;
}

mode_t game_mode = (mode_t){ NULL, &oled_task_game, &process_record_game };
