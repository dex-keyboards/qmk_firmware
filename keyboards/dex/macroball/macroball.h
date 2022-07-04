/* Copyright 2020 Alexander Tulloh
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#include "quantum.h"

#define LAYOUT( \
    K00, \
    K10,                     K15, K16, \
    K20,                     K25, K26, \
    K30, K31, K32, K33, K34, K35, K36 \
    ) \
    { \
        { K00, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO }, \
        { K10, KC_NO, KC_NO, KC_NO, KC_NO, K15, K16 }, \
        { K20, KC_NO, KC_NO, KC_NO, KC_NO, K25, K26 }, \
        { K30, K31, K32, K33, K34, K35, K36 } \
    }

enum custom_keycodes {
    KC_SCROLL = SAFE_RANGE,
    KC_ENC_MODE
};

typedef union {
  uint32_t raw;
  struct {
    uint8_t motion_cpi_step;
    uint8_t scroll_cpi_step;
  };
} config_macroball_t;

typedef struct {
    uint8_t x;
    uint8_t y;
} uvec8_t;

typedef struct {
    int16_t x;
    int16_t y;
} vec16_t;

vec16_t add_vec16(vec16_t a, vec16_t b);

typedef struct {
    const uvec8_t size;
    const char* diffuse;
    const char* alpha;
} sprite_t;

typedef struct {
    const char value;
    const vec16_t offset;
    const sprite_t* sprite;
} glyph_t;

typedef void (*encoder_update_mode_t)(uint8_t index, bool clockwise);

typedef void (*oled_task_mode_t)(uint32_t time, uint32_t delta, vec16_t offset);

typedef bool (*process_record_mode_t)(uint16_t keycode, keyrecord_t *record);

typedef struct {
    const encoder_update_mode_t encoder_update_mode;
    const oled_task_mode_t oled_task_mode;
    const process_record_mode_t process_record_mode;
} mode_t;

uint8_t get_motion_cpi_step(void);

void set_motion_cpi_step(uint8_t cpi_step);

uint8_t get_scroll_cpi_step(void);

void set_scroll_cpi_step(uint8_t cpi_step);

void oled_write_sprite_positioned(sprite_t sprite, vec16_t position);

void oled_write_sprite_string_positioned(
    char* value,
    uint8_t length,
    vec16_t position,
    int8_t character_width);

#define SCROLL_STEP 1
#define CPI_STEP 100
