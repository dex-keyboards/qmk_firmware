/* Copyright 2021 Alexander Tulloh
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

#include QMK_KEYBOARD_H

enum layer_names {
    _BASE,
    _LOWER,
    _RAISE
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [_BASE] = LAYOUT(
     KC_ENC_MODE,
     KC_BTN3,                              KC_BSPC, KC_SCROLL,
     MO(_LOWER),                           KC_UP,   KC_ENT,
     _______, KC_BTN1, KC_BTN2, KC_MPLY, KC_LEFT, KC_DOWN, KC_RGHT
  ),

  [_LOWER] = LAYOUT(
     RESET,
     RGB_MOD,                                     RGB_TOG, _______,
     _______,                                     KC_PGUP, KC_LSFT,
     _______, RGB_HUI, RGB_SAI, RGB_VAI, KC_HOME, KC_PGDN, KC_END
  ),

  [_RAISE] = LAYOUT(
     _______,
     _______,                                     _______, _______,
     _______,                                     _______, _______,
     _______, _______, _______, _______, _______, _______, _______
  )
};
