/* Copyright 2023 Brian Low
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

// Left-hand home row mods
#define CTL_A LCTL_T(KC_A)
#define ALT_S LALT_T(KC_S)
#define SFT_F LSFT_T(KC_F)
#define GUI_D LGUI_T(KC_D)

// Right-hand home row mods
#define GUI_K RGUI_T(KC_K)
#define SFT_J RSFT_T(KC_J)
#define ALT_L LALT_T(KC_L)
#define CTL_SCLN RCTL_T(KC_SCLN)

#define Q_MOD LT(_Q, KC_Q)
#define TAB_MEH MEH_T(KC_TAB)
#define DEL_WORD LALT(KC_BSPC)
#define DEL_LINE LGUI(KC_BSPC)
#define ARR_ESC LT(_ARROWS, KC_ESC)
#define SYM_V LT(_V, KC_V)
#define SYM_M LT(_M, KC_M)

enum sofle_layers {
    _QWERTY,
    _ARROWS,
    _Q,
    _V,
    _M,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
     * QWERTY
     * ,-----------------------------------------.                    ,-----------------------------------------.
     * |  `   |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  |  `   |
     * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
     * | ESC  |   Q  |   W  |   E  |   R  |   T  |                    |   Y  |   U  |   I  |   O  |   P  | Bspc |
     * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
     * | Tab  |   A  |   S  |   D  |   F  |   G  |-------.    ,-------|   H  |   J  |   K  |   L  |   ;  |  '   |
     * |------+------+------+------+------+------|  Mute |    | Pause |------+------+------+------+------+------|
     * |LShift|   Z  |   X  |   C  |   V  |   B  |-------|    |-------|   N  |   M  |   ,  |   .  |   /  |RShift|
     * `-----------------------------------------/       /     \      \-----------------------------------------'
     *            | LCTL | LGUI | LCMD | LALT | /Enter  /       \Space \  | RALT | RCMD | RGUI | RCTL |
     *            |      |      |      |      |/       /         \      \ |      |      |      |      |
     *            `----------------------------------'           '------''---------------------------'
     */

[_QWERTY] = LAYOUT(
    KC_GRV,   KC_1,   KC_2,    KC_3,    KC_4,    KC_5,                                          KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS,
    TAB_MEH,  Q_MOD,  KC_W,    KC_E,    KC_R,    KC_T,                                          KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_EQL,
    ARR_ESC,  CTL_A,   ALT_S,  GUI_D,   SFT_F,   KC_G,                                          KC_H,    SFT_J,   GUI_K,   ALT_L,   CTL_SCLN, KC_QUOT,
    KC_LSFT,  KC_Z,  KC_X,     KC_C,    SYM_V,   KC_B,    KC_MUTE,                 KC_MPLY,     KC_N,    SYM_M,   KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
                     KC_LALT,  KC_LGUI, KC_BSPC, DEL_WORD,DEL_LINE,        LGUI(KC_SPC),KC_ENT,  KC_SPC,  KC_RGUI, KC_RCTL
),

[_ARROWS] = LAYOUT(
    _______, _______, _______, _______, _______,  _______,                           _______,    _______,       _______,    _______,       _______,   _______,
    _______, _______, _______, _______, _______,  _______,                        LALT(KC_LEFT), LALT(KC_DOWN), LALT(KC_UP), LALT(KC_RGHT),_______,   _______,
    _______, KC_LSFT, _______, _______, _______,  _______,                        KC_LEFT,       KC_DOWN,       KC_UP,       KC_RGHT,      _______,   _______,
    _______, RGB_TOG, _______,  _______, _______, _______, _______,       _______,LGUI(KC_LEFT), LGUI(KC_DOWN), LGUI(KC_UP), LGUI(KC_RGHT), _______,   _______,
                      _______, _______, _______,  _______, _______,       _______,_______,       _______,       _______,     _______
),

[_V] = LAYOUT(
    _______, _______, _______, _______, _______,  _______,                        _______, _______,       _______,       _______,      _______,      _______,
    _______, _______, _______, _______, _______,  _______,                        _______, LSFT(KC_LBRC), LSFT(KC_RBRC), KC_MINS,      LSFT(KC_EQL), _______,
    _______, _______, _______, _______, _______,  _______,                        _______, LSFT(KC_9),    LSFT(KC_0),    LSFT(KC_MINS),KC_EQL,       _______,
    _______, _______, _______,  _______, _______, _______, _______,       _______,_______, KC_LBRC,       KC_RBRC,       LSFT(KC_BSLS),KC_BSLS,      _______,
                      _______, _______, _______,  _______, _______,       _______,_______, _______,       _______,       _______
),

[_Q] = LAYOUT(
    _______, _______, _______, _______, _______, _______,                         _______, _______,       _______,     _______,       _______,       _______,
    _______, _______, KC_F1,   KC_F2,   KC_F3,    KC_F4,                          _______, _______,       _______,     LCTL(KC_LEFT), LCTL(KC_RIGHT),_______,
    _______, _______, KC_F7,   KC_F8,   KC_F9,   _______,                         _______, LSFT(KC_QUOTE),KC_QUOTE,    _______,       _______,       _______,
    _______, _______, _______, _______, _______, _______, _______,       _______, _______, _______,       LAG(KC_LEFT),LAG(KC_RIGHT), _______,       _______,
                      _______, _______, _______, _______, _______,       _______, _______, _______,       _______,     _______
),

[_M] = LAYOUT(
    _______, _______, _______, _______, _______, _______,                         _______,    _______,    _______,    _______,    _______,    _______,
    _______, _______, _______, _______, _______, _______,                         _______,    _______,    _______,    _______,    _______,    _______,
    _______, KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_TILD,                         _______,    _______,    _______,    _______,    _______,    _______,
    _______, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_GRAVE,_______,       _______, _______,    _______,    _______,    _______,    _______,    _______,
                      _______, _______, _______, _______, _______,       _______, _______,    _______,    _______,    _______
),
};

// #if defined(ENCODER_MAP_ENABLE)
// const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
//     [_QWERTY] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_MPRV, KC_MNXT) },
//     [_ARROWS] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_MPRV, KC_MNXT) },
//     [_V]      = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_MPRV, KC_MNXT) },
//     [_Q]      = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_MPRV, KC_MNXT) },
//     [_M]      = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_MPRV, KC_MNXT) },
// };
// #endif

bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) {
        if (clockwise) {
            tap_code16(LSA(KC_F2));
        } else {
            tap_code16(LSA(KC_F1));
        }
    } else {
        if (clockwise) {
            tap_code16(LSA(KC_F12));
        } else {
            tap_code16(LSA(KC_F11));
        }
    }
    return false;
}
