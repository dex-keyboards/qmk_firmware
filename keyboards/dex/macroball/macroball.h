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
    KC_ENC_MODE,
    KC_CPI_1,
    KC_CPI_2,
    KC_CPI_3
};

typedef union {
  uint32_t raw;
  struct {
    uint8_t motion_cpi_step;
    uint8_t scroll_cpi_step;
  };
} config_macroball_t;
