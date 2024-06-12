/*
Copyright 2022 @Yowkees
Copyright 2022 MURAOKA Taro (aka KoRoN, @kaoriya)

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H

#include "quantum.h"

// Tap Dance declarations
enum {
    TD_9, TD_0, TD_M, TD_U, TD_D,
};

// Tap Dance definitions
tap_dance_action_t tap_dance_actions[] = {
    // Tap once for Escape, twice for Caps Lock
    [TD_9] = ACTION_TAP_DANCE_DOUBLE(KC_9, KC_LBRC),
    [TD_0] = ACTION_TAP_DANCE_DOUBLE(KC_0, KC_RBRC),
    [TD_M] = ACTION_TAP_DANCE_DOUBLE(KC_MINS, KC_EQL),
    [TD_U] = ACTION_TAP_DANCE_DOUBLE(KC_HOME, KC_PGUP),
    [TD_D] = ACTION_TAP_DANCE_DOUBLE(KC_END, KC_PGDN),
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    static uint16_t hold_timer = 0;

    switch (keycode) {
        case KC_H:
            if (record->event.pressed) {
                hold_timer = timer_read();
            } else {
                if (timer_elapsed(hold_timer) < TAPPING_TERM) {
                    tap_code(KC_H); // Tap: Send 'h'
                } else {
                    tap_code(KC_ESC); // Hold: Send 'Esc'
                }
            }
            return false;
    }
    return true;
}

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT_universal(
    KC_GRV   , KC_1      , KC_2       , KC_3        , KC_4        , KC_5        ,                                  KC_6     , KC_7        , KC_8        , TD(TD_9)    , TD(TD_0) , TD(TD_M) ,
    KC_DEL   , KC_Q      , KC_W       , KC_E        , KC_R        , KC_T        ,                                  KC_Y     , KC_U        , KC_I        , KC_O        , KC_P     , KC_NUBS  ,
    KC_CAPS  , LT(1,KC_A), CTL_T(KC_S), SFT_T(KC_D) , ALT_T(KC_F) , GUI_T(KC_G) ,                                  KC_H     , ALT_T(KC_J) , SFT_T(KC_K) , CTL_T(KC_L) , KC_SCLN  , KC_QUOT  ,
    KC_LSFT  , KC_Z      , KC_X       , KC_C        , KC_V        , KC_B        , KC_F5    ,              KC_ESC , KC_N     , KC_M        , KC_COMM     , KC_DOT      , KC_SLSH  , KC_RSFT  ,
    KC_LCTL  , KC_LGUI   , KC_LALT    , _______     , KC_SPC      , KC_BSPC     , KC_LGUI  ,              KC_TAB , KC_ENT   , _______     , _______     , _______     , KC_LNG2  , TO(2)
  ),

  [1] = LAYOUT_universal(
    _______  , KC_F1    , KC_F2    , KC_F3     , KC_F4    , KC_F5   ,                                  KC_F6    , KC_F7    , KC_F8    , KC_F9    , KC_F10   , KC_F11   ,
    _______  , _______  , _______  , _______   , _______  , _______ ,                                  _______  , TD(TD_U) , KC_UP    , TD(TD_D) , _______  , KC_F12   ,
    _______  , _______  , KC_LCTL  , KC_LSFT   , KC_LALT  , _______ ,                                  _______  , KC_LEFT  , KC_DOWN  , KC_RGHT  , _______  , _______  ,
    _______  , _______  , _______  , _______   , _______  , _______ , _______  ,            _______  , _______  , _______  , _______  , _______  , _______  , _______  ,
    _______  , _______  , _______  , _______   , _______  , _______ , _______  ,            _______  , KC_LNG1  , _______  , _______  , _______  , _______  , _______
  ),

  [2] = LAYOUT_universal(
    _______  , AML_TO   , AML_I50  , AML_D50  , _______  , _______  ,                                  CPI_D1K  , CPI_D100 , CPI_I100 , CPI_I1K  , RGB_M_SN , RGB_M_K  ,
    _______  , _______  , CPI_I100 , CPI_D100 , _______  , _______  ,                                  _______  , AML_TO   , _______  , _______  , _______  , _______  ,
    KBC_SAVE , _______  , SSNP_VRT , SSNP_HOR , SCRL_MO  , _______  ,                                  _______  , KC_BTN1  , KC_BTN2  , _______  , _______  , _______  ,
    _______  , _______  , SCRL_DVI , SCRL_DVD , _______  , _______  , EE_CLR   ,            _______  , _______  , _______  , _______  , _______  , _______  , _______  ,
    QK_BOOT  , _______  , _______  , _______  , _______  , _______  , _______  ,            _______  , _______  , _______  , _______  , _______  , QK_BOOT  , TO(0)
  ),
};
// clang-format on

// layer_state_t layer_state_set_user(layer_state_t state) {
//     // Auto enable scroll mode when the highest layer is 2
//     keyball_set_scroll_mode(get_highest_layer(state) == 2);
//     return state;
// }

#ifdef OLED_ENABLE

#include "lib/oledkit/oledkit.h"

void oledkit_render_info_user(void) {
    keyball_oled_render_keyinfo();
    keyball_oled_render_ballinfo();
    keyball_oled_render_layerinfo();
}
#endif
