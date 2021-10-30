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

#include "macroball.h"
#include "pointing_device.h"
#include "pmw/pmw.h"

#define CLAMP_HID(value) value < -127 ? -127 : value > 127 ? 127 : value
#define DEFAULT_MOTION_CPI 2000
#define DEFAULT_SCROLL_CPI 500
#define CLAMPED_CPI_STEP(value) value < 1 ? 1 : value > 120 ? 120 : value
#define CLAMPED_SCROLL_STEP(value) value < 1 ? 1 : value > 10 ? 10 : value
#define SCROLL_STEP 100

enum encoder_mode {
    ENCM_VOLUME,
    ENCM_MOTION_CPI,
    ENCM_SCROLL_CPI
};


static const uint8_t bmp[] = {
0x00, 0x83, 0x0C, 0x03, 0x04, 0x04, 0x02, 0x0A, 0x01, 0x09, 0x02, 0x0A, 0x03, 0x09, 0x02,
0x0A, 0x03, 0x0A, 0x01, 0x04, 0x06, 0x04, 0x1E, 0x05, 0x02, 0x04, 0x02, 0x0A, 0x02, 0x09,
0x02, 0x0A, 0x02, 0x0A, 0x02, 0x0A, 0x02, 0x0A, 0x02, 0x03, 0x07, 0x03, 0x1E, 0x0C, 0x02,
0x03, 0x04, 0x03, 0x01, 0x04, 0x08, 0x03, 0x04, 0x03, 0x02, 0x03, 0x03, 0x04, 0x02, 0x03,
0x04, 0x03, 0x02, 0x03, 0x04, 0x03, 0x02, 0x03, 0x07, 0x03, 0x1E, 0x0C, 0x01, 0x04, 0x03,
0x04, 0x01, 0x03, 0x08, 0x04, 0x03, 0x04, 0x01, 0x04, 0x03, 0x03, 0x02, 0x04, 0x03, 0x04,
0x01, 0x04, 0x03, 0x04, 0x01, 0x04, 0x06, 0x04, 0x1E, 0x03, 0x01, 0x03, 0x01, 0x03, 0x02,
0x0A, 0x02, 0x03, 0x08, 0x0A, 0x02, 0x03, 0x04, 0x03, 0x02, 0x0A, 0x02, 0x0A, 0x02, 0x03,
0x07, 0x03, 0x1E, 0x04, 0x02, 0x01, 0x02, 0x03, 0x02, 0x0A, 0x01, 0x04, 0x08, 0x08, 0x04,
0x03, 0x03, 0x03, 0x03, 0x03, 0x04, 0x03, 0x02, 0x0A, 0x02, 0x03, 0x07, 0x03, 0x1E, 0x04,
0x04, 0x04, 0x01, 0x0A, 0x02, 0x03, 0x08, 0x03, 0x03, 0x03, 0x03, 0x04, 0x03, 0x03, 0x02,
0x04, 0x03, 0x03, 0x02, 0x0A, 0x02, 0x04, 0x06, 0x04, 0x1E, 0x03, 0x05, 0x03, 0x02, 0x03,
0x04, 0x03, 0x01, 0x0A, 0x02, 0x03, 0x04, 0x03, 0x02, 0x0A, 0x02, 0x0A, 0x02, 0x03, 0x04,
0x03, 0x02, 0x09, 0x01, 0x09, 0x19, 0x03, 0x05, 0x08, 0x03, 0x04, 0x02, 0x08, 0x02, 0x04,
0x04, 0x03, 0x01, 0x0A, 0x02, 0x0A, 0x02, 0x04, 0x03, 0x04, 0x01, 0x09, 0x01, 0x09,0x98,
0x91 };

static config_macroball_t kb_config;
static int8_t current_encoder_mode;

static bool scroll_pressed;
static int8_t scroll_h;
static int8_t scroll_v;

static bool mouse_buttons_dirty;

