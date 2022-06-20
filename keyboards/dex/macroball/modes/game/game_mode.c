#include "game_mode.h"
#include "../../coroutine.h"
#include "../../sprites/ball_sprite.h"
#include "../../sprites/palm_sprite.h"

static vec16_t ball_position = (vec16_t){ 56, 16 };

void oled_task_game(uint32_t time, uint32_t delta){

    oled_write_sprite_positioned(palm_sprite, (vec16_t){ 56, 16 });

    static uint32_t start;

    startCoroutine;

    start = time;

    while(time - start < 100)
    {
        oled_write_sprite_positioned(ball_frame_0_sprite, ball_position);
        yield;
    }

    start = time;

    while(time - start < 50)
    {
        oled_write_sprite_positioned(ball_frame_1_sprite, ball_position);
        yield;
    }

    start = time;

    while(time - start < 200)
    {
        oled_write_sprite_positioned(ball_frame_2_sprite, ball_position);
        yield;
    }

    start = time;

    while(time - start < 50)
    {
        oled_write_sprite_positioned(ball_frame_3_sprite, ball_position);
        yield;
    }

    start = time;

    while(time - start < 50)
    {
        oled_write_sprite_positioned(ball_frame_4_sprite, ball_position);
        yield;
    }

    oled_write_sprite_positioned(ball_frame_4_sprite, ball_position);

    endCoroutine;
}

static uvec8_t left_key = (uvec8_t){ 3, 4};
static uvec8_t right_key = (uvec8_t){ 3, 6};
static uvec8_t down_key = (uvec8_t){ 3, 5};
static uvec8_t up_key = (uvec8_t){ 2, 5};

static bool matrix_is_on_key(uvec8_t* key){
    return matrix_is_on((*key).x, (*key).y);
}

bool process_record_game(uint16_t keycode, keyrecord_t *record){

    if(matrix_is_on_key(&left_key)){
        ball_position.x -= 1;
    }

    if(matrix_is_on_key(&right_key)){
        ball_position.x += 1;
    }

    if(matrix_is_on_key(&down_key)){
        ball_position.y -= 1;
    }

    if(matrix_is_on_key(&up_key)){
        ball_position.y += 1;
    }

    return false;
}

mode_t game_mode = (mode_t){ NULL, &oled_task_game, &process_record_game };
