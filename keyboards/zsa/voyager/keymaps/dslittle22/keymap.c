// Copyright 2023 ZSA Technology Labs, Inc <@zsa>
// Copyright 2023 Christopher Courtney, aka Drashna Jael're  (@drashna) <drashna@live.com>
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include "process_tap_dance.h"
#include "process_combo.h"

#define LCTL_A MT(MOD_LCTL, KC_A)
#define LALT_S MT(MOD_LALT, KC_S)
#define LGUI_D MT(MOD_LGUI, KC_D)
#define LSFT_F MT(MOD_LSFT, KC_F)
#define RSFT_J MT(MOD_RSFT, KC_J)
#define RGUI_K MT(MOD_RGUI, KC_K)
#define RALT_L MT(MOD_RALT, KC_L)
#define RCTL_SCLN MT(MOD_RCTL, KC_SCLN)

enum custom_keycodes {
    CMD_BSPC,
    OPT_BSPC,
    QUOTES = SAFE_RANGE,
    SQUOTES,
    BACKTICKS,
    ADDED,
    ASSIGNMENT,
    SUBTRACTED,
    MULTIPIED,
    SEL_LINE,
    SEL_WORD,
};


enum tap_dance_codes {
    OPT_CMD_BSPC,
    ALFRED_SPOTLIGHT,
    EXP_COLEMAK,
    CAPS_LOCK_WORD
};

const uint16_t PROGMEM alfred_combo_1[] = {MT(MOD_LSFT, KC_F), KC_C, COMBO_END};
const uint16_t PROGMEM alfred_combo_2[] = {MT(MOD_RSFT, KC_J), KC_COMMA, COMBO_END};

combo_t key_combos[] = {
    COMBO(alfred_combo_1, LGUI(KC_SPACE)),
    COMBO(alfred_combo_2, LGUI(KC_SPACE)),
};

typedef enum {
    TD_NONE,
    TD_UNKNOWN,
    TD_SINGLE_TAP,
    TD_SINGLE_HOLD,
    TD_DOUBLE_TAP,
    TD_DOUBLE_HOLD,
} td_state_t;


typedef struct {
    bool is_press_action;
    td_state_t state;
} td_tap_t;


typedef struct {
    uint16_t tap;
    uint16_t hold;
    uint16_t held;
} tap_dance_tap_hold_t;
tap_dance_action_t *action;

td_state_t cur_dance(tap_dance_state_t *state);

// For the x tap dance. Put it here so it can be used in any keymap
void clw_finished(tap_dance_state_t *state, void *user_data);
void clw_reset(tap_dance_state_t *state, void *user_data);

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
      MEH_T(KC_TAB),        KC_Q,     KC_W,    KC_E,   KC_R,      KC_T,                                                               KC_Y,           KC_U,    KC_I,      KC_O,    KC_P,       ALL_T(KC_BSLS),
      LT(6,KC_ESCAPE),      LCTL_A,   LALT_S,  LGUI_D, LSFT_F,    KC_G,                                                               KC_H,           RSFT_J,  RGUI_K,    RALT_L,  RCTL_SCLN,  KC_QUOTE,
      TD(CAPS_LOCK_WORD),   KC_Z,     KC_X,    KC_C,   KC_V,      KC_B,                                                               KC_N,           KC_M,    KC_COMMA,  KC_DOT,  KC_SLASH,   OSM(MOD_LSFT),
      TD(ALFRED_SPOTLIGHT), KC_PGUP,  KC_PGDN, KC_TAB, KC_GRAVE,  LT(2,KC_BSPC),                                                      LT(2,KC_SPACE), KC_LEFT, KC_DOWN,   KC_UP,   KC_RIGHT,   TD(EXP_COLEMAK),
                                                                  LT(3, OPT_BSPC),    LT(4, CMD_BSPC),                LT(3,KC_GRAVE), LT(4,KC_ENTER)
    ),
    [1] = LAYOUT(
      LT(7,KC_TAB),   KC_Q,           KC_W,           KC_F,           KC_P,           KC_B,                                                      KC_J,           KC_L,           KC_U,           KC_Y,           KC_SCLN,        KC_TRANSPARENT,
      KC_TRANSPARENT, MT(MOD_LCTL, KC_A),MT(MOD_LALT, KC_R),MT(MOD_LGUI, KC_S),MT(MOD_LSFT, KC_T),KC_G,                                          KC_M,           MT(MOD_LSFT, KC_N),MT(MOD_LGUI, KC_E),MT(MOD_LALT, KC_I),MT(MOD_LCTL, KC_O),KC_TRANSPARENT,
      KC_TRANSPARENT, KC_Z,           KC_X,           KC_C,           KC_D,           KC_V,                                                      KC_K,           KC_H,           KC_COMMA,       KC_DOT,         KC_SLASH,       KC_TRANSPARENT,
      KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                            KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
                                                                                      KC_TRANSPARENT, KC_TRANSPARENT,            KC_TRANSPARENT, KC_TRANSPARENT
    ),
    [2] = LAYOUT(
      KC_HASH,        KC_AT,          KC_AMPR,        KC_PIPE,        KC_UNDS,        KC_QUES,                                                     KC_TRANSPARENT, KC_LCBR,        KC_RCBR,        KC_GRAVE,       KC_TRANSPARENT, KC_TRANSPARENT,
      KC_CIRC,        KC_EXLM,        KC_GRAVE,       KC_QUOTE,       KC_DQUO,        KC_DLR,                                                      KC_TRANSPARENT, KC_LPRN,        KC_RPRN,        KC_QUOTE,       OSL(6),         KC_TRANSPARENT,
      KC_HASH,        KC_LABK,        KC_MINUS,       KC_EQUAL,       KC_RABK,        KC_QUES,                                                     KC_TRANSPARENT, KC_LBRC,        KC_RBRC,        KC_DQUO,        KC_TRANSPARENT, KC_TRANSPARENT,
      KC_TILD,        KC_SLASH,       KC_ASTR,        KC_PLUS,        KC_PERC,        KC_TRANSPARENT,                                              KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
                                                                                      KC_TRANSPARENT, KC_TRANSPARENT,              KC_TRANSPARENT, KC_TRANSPARENT
    ),
    [3] = LAYOUT(
      KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                               KC_DLR,         KC_7,           KC_8,           KC_9,           KC_ASTR,        KC_SLASH,
      KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                               KC_TRANSPARENT, KC_4,           KC_5,           KC_6,           KC_EQUAL,       KC_PERC,
      KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                               KC_0,           KC_1,           KC_2,           KC_3,           KC_PLUS,        KC_TRANSPARENT,
      TO(0),          KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                               KC_TRANSPARENT, KC_BSPC,        KC_COMMA,       KC_DOT,         KC_MINUS,       QK_LLCK,
                                                                                      KC_TRANSPARENT, KC_TRANSPARENT,        TO(0), KC_TRANSPARENT
    ),
    [4] = LAYOUT(
      KC_TRANSPARENT, KC_F1,          KC_F2,          KC_F3,          KC_F4,          KC_F5,                                          RGB_TOG,        TOGGLE_LAYER_COLOR, RGB_MODE_FORWARD, RGB_MODE_REVERSE,     RGB_VAD,        RGB_VAI,
      KC_TRANSPARENT, KC_F6,          KC_F7,          KC_F8,          KC_F9,          KC_F10,                                         KC_TRANSPARENT, KC_TRANSPARENT,     KC_TRANSPARENT,   KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
      KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_F11,         KC_F12,         KC_F13,                                         KC_TRANSPARENT, KC_TRANSPARENT,     KC_TRANSPARENT,   KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
      TO(0),          KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                 RM_HUEU,        RM_HUED,            KC_TRANSPARENT,  KC_TRANSPARENT, KC_TRANSPARENT, QK_BOOT,
                                                                                      KC_TRANSPARENT, TO(0),          KC_TRANSPARENT, KC_TRANSPARENT
    ),
    [5] = LAYOUT(
      KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                    LALT(KC_LEFT),  LALT(KC_DOWN),  LALT(KC_UP),    LALT(KC_RIGHT), KC_TRANSPARENT, KC_TRANSPARENT,
      KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                    KC_LEFT,        KC_DOWN,        KC_UP,          KC_RIGHT,       KC_TRANSPARENT, KC_TRANSPARENT,
      KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                    LGUI(KC_LEFT),  LGUI(KC_DOWN),  LGUI(KC_UP),    LGUI(KC_RIGHT), KC_TRANSPARENT, KC_TRANSPARENT,
      KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
                                                                                      KC_TRANSPARENT, KC_TRANSPARENT,    KC_TRANSPARENT, KC_TRANSPARENT
    ),
    [6] = LAYOUT(
      KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                     KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
      KC_TRANSPARENT, SEL_WORD,       BACKTICKS,      SQUOTES,        QUOTES,         KC_TRANSPARENT,                                     KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
      KC_TRANSPARENT, SEL_LINE,       SUBTRACTED,     ASSIGNMENT,     KC_TRANSPARENT, KC_TRANSPARENT,                                     KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
      KC_TRANSPARENT, KC_TRANSPARENT, MULTIPIED,      ADDED,          KC_TRANSPARENT, KC_TRANSPARENT,                                     KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
                                                                                      KC_TRANSPARENT, KC_TRANSPARENT,     KC_TRANSPARENT, KC_TRANSPARENT
    )
  };


/* Return an integer that corresponds to what kind of tap dance should be executed.
 *
 * How to figure out tap dance state: interrupted and pressed.
 *
 * Interrupted: If the state of a dance is "interrupted", that means that another key has been hit
 *  under the tapping term. This is typically indicative that you are trying to "tap" the key.
 *
 * Pressed: Whether or not the key is still being pressed. If this value is true, that means the tapping term
 *  has ended, but the key is still being pressed down. This generally means the key is being "held".
 *
 * One thing that is currently not possible with qmk software in regards to tap dance is to mimic the "permissive hold"
 *  feature. In general, advanced tap dances do not work well if they are used with commonly typed letters.
 *  For example "A". Tap dances are best used on non-letter keys that are not hit while typing letters.
 */
 td_state_t cur_dance(tap_dance_state_t *state) {
    if (state->count == 1) {
        if (state->interrupted || !state->pressed) return TD_SINGLE_TAP;
        // Key has not been interrupted, but the key is still held. Means you want to send a 'HOLD'.
        else return TD_SINGLE_HOLD;
    } else if (state->count == 2) {
        if (state->interrupted || state->pressed) return TD_DOUBLE_HOLD;
        else return TD_DOUBLE_TAP;
    } else return TD_UNKNOWN;
}

static td_tap_t cwl_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

void cwl_finished(tap_dance_state_t *state, void *user_data) {
    cwl_tap_state.state = cur_dance(state);
    switch (cwl_tap_state.state) {
        case TD_SINGLE_TAP: register_code(KC_LSFT); break;
        case TD_SINGLE_HOLD: register_code(KC_LSFT); break;

        case TD_DOUBLE_TAP:
        case TD_DOUBLE_HOLD: register_code(KC_CAPS); break;
        default: break;
    }
}

void cwl_reset(tap_dance_state_t *state, void *user_data) {
    switch (cwl_tap_state.state) {
        case TD_SINGLE_TAP: caps_word_toggle(); unregister_code(KC_LSFT); break;
        case TD_SINGLE_HOLD: unregister_code(KC_LSFT); break;
        // this unregistering is making caps lock not work,
        // and there seems to be no issue just keeping it registered
        // case TD_DOUBLE_TAP: unregister_code(KC_CAPS); break;
        case TD_DOUBLE_HOLD: unregister_code(KC_CAPS); break;
        default: break;
    }
    cwl_tap_state.state = TD_NONE;
}

void tap_dance_tap_hold_finished(tap_dance_state_t *state, void *user_data) {
    tap_dance_tap_hold_t *tap_hold = (tap_dance_tap_hold_t *)user_data;

    if (state->pressed) {
        if (state->count == 1
#ifndef PERMISSIVE_HOLD
            && !state->interrupted
#endif
        ) {
            register_code16(tap_hold->hold);
            tap_hold->held = tap_hold->hold;
        } else {
            register_code16(tap_hold->tap);
            tap_hold->held = tap_hold->tap;
        }
    }
}

void tap_dance_tap_hold_reset(tap_dance_state_t *state, void *user_data) {
    tap_dance_tap_hold_t *tap_hold = (tap_dance_tap_hold_t *)user_data;

    if (tap_hold->held) {
        unregister_code16(tap_hold->held);
        tap_hold->held = 0;
    }
}

#define ACTION_TAP_DANCE_TAP_HOLD(tap, hold) \
    { .fn = {NULL, tap_dance_tap_hold_finished, tap_dance_tap_hold_reset}, .user_data = (void *)&((tap_dance_tap_hold_t){tap, hold, 0}), }

tap_dance_action_t tap_dance_actions[] = {
    [OPT_CMD_BSPC] = ACTION_TAP_DANCE_TAP_HOLD(LALT(KC_BSPC), LGUI(KC_BSPC)),
    [ALFRED_SPOTLIGHT] = ACTION_TAP_DANCE_TAP_HOLD(LGUI(KC_SPACE), LALT(KC_SPACE)),
    [EXP_COLEMAK] = ACTION_TAP_DANCE_LAYER_TOGGLE(LALT(KC_6), 1),
    [CAPS_LOCK_WORD] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, cwl_finished, cwl_reset)
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        // macros
    case QUOTES:
        if (record->event.pressed) {
            SEND_STRING(SS_LSFT(SS_TAP(X_QUOTE)) SS_DELAY(10) SS_LSFT(SS_TAP(X_QUOTE)) SS_DELAY(10) SS_TAP(X_LEFT));
        }
        break;
    case SQUOTES:
        if (record->event.pressed) {
            SEND_STRING(SS_TAP(X_QUOTE) SS_DELAY(10) SS_TAP(X_QUOTE) SS_DELAY(10) SS_TAP(X_LEFT));
        }
        break;
    case BACKTICKS:
        if (record->event.pressed) {
            SEND_STRING(SS_TAP(X_GRAVE) SS_DELAY(10) SS_TAP(X_GRAVE) SS_DELAY(10) SS_TAP(X_LEFT));
        }
        break;
    case ADDED:
        if (record->event.pressed) {
            SEND_STRING(SS_TAP(X_SPACE) SS_DELAY(10) SS_TAP(X_KP_PLUS) SS_DELAY(10) SS_TAP(X_SPACE));
        }
        break;
    case ASSIGNMENT:
        if (record->event.pressed) {
            SEND_STRING(SS_TAP(X_SPACE) SS_DELAY(10) SS_TAP(X_EQUAL) SS_DELAY(10) SS_TAP(X_SPACE));
        }
        break;
    case SUBTRACTED:
        if (record->event.pressed) {
            SEND_STRING(SS_TAP(X_SPACE) SS_DELAY(10) SS_TAP(X_MINUS) SS_DELAY(10) SS_TAP(X_SPACE));
        }
        break;
    case MULTIPIED:
        if (record->event.pressed) {
            SEND_STRING(SS_TAP(X_SPACE) SS_DELAY(10) SS_LSFT(SS_TAP(X_KP_ASTERISK)) SS_DELAY(10) SS_TAP(X_SPACE));
        }
        break;
    case SEL_LINE:
        if (record->event.pressed) {
            SEND_STRING(SS_LGUI(SS_TAP(X_LEFT)) SS_DELAY(10) SS_LGUI(SS_LSFT(SS_TAP(X_RIGHT))));
        }
        break;
    case SEL_WORD:
        if (record->event.pressed) {
            SEND_STRING(SS_LALT(SS_TAP(X_LEFT)) SS_DELAY(10) SS_LALT(SS_LSFT(SS_TAP(X_RIGHT))));
        }
        break;

        // tap dance
        // list all tap dance keycodes with tap-hold configurations
        case TD(ALFRED_SPOTLIGHT):
        case TD(OPT_CMD_BSPC):
        action = &tap_dance_actions[QK_TAP_DANCE_GET_INDEX(keycode)];
        if (!record->event.pressed && action->state.count && !action->state.finished) {
            tap_dance_tap_hold_t *tap_hold = (tap_dance_tap_hold_t *)action->user_data;
            tap_code16(tap_hold->tap);
        }
        break;


        case LT(3, OPT_BSPC):
        if (!record->event.pressed && record->tap.count && !record->tap.interrupted) {
            tap_code16(LALT(KC_BSPC));
            layer_off(3);
            return false;
        }
        return true;
        break;

        case LT(4, CMD_BSPC):
        if (!record->event.pressed && record->tap.count && !record->tap.interrupted) {
            tap_code16(LGUI(KC_BSPC));
            layer_off(4);
            return false;
        }
        return true;
        break;
    }
    return true;
};


uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case LCTL_A:
        case LALT_S:
        case LGUI_D:
        case LSFT_F:
        case RSFT_J:
        case RGUI_K:
        case RALT_L:
        case RCTL_SCLN:
            return 130;
            break;

        default:
            return TAPPING_TERM;
    }
}


const char chordal_hold_layout[MATRIX_ROWS][MATRIX_COLS] PROGMEM =
    LAYOUT(
        'L', 'L', 'L', 'L', 'L', 'L',           'R', 'R', 'R', 'R', 'R', 'R',
        'L', 'L', 'L', 'L', 'L', 'L',           'R', 'R', 'R', 'R', 'R', 'R',
        'L', 'L', 'L', 'L', 'L', 'L',           'R', 'R', 'R', 'R', 'R', 'R',
        'L', 'L', 'L', 'L', 'L', 'L',           'R', 'R', 'R', 'R', 'R', 'R',
                            'L', 'L',             'R', 'R'
    );
