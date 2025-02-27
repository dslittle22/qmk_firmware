// Copyright 2023 ZSA Technology Labs, Inc <@zsa>
// Copyright 2023 Christopher Courtney, aka Drashna Jael're  (@drashna) <drashna@live.com>
// SPDX-License-Identifier: GPL-2.0-or-later


#include QMK_KEYBOARD_H
#include "process_tap_dance.h"

enum custom_keycodes {
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


typedef struct {
    uint16_t tap;
    uint16_t hold;
    uint16_t held;
} tap_dance_tap_hold_t;
tap_dance_action_t *action;

enum tap_dance_codes {
    OPT_CMD_BSPC,
    ALFRED_SPOTLIGHT,
    EXP_COLEMAK,
    EXP_QWERTY,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
      MEH_T(KC_TAB),  KC_Q,           KC_W,           KC_E,           KC_R,           KC_T,                                           KC_Y,           KC_U,           KC_I,           KC_O,           KC_P,           ALL_T(KC_BSLS),
      LT(6,KC_ESCAPE),MT(MOD_LCTL, KC_A),MT(MOD_LALT, KC_S),MT(MOD_LGUI, KC_D),MT(MOD_LSFT, KC_F),KC_G,                                           KC_H,           MT(MOD_RSFT, KC_J),MT(MOD_RGUI, KC_K),MT(MOD_RALT, KC_L),MT(MOD_RCTL, KC_SCLN),KC_QUOTE,
      CW_TOGG,        KC_Z,           KC_X,           KC_C,           KC_V,           KC_B,                                           KC_N,           KC_M,           KC_COMMA,       KC_DOT,         KC_SLASH,       OSM(MOD_LSFT),
      TD(ALFRED_SPOTLIGHT),    KC_HOME,        KC_PAGE_UP,     KC_PGDN,        KC_END,         LT(2,KC_BSPC),                                  LT(2,KC_SPACE), KC_LEFT,        KC_DOWN,        KC_UP,          KC_RIGHT,       TD(EXP_COLEMAK),
                                                      TD(OPT_CMD_BSPC),    LT(3,KC_TAB),                                   LT(4,KC_GRAVE), LT(3,KC_ENTER)
    ),
    [1] = LAYOUT(
      LT(7,KC_TAB),   KC_Q,           KC_W,           KC_F,           KC_P,           KC_B,                                           KC_J,           KC_L,           KC_U,           KC_Y,           KC_SCLN,        KC_TRANSPARENT,
      KC_TRANSPARENT, MT(MOD_LCTL, KC_A),MT(MOD_LALT, KC_R),MT(MOD_LGUI, KC_S),MT(MOD_LSFT, KC_T),KC_G,                                           KC_M,           MT(MOD_LSFT, KC_N),MT(MOD_LGUI, KC_E),MT(MOD_LALT, KC_I),MT(MOD_LCTL, KC_O),KC_TRANSPARENT,
      KC_TRANSPARENT, KC_Z,           KC_X,           KC_C,           KC_D,           KC_V,                                           KC_K,           KC_H,           KC_COMMA,       KC_DOT,         KC_SLASH,       KC_TRANSPARENT,
      KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
                                                      KC_TRANSPARENT, KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_TRANSPARENT
    ),
    [2] = LAYOUT(
      KC_HASH,        KC_AT,          KC_AMPR,        KC_PIPE,        KC_UNDS,        KC_QUES,                                        KC_TRANSPARENT, KC_LCBR,        KC_RCBR,        KC_GRAVE,       KC_TRANSPARENT, KC_TRANSPARENT,
      KC_CIRC,        KC_EXLM,        KC_GRAVE,       KC_QUOTE,       KC_DQUO,        KC_DLR,                                         KC_TRANSPARENT, KC_LPRN,        KC_RPRN,        KC_QUOTE,       OSL(6),         KC_TRANSPARENT,
      KC_HASH,        KC_LABK,        KC_MINUS,       KC_EQUAL,       KC_RABK,        KC_QUES,                                        KC_TRANSPARENT, KC_LBRC,        KC_RBRC,        KC_DQUO,        KC_TRANSPARENT, KC_TRANSPARENT,
      KC_TILD,        KC_SLASH,       KC_ASTR,        KC_PLUS,        KC_PERC,        KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
                                                      KC_TRANSPARENT, KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_TRANSPARENT
    ),
    [3] = LAYOUT(
      KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                 KC_DLR,         KC_7,           KC_8,           KC_9,           KC_ASTR,        KC_SLASH,
      KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_4,           KC_5,           KC_6,           KC_EQUAL,       KC_PERC,
      KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                 KC_0,           KC_1,           KC_2,           KC_3,           KC_PLUS,        KC_TRANSPARENT,
      TO(0),          KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_BSPC,        KC_COMMA,       KC_DOT,         KC_MINUS,       QK_LLCK,
                                                      KC_TRANSPARENT, KC_TRANSPARENT,                                 TO(0),          KC_TRANSPARENT
    ),
    [4] = LAYOUT(
      KC_TRANSPARENT, KC_F1,          KC_F2,          KC_F3,          KC_F4,          KC_F5,                                          RGB_TOG,        TOGGLE_LAYER_COLOR, RGB_MODE_FORWARD, RGB_MODE_REVERSE,     RGB_VAD,        RGB_VAI,
      KC_TRANSPARENT, KC_F6,          KC_F7,          KC_F8,          KC_F9,          KC_F10,                                         KC_TRANSPARENT, KC_TRANSPARENT,     KC_TRANSPARENT,   KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
      KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_F11,         KC_F12,         KC_F13,                                         KC_TRANSPARENT, KC_TRANSPARENT,     KC_TRANSPARENT,   KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
      TO(0),          KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                 RM_HUEU,        RM_HUED,            KC_TRANSPARENT,  KC_TRANSPARENT, KC_TRANSPARENT, QK_BOOT,
                                                      KC_TRANSPARENT, TO(0),                                          KC_TRANSPARENT, KC_TRANSPARENT
    ),
    [5] = LAYOUT(
      KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                 LALT(KC_LEFT),  LALT(KC_DOWN),  LALT(KC_UP),    LALT(KC_RIGHT), KC_TRANSPARENT, KC_TRANSPARENT,
      KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                 KC_LEFT,        KC_DOWN,        KC_UP,          KC_RIGHT,       KC_TRANSPARENT, KC_TRANSPARENT,
      KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                 LGUI(KC_LEFT),  LGUI(KC_DOWN),  LGUI(KC_UP),    LGUI(KC_RIGHT), KC_TRANSPARENT, KC_TRANSPARENT,
      KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
                                                      KC_TRANSPARENT, KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_TRANSPARENT
    ),
    [6] = LAYOUT(
      KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
      KC_TRANSPARENT, SEL_WORD,       BACKTICKS,      SQUOTES,        QUOTES,         KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
      KC_TRANSPARENT, SEL_LINE,       SUBTRACTED,     ASSIGNMENT,     KC_TRANSPARENT, KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
      KC_TRANSPARENT, KC_TRANSPARENT, MULTIPIED,      ADDED,          KC_TRANSPARENT, KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
                                                      KC_TRANSPARENT, KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_TRANSPARENT
    )
  };


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

    }
    return true;
};