static int16_t timer;
static int16_t frameTimer;

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

    timer = timer_read();
    frameTimer = timer_read();

    // todo: move to kb startup
    current_encoder_mode = ENCM_VOLUME;

    pmw_init();

    // read config from EEPROM and update if needed
    kb_config.raw = eeconfig_read_kb();

    if(!kb_config.motion_cpi_step){
        set_motion_cpi_step(20);
        set_scroll_cpi_step(20);
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

void oled_task_user(void){

    if(timer_elapsed(frameTimer) < 250)
        return;

    // oled_clear();
    frameTimer = timer_read();

    uint8_t  width = 128;
    //   uint8_t  height = 64;
    uint16_t elapsed = timer_elapsed(timer); 
    float pi = 3.147f;
    uint16_t k = 0;
    uint8_t on = 0;

    // for(int j = 0; j < height; j++)
    // for(int i = 0; i < width; i++)
    // {
    //     oled_write_pixel(i,j, true);
    // }

    uint8_t xbuf[width];
    
    for (int i = 0; i < sizeof(bmp); i++)
    {
        uint16_t len;

        if((bmp[i] & 0x80) == 0x0){
            len = bmp[i];
         //   i++;
         }
        else{
            len = (((uint16_t)(bmp[i] & 0x7F)) << 8) | bmp[i + 1];
            i ++;
        }

                // oled_write_pixel(x, y, true);
        // if(on == 1){
            for(int j = k; j < k + len; j++){
                uint8_t x = j % width;
                uint8_t y = j / width;


                if(y == 0)
                {
                    xbuf[x] = (uint8_t)(sin((float)(x + elapsed / 50) * 4 / width * (2 * pi)) * 20) + 40;
                }

                uint8_t xbufx = xbuf[x];

                oled_write_pixel(x, y, xbufx >= y - 1 && xbufx <= y + 1 ? false : on );
            }
        // }
        
        k += len;
        on = on == 1 ? 0 : 1;
    }
    
    // for (int x = 0; x < width; x++)
    // {
    //     uint8_t l = (uint8_t)(sin((float)(x + elapsed / 50) * 4 / width * (2 * pi)) * 10) + 10;
    //     oled_write_pixel(x, l, false);
    // }

    // for (uint8_t i = 0; i < width; i++)
    // {
    //     uint8_t l = (uint8_t)(sin((float)(i + elapsed / 50) * 4 / width * (2 * pi)) * 10) + 10;

    //     for (uint8_t j = 0; j < height; j++)
    //     {
    //         oled_write_pixel(i,j, j != l ? buffer[i][j] : false);
    //     }
    // }

    
    // for (int i = 0; i < width; i++)
    // {
    //     int y = (uint8_t)(sin((float)((j % width) + elapsed / 50) * 4 / width * (2 * pi)) * 10) + 10;
    //     buffer[i, y] = 0;
    // }
    
    // for (int i = 0; i < width; i++)
    // for (int j = 0; i < height; j++)
    // {
    //     oled_write_pixel(i,j, buffer[i][j]);
    // }

    // for (int i = 0; i < width; i++){
    //     //       pixels[i][j] = 0;

    //         // oled_write_pixel(i,j,false);

    //    int l = (int)(sin((float)(i + elapsed / 50) * 4 / width * (2 * pi)) * 10) + 10;
    //     //  pixels[i][l] = true;
    //     //int k = (int)(sin(elapsed / 10000.0 * (2 * pi)) * 30) + 30;
    //      oled_write_pixel(i,l,false);
    //      oled_write_pixel(i+1,l,false);
    //      oled_write_pixel(i-1,l,false);
    //     // oled_write_pixel(i,k,true);

    // // for (int i = 0; i < width; i++)
    // // {
    // //     for(int j = 0; j < height; j++)
    // //          oled_write_pixel(i,j,pixels[i][j]);

    // // }
    // }

     return;

    switch (current_encoder_mode)
    {
        case  ENCM_VOLUME:
            oled_write_P(PSTR("Volume"), false);
            break;

        case  ENCM_MOTION_CPI:
            oled_write_P(PSTR("DPI: "), false);
            char scpi[5];
            itoa(kb_config.motion_cpi_step * CPI_STEP, scpi, 10);
            oled_write(scpi, false);
            break;

        case  ENCM_SCROLL_CPI:
            oled_write_P(PSTR("SCROLL: "), false);
            char sscroll[5];
            itoa(kb_config.scroll_cpi_step * 100, sscroll, 10);
            oled_write(sscroll, false);
            break;

        default:
            oled_write_P(PSTR("Macroball!"), false);
            break;
    }
}
