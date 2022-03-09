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

#include <string.h>
#include "macroball.h"
#include "pointing_device.h"
#include "pmw/pmw.h"
#include "../coroutine.h"

static const char PROGMEM bmp[] = {
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xC0, 0xE0,
0xE0, 0xE0, 0xE0, 0xC0, 0xE0, 0xE0, 0xE0, 0xE0, 0xC0, 0x00, 0x00, 0x00, 0x80, 0xC0, 0xE0, 0xE0,
0xE0, 0xE0, 0xE0, 0xC0, 0x00, 0x00, 0x00, 0x80, 0xC0, 0xE0, 0xE0, 0xE0, 0xE0, 0xE0, 0xC0, 0x00,
0x00, 0x00, 0xC0, 0xE0, 0xE0, 0xE0, 0xE0, 0xE0, 0xE0, 0x40, 0x00, 0x00, 0x00, 0xC0, 0xE0, 0xE0,
0xE0, 0xE0, 0xE0, 0xE0, 0x00, 0x00, 0x00, 0x00, 0x80, 0xE0, 0xE0, 0xE0, 0xE0, 0xE0, 0xE0, 0xC0,
0x00, 0x00, 0x00, 0x80, 0xC0, 0xE0, 0xE0, 0xE0, 0xE0, 0xE0, 0xC0, 0x00, 0x00, 0x00, 0xE0, 0xE0,
0xE0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xE0, 0xE0, 0xE0, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF8, 0xFF, 0x7F, 0x07,
0xF0, 0xFF, 0xFF, 0x0F, 0xE0, 0xFE, 0xFF, 0x1F, 0x01, 0x00, 0x80, 0xF8, 0xFF, 0x7F, 0x1F, 0xFC,
0xFF, 0xFF, 0x0F, 0x00, 0x00, 0x00, 0xF8, 0xFF, 0xFF, 0xE7, 0xF0, 0xF1, 0x71, 0x01, 0x00, 0x00,
0x80, 0xF8, 0xFF, 0x7F, 0x0F, 0xFE, 0xFF, 0x7F, 0x03, 0x00, 0x00, 0x40, 0xFC, 0xFF, 0xFF, 0xE3,
0xF8, 0xFF, 0x7F, 0x07, 0x00, 0x00, 0x00, 0xF8, 0xFF, 0xFF, 0xEF, 0xFE, 0xFF, 0x7F, 0x03, 0x00,
0x00, 0x80, 0xF8, 0xFF, 0x7F, 0x1F, 0xFC, 0xFF, 0xFF, 0x0F, 0x00, 0x00, 0x40, 0xFC, 0xFF, 0xFF,
0xE1, 0xE0, 0xE0, 0x60, 0x00, 0x00, 0x00, 0x40, 0xFC, 0xFF, 0xFF, 0xE1, 0xE0, 0xE0, 0x60, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };

static const char PROGMEM ball_diffuse[] = {
0x00, 0x00, 0x80, 0xF8, 0x18, 0x08, 0x0C, 0x04, 0xE4, 0xE4, 0xCC, 0x08, 0x78, 0xE0, 0x00, 0x00,
0x00, 0x00, 0x01, 0x0F, 0x18, 0x10, 0x20, 0x20, 0x20, 0x20, 0x30, 0x18, 0x0E, 0x03, 0x00, 0x00, };

static const char PROGMEM ball_alpha[] = {
0x00, 0x00, 0x80, 0xF8, 0xF8, 0xF8, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xF8, 0xF8, 0xE0, 0x00, 0x00,
0x00, 0x00, 0x01, 0x0F, 0x1F, 0x1F, 0x3F, 0x3F, 0x3F, 0x3F, 0x3F, 0x1F, 0x0F, 0x03, 0x00, 0x00 };

const char palm_diffuse[] PROGMEM = {
0x00, 0x10, 0x1C, 0x9C, 0xDE, 0xDE, 0xDE, 0xFC, 0xFC, 0xF8, 0xF0, 0xE0, 0xF0, 0xF8, 0xFC, 0xFC,
0xDE, 0xDE, 0x9E, 0x0E, 0x0E, 0x0C, 0x00, 0x00, 0x00, 0x7C, 0xFF, 0x3F, 0x0F, 0x07, 0x07, 0x03,
0x7B, 0xF1, 0xC7, 0x0F, 0x3F, 0xFF, 0xFF, 0xE7, 0x07, 0x0F, 0x0F, 0x1F, 0x7E, 0x70, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF0, 0xF7, 0xD6, 0x92, 0xBA, 0xBC, 0x00, 0x00, 0x07, 0x1F,
0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };

const char palm_alpha[] PROGMEM = {
0x00, 0x10, 0x1C, 0x9C, 0xDE, 0xDE, 0xDE, 0xFC, 0xFC, 0xF8, 0xF0, 0xE0, 0xF0, 0xF8, 0xFC, 0xFC,
0xDE, 0xDE, 0x9E, 0x0E, 0x0E, 0x0C, 0x00, 0x00, 0x00, 0x7C, 0xFF, 0x3F, 0x0F, 0x07, 0x07, 0x03,
0x7B, 0xF1, 0xC7, 0x0F, 0x3F, 0xFF, 0xFF, 0xE7, 0x07, 0x0F, 0x0F, 0x1F, 0x7E, 0x70, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF0, 0xF7, 0xD6, 0x92, 0xBA, 0xBC, 0x00, 0x00, 0x07, 0x1F,
0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

sprite_t palm_sprite = {
  .width = 24,
  .height = 24,
  .diffuse = palm_diffuse,
  .alpha = palm_alpha
};

static sprite_t ball_sprite = {
  .width = 16,
  .height = 16,
  .diffuse = ball_diffuse,
  .alpha = ball_alpha
};

// static sprite_t full_sprite = {
//   .width = 128,
//   .height = 16,
//   .diffuse = bmp,
//   .alpha = NULL
// };

#define CLAMP_HID(value) value < -127 ? -127 : value > 127 ? 127 : value
#define DEFAULT_MOTION_CPI 500
#define DEFAULT_SCROLL_CPI 100
#define CLAMPED_CPI_STEP(value) value < 1 ? 1 : value > 120 ? 120 : value
#define CLAMPED_SCROLL_STEP(value) value < 1 ? 1 : value > 10 ? 10 : value
#define SCROLL_STEP 1

enum encoder_mode {
    ENCM_VOLUME,
    ENCM_MOTION_CPI,
    ENCM_SCROLL_CPI
};

static config_macroball_t kb_config;
static int8_t current_encoder_mode;

static bool scroll_pressed;
static int8_t scroll_h;
static int8_t scroll_v;

static bool mouse_buttons_dirty;

static void set_motion_cpi_step(uint8_t cpi_step){

    uint8_t clamped_cpi_step = CLAMPED_CPI_STEP(cpi_step);

    pmw_set_config((config_pmw_t){ clamped_cpi_step * CPI_STEP});

    kb_config.motion_cpi_step = clamped_cpi_step;
    eeconfig_update_kb(kb_config.raw);
}

static void set_scroll_cpi_step(uint8_t scroll_step){

    uint8_t clamped_scroll_step = CLAMPED_SCROLL_STEP(scroll_step);

    kb_config.scroll_cpi_step = clamped_scroll_step;
    eeconfig_update_kb(kb_config.raw);
}

void pointing_device_init(void){

    // todo: move to kb startup
    current_encoder_mode = ENCM_VOLUME;

    pmw_init();

    // read config from EEPROM and update if needed
    kb_config.raw = eeconfig_read_kb();

    if(kb_config.motion_cpi_step){
        set_motion_cpi_step(kb_config.motion_cpi_step);
        //set_scroll_cpi_step(kb_config.scroll_cpi_step);
    }
    else{
        set_motion_cpi_step(DEFAULT_MOTION_CPI / 100);
        set_scroll_cpi_step(SCROLL_STEP);
    }
}

void pointing_device_task(void){

    report_mouse_t mouse_report = pointing_device_get_report();
    report_pmw_t sensor_report = pmw_get_report();

    int8_t clamped_x = CLAMP_HID(sensor_report.x);
    int8_t clamped_y = CLAMP_HID(sensor_report.y);

    if(scroll_pressed) {

        // accumulate scroll
        scroll_h += clamped_x;
        scroll_v += clamped_y;

        int8_t scaled_scroll_h = scroll_h / kb_config.motion_cpi_step * kb_config.scroll_cpi_step;
        int8_t scaled_scroll_v = scroll_v / kb_config.motion_cpi_step * kb_config.scroll_cpi_step;

        // clear accumulated scroll on assignment

        if(scaled_scroll_h != 0){
            mouse_report.h = -scaled_scroll_h * SCROLL_STEP;
            scroll_h = 0;
        }

        if(scaled_scroll_v != 0){
            mouse_report.v = -scaled_scroll_v * SCROLL_STEP;
            scroll_v = 0;
        }
    }
    else {
        mouse_report.x = -clamped_x;
        mouse_report.y = clamped_y;
    }

    pointing_device_set_report(mouse_report);

    // only send report on change as even sending report with no change is treated as movement
    if(mouse_buttons_dirty ||
       mouse_report.x != 0 ||
       mouse_report.y != 0 ||
       mouse_report.h != 0 ||
       mouse_report.v != 0){

        mouse_buttons_dirty = false;
        pointing_device_send();
    }
}

bool encoder_update_kb(uint8_t index, bool clockwise) {

    switch (current_encoder_mode)
    {
        case  ENCM_VOLUME:
            if (clockwise) {
                tap_code(KC_VOLD);
            } else {
                tap_code(KC_VOLU);
            }
            break;

        case  ENCM_MOTION_CPI:
            set_motion_cpi_step(kb_config.motion_cpi_step + (clockwise ? 1 : -1));
            break;

        case  ENCM_SCROLL_CPI:
            set_scroll_cpi_step(kb_config.scroll_cpi_step + (clockwise ? 1 : -1));
            break;

        default:
            break;
    }

    return true;

}

static void on_mouse_button(uint8_t mouse_button, keyrecord_t *record) {

    report_mouse_t report = pointing_device_get_report();

    if(record->event.pressed)
        report.buttons |= mouse_button;
    else
        report.buttons &= ~mouse_button;

    pointing_device_set_report(report);
    mouse_buttons_dirty = true;
}

static void on_next_encoder_mode(keyrecord_t *record){
    if(record->event.pressed && current_encoder_mode++ == ENCM_SCROLL_CPI)
        current_encoder_mode = ENCM_VOLUME;
}

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {

    if(!process_record_user(keycode, record))
        return false;

    // handle mouse drag and scroll

    switch (keycode) {
        case KC_BTN1:
            on_mouse_button(MOUSE_BTN1, record);
            return false;

        case KC_BTN2:
            on_mouse_button(MOUSE_BTN2, record);
            return false;

        case KC_BTN3:
            on_mouse_button(MOUSE_BTN3, record);
            return false;

        case KC_BTN4:
            on_mouse_button(MOUSE_BTN4, record);
            return false;

        case KC_BTN5:
            on_mouse_button(MOUSE_BTN5, record);
            return false;

        case KC_SCROLL:
            scroll_pressed = record->event.pressed;
            return false;

        case KC_ENC_MODE:
            on_next_encoder_mode(record);
            return false;

        default:
            return true;
  }
}

#define MIN(x, min) x < min ? x: min
#define MAX(x, max) x > max ? x: max
#define CLAMP(x, min, max) MIN(max, MAX(x, min))

static uint8_t *screen_buffer;

static void oled_write_sprite_positioned(sprite_t sprite, int16_t x, int16_t y) {
    
    if (x >= OLED_DISPLAY_WIDTH)
        return;

    if (y >= OLED_DISPLAY_HEIGHT)
        return;

    int16_t end_x = x + sprite.width;
    if (end_x < 0)
        return;

    int16_t end_y = y + sprite.height;
    if (end_y < 0)
        return;

    uint8_t resolved_x = MAX(x, 0);
    uint8_t resolved_end_x = MIN(end_x, OLED_DISPLAY_WIDTH);
    uint8_t resolved_w = resolved_end_x - resolved_x;
    uint16_t offset_x = resolved_x - x;

    uint8_t y_space = 8;
    uint8_t resolved_y = (y >= 0 ? y : 0) / y_space;
    uint8_t resolved_end_y = (end_y < OLED_DISPLAY_HEIGHT ? end_y : OLED_DISPLAY_HEIGHT) / y_space;
    uint8_t resolved_h = resolved_end_y - resolved_y;
    uint16_t offset_y = resolved_y - (y >= 0 ? y : y - y_space + 1) / y_space;

    for (uint8_t j = 0; j < resolved_h; j++) {
        for (uint8_t i = 0; i < resolved_w; i++) {

            uint16_t index = i + offset_x + (j + offset_y) * sprite.width;
            uint8_t alpha = sprite.alpha == NULL ? 0xFF : pgm_read_byte(sprite.alpha + index);
            uint8_t diffuse = pgm_read_byte(sprite.diffuse + index);

            uint16_t screen_index = (j + resolved_y) * OLED_DISPLAY_WIDTH + resolved_x + i;
            uint8_t current = screen_buffer[screen_index];
            screen_buffer[screen_index] = current ^ ((current ^ diffuse) & alpha);
        }
    }
}

static void coroutine(uint32_t time, uint32_t delta) {

    oled_clear();

    oled_write_sprite_positioned(ball_sprite, 56, 24);        

    int grid_size = 10;
    int grid_spacing = 50;

    for(int j = 0; j < grid_size; j++){
        for(int k = 0; k < grid_size; k++){
            oled_write_sprite_positioned(
                palm_sprite,
                j * grid_spacing - grid_size * grid_spacing / 2,
                k * grid_spacing - grid_size * grid_spacing / 2);
        }
    }
}

static uint32_t oled_timer;

static uint32_t frame_duration = 50;

void oled_task_user(void) {

    if (oled_timer == 0)
        oled_timer = timer_read32();

    uint32_t elapsed = timer_elapsed32(oled_timer);

    if (elapsed < frame_duration)
        return;

    screen_buffer = oled_read_raw(0).current_element;

    switch (current_encoder_mode)
    {
        case  ENCM_VOLUME:

            coroutine(oled_timer, elapsed);
            break;

        case  ENCM_MOTION_CPI:
            oled_set_cursor(0,0);
            oled_write("DPI: ", false);
            char scpi[5];
            itoa(kb_config.motion_cpi_step * CPI_STEP, scpi, 10);
            oled_write(scpi, false);
            break;

        case  ENCM_SCROLL_CPI:
            oled_set_cursor(0,0);
            oled_write_raw("SCROLL: ", false);
            char sscroll[5];
            itoa(kb_config.scroll_cpi_step * 100, sscroll, 10);
            oled_write(sscroll, false);
            break;

        default:
            //oled_write_P(PSTR("Macroball!"), false);
            break;
    }
    
    oled_timer = timer_read32();
}