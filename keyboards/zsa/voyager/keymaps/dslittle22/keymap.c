// Copyright 2023 ZSA Technology Labs, Inc <@zsa>
// Copyright 2023 Christopher Courtney, aka Drashna Jael're  (@drashna) <drashna@live.com>
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include "process_tap_dance.h"
#include "process_combo.h"
// #include "process_key_override.h"


#define LCTL_A MT(MOD_LCTL, KC_A)
#define LALT_S MT(MOD_LALT, KC_S)
#define LGUI_D MT(MOD_LGUI, KC_D)
#define LSFT_F MT(MOD_LSFT, KC_F)
#define RSFT_J MT(MOD_RSFT, KC_J)
#define RGUI_K MT(MOD_RGUI, KC_K)
#define RALT_L MT(MOD_RALT, KC_L)
#define RCTL_SCLN MT(MOD_RCTL, KC_SCLN)

// add these for the colemak layout
#define LALT_R MT(MOD_LALT, KC_R)
#define LGUI_S MT(MOD_LGUI, KC_S)
#define LSFT_T_ MT(MOD_LSFT, KC_T)
#define RSFT_N MT(MOD_RSFT, KC_N)
#define RGUI_E MT(MOD_RGUI, KC_E)
#define RALT_I MT(MOD_RALT, KC_I)
#define RCTL_O MT(MOD_RCTL, KC_O)

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
    SEMI_COLON_SWAP,
    ALT_6,
    TILDE,
    ATAT
};


enum tap_dance_codes {
    OPT_CMD_BSPC,
    ALFRED_SPOTLIGHT,
    EXP_COLEMAK,
    CAPS_LOCK_WORD
};


// const key_override_t semi_to_colon_override = {
//     .trigger_mods          = 0, // no mods need to be held to activate
//     .trigger               = KC_SCLN,
//     .replacement           = KC_COLON,
//     .layers                = ~0,      // active on all layers
//     .negative_mod_mask     = MOD_MASK_CSAG, // Only trigger if no mods are active
//     .suppressed_mods       = 0, // no mods should be held down, so we don't need to suppress any
//     .options               = ko_options_default
// };


// const key_override_t colon_to_semi_override = {
//     .trigger_mods          = MOD_MASK_SHIFT, // left or right shift
//     .trigger               = KC_SCLN,
//     .replacement           = KC_A,
//     .layers                = ~0,      // active on all layers
//     .negative_mod_mask     = 0, // MOD_MASK_CAG, // Only trigger if no mods are active
//     .suppressed_mods       = 0,// MOD_MASK_SHIFT, // no mods should be held down, so we don't need to suppress any
//     .options               = ko_options_default
// };


// const key_override_t *key_overrides[] = {
	// &semi_to_colon_override,
    // &colon_to_semi_override,
// };

const uint16_t PROGMEM alfred_combo_1[] = {LSFT_F, KC_C, COMBO_END};
const uint16_t PROGMEM alfred_combo_2[] = {RSFT_J, KC_COMMA, COMBO_END};

const uint16_t PROGMEM colemak_alfred_combo_1[] = {KC_X, KC_C, COMBO_END};
const uint16_t PROGMEM colemak_alfred_combo_2[] = {KC_DOT, KC_COMMA, COMBO_END};

const uint16_t PROGMEM colemak_combo[] = {KC_UP, KC_RIGHT, COMBO_END};


combo_t key_combos[] = {
    COMBO(alfred_combo_1, LGUI(KC_SPACE)),
    COMBO(alfred_combo_2, LGUI(KC_SPACE)),
    COMBO(colemak_alfred_combo_1, LGUI(KC_SPACE)),
    COMBO(colemak_alfred_combo_2, LGUI(KC_SPACE)),
    COMBO(colemak_combo, TG(1)),
};

typedef enum {
    TD_NONE,
    TD_UNKNOWN,
    TD_SINGLE_TAP,
    TD_SINGLE_TAP_INTERRUPTED,
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

int colemak_when_tab_pressed = 0;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
      MEH_T(KC_TAB),        KC_Q,     KC_W,    KC_E,   KC_R,      KC_T,                                                            KC_Y,           KC_U,    KC_I,      KC_O,    KC_P,       ALL_T(KC_BSLS),
      LT(6,KC_ESCAPE),      LCTL_A,   LALT_S,  LGUI_D, LSFT_F,    KC_G,                                                            KC_H,           RSFT_J,  RGUI_K,    RALT_L,  RCTL_SCLN,  KC_QUOTE,
      TD(CAPS_LOCK_WORD),   KC_Z,     KC_X,    KC_C,   KC_V,      KC_B,                                                            KC_N,           KC_M,    KC_COMMA,  KC_DOT,  KC_SLASH,   OSM(MOD_LSFT),
      TD(ALFRED_SPOTLIGHT), KC_PGUP,  KC_PGDN, KC_TAB, KC_GRAVE,  LT(2,KC_BSPC),                                                   LT(2,KC_SPACE), KC_LEFT, KC_DOWN,   KC_UP,   KC_RIGHT,   ATAT,
                                                                                      LT(3, OPT_BSPC),  LT(4, CMD_BSPC),       LT(3,KC_GRAVE), LT(4,KC_ENTER)
    ),
    [1] = LAYOUT(
      _______, KC_Q,    KC_W,    KC_F,    KC_P,    KC_B,                                     KC_J,    KC_L,    KC_U,     KC_Y,     SEMI_COLON_SWAP,  _______,
      _______, LCTL_A,  LALT_R,  LGUI_S,  LSFT_T_, KC_G,                                     KC_M,    RSFT_N,  RGUI_E,   RALT_I,   RCTL_O,           _______,
      _______, KC_Z,    KC_X,    KC_C,    KC_D,    KC_V,                                     KC_K,    KC_H,    KC_COMMA, KC_DOT,   KC_SLASH,         _______,
      _______, _______, _______, _______, _______, _______,                                  _______, _______, _______,  _______,  _______,          _______,
                                                                       _______, _______,        _______, _______
    ),
    [2] = LAYOUT(
      KC_HASH,        KC_AT,          KC_AMPR,        KC_PIPE,        KC_UNDS,        KC_QUES,                                        _______, KC_LCBR, KC_RCBR, KC_GRAVE, _______, _______,
      KC_CIRC,        KC_EXLM,        KC_GRAVE,       KC_QUOTE,       KC_DQUO,        KC_DLR,                                         _______, KC_LPRN, KC_RPRN, KC_QUOTE, OSL(6), _______,
      KC_HASH,        KC_LABK,        KC_MINUS,       KC_EQUAL,       KC_RABK,        KC_QUES,                                        _______, KC_LBRC, KC_RBRC, KC_DQUO, _______, _______,
      TILDE,         KC_SLASH,         KC_ASTR,       KC_PLUS,        KC_PERC,        _______,                                        _______, _______, _______, _______, _______, _______,
                                                                                                          _______, _______,              _______, _______
    ),
    [3] = LAYOUT(
      _______, _______, _______, _______, _______, _______,                               KC_DLR,  KC_7,           KC_8,           KC_9,           KC_ASTR,        KC_SLASH,
      _______, _______, _______, _______, _______, _______,                               _______, KC_4,           KC_5,           KC_6,           KC_EQUAL,       KC_PERC,
      _______, _______, _______, _______, _______, _______,                               KC_0,    KC_1,           KC_2,           KC_3,           KC_PLUS,        _______,
      _______, _______, _______, _______, _______, _______,                               _______, KC_BSPC,        KC_COMMA,       KC_DOT,         KC_MINUS,       QK_LAYER_LOCK,
                                                                                      _______, _______,        TO(0), _______
    ),
    [4] = LAYOUT(
      _______, KC_F1,          KC_F2,          KC_F3,          KC_F4,          KC_F5,                                          RGB_TOG,        TOGGLE_LAYER_COLOR, RGB_MODE_FORWARD, RGB_MODE_REVERSE,     RGB_VAD,  RGB_VAI,
      _______, KC_F6,          KC_F7,          KC_F8,          KC_F9,          KC_F10,                                         _______, _______,     _______,   _______, _______, _______,
      _______, _______, _______, KC_F11,         KC_F12,         KC_F13,                                         _______, _______,     _______,   _______, _______, DB_TOGG,
      QK_BOOT,          _______, _______, _______, _______, _______,                                 RM_HUEU,        RM_HUED,            _______,  _______, _______,  QK_LAYER_LOCK,
                                                                                      _______, TO(0),                   TO(0), _______
    ),
    [5] = LAYOUT(
      _______, _______, _______, _______, _______, _______,                                    LALT(KC_LEFT),  LALT(KC_DOWN),  LALT(KC_UP),    LALT(KC_RIGHT), _______, _______,
      _______, _______, _______, _______, _______, _______,                                    KC_LEFT,        KC_DOWN,        KC_UP,          KC_RIGHT,       _______, _______,
      _______, _______, _______, _______, _______, _______,                                    LGUI(KC_LEFT),  LGUI(KC_DOWN),  LGUI(KC_UP),    LGUI(KC_RIGHT), _______, _______,
      _______, _______, _______, _______, _______, _______,                                    _______, _______, _______, _______, _______, _______,
                                                                                      _______, _______,    _______, _______
    ),
    [6] = LAYOUT(
      _______, _______, _______, _______, _______, _______,                                     _______, _______, _______, _______, _______, _______,
      _______, SEL_WORD,       BACKTICKS,      SQUOTES,        QUOTES,         _______,                                     _______, _______, _______, _______, _______, _______,
      _______, SEL_LINE,       SUBTRACTED,     ASSIGNMENT,     _______, _______,                                     _______, _______, _______, _______, _______, _______,
      _______, _______, MULTIPIED,      ADDED,          _______, _______,                                     _______, _______, _______, _______, _______, _______,
                                                                                      _______, _______,     _______, _______
    ),
    // regular qwerty layer
    [7] = LAYOUT(
        _______, KC_Q,           KC_W,           KC_E,           KC_R,           KC_T,                                              KC_Y,      KC_U,    KC_I,     KC_O,     KC_P,     KC_BSLS,
        _______, KC_A,           KC_S,           KC_D,           KC_F,           KC_G,                                              KC_H,      KC_J,    KC_K,     KC_L,     KC_SCLN,  KC_QUOTE,
        _______, KC_Z,           KC_X,           KC_C,           KC_V,           KC_B,                                              KC_N,      KC_M,    KC_COMMA, KC_DOT,   KC_SLASH, _______,
        _______, _______, _______, _______, _______, _______,                                    _______, _______, _______, _______, _______,
                                                                                                            _______, _______,     TO(0), _______,
      ),
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
        // if (state->interrupted || !state->pressed) return TD_SINGLE_TAP;
        if (state->interrupted) return TD_SINGLE_TAP_INTERRUPTED;
        else if (!state->pressed) return TD_SINGLE_TAP;

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
        case TD_SINGLE_TAP:
        case TD_SINGLE_TAP_INTERRUPTED: register_code(KC_LSFT); break;
        case TD_SINGLE_HOLD: register_code(KC_LSFT); break;

        case TD_DOUBLE_TAP:
        case TD_DOUBLE_HOLD: register_code(KC_CAPS); break;
        default: break;
    }
}

void cwl_reset(tap_dance_state_t *state, void *user_data) {
    switch (cwl_tap_state.state) {
        case TD_SINGLE_TAP_INTERRUPTED: unregister_code(KC_LSFT); break;
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

// run after tap dance finishes, which means either:
// 1) the key was pressed and held, and the tapping term expired, or
// 2) the tap dance key was pressed and then interrupted
void tap_dance_tap_hold_finished(tap_dance_state_t *state, void *user_data) {
    tap_dance_tap_hold_t *tap_hold = (tap_dance_tap_hold_t *)user_data;
    dprint("tap_dance_tap_hold_finished\n");
    dprintf("state->count: %d\n", state->count);
    dprintf("state->pressed: %d\n", state->pressed);
    dprintf("state->interrupted: %d\n", state->interrupted);
    dprintf("\n");

    // so if the key was pressed and held, and the tapping term expired,
    // then register a hold
    if (state->pressed) {
        if (state->count == 1
            // in my case I have permissive hold enabled,
            // so we will send the hold if interrupted
#ifndef PERMISSIVE_HOLD
            && !state->interrupted
#endif
        ) {
            register_code16(tap_hold->hold);
            tap_hold->held = tap_hold->hold;
        } else {
            // otherwise the tap dance key was interrupted- send the tap
            register_code16(tap_hold->tap);
            tap_hold->held = tap_hold->tap;
        }
    }
}

// this when the tap dance is "fully" over. Usually it runs immediately after
// tap_dance_tap_hold_finished, but if the key is held, then
// tap_dance_tap_hold_finished runs after tapping term expires, and
// this runs when the key is released.

// its only job is to release whatever key was registered.
void tap_dance_tap_hold_reset(tap_dance_state_t *state, void *user_data) {
    tap_dance_tap_hold_t *tap_hold = (tap_dance_tap_hold_t *)user_data;

    dprint("tap_dance_tap_hold_reset\n");
    dprintf("state->count: %d\n", state->count);
    dprintf("state->pressed: %d\n", state->pressed);
    dprintf("state->interrupted: %d\n", state->interrupted);
    dprintf("\n");

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
    [CAPS_LOCK_WORD] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, cwl_finished, cwl_reset),
    // [EXP_COLEMAK] = ACTION_TAP_DANCE_LAYER_TOGGLE(LALT(KC_6), 1),
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    dprintf("keycode: %d\n", keycode);
    dprintf("count: %d\n", record->tap.count);
    dprintf("interrupted: %d\n", record->tap.interrupted);
    dprintf("event.pressed: %d\n", record->event.pressed);
    dprintf("\n");

    switch (keycode) {
        case ATAT:
            if (record->event.pressed) {
                tap_code16(KC_AT);
                tap_code16(KC_AT);
                return false;
            }
            break;
        case TILDE:
            if (record->event.pressed) {
                tap_code16(LSFT(KC_GRAVE));
                return false;
            }
            break;
        case ALT_6:
            if (record->event.pressed) {
                tap_code16(LALT(KC_6));
                return false;
            }
            break;
        case SEMI_COLON_SWAP:
        if (record->event.pressed) {
            uint8_t mods = get_mods();
            if (mods == 0) {
                // send colon on tap with no mods
            tap_code16(KC_COLON);
            return false;
            }
            else if (mods == MOD_BIT_LSHIFT || mods == MOD_BIT_RSHIFT) {
                unregister_mods(mods);
                tap_code(KC_SEMICOLON);
                register_mods(mods);
                return false;
            }
        }
        break;

        case MEH_T(KC_TAB):
            if (record->event.pressed) {
                colemak_when_tab_pressed = layer_state_is(1);
                if (!colemak_when_tab_pressed) {
                    break;
                }

                layer_off(1);
            } else {
                if (colemak_when_tab_pressed) {
                    layer_on(1);
                }
            }

        break;

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
            // this is intercepting on release of >=1 press, and the tap dance
            // is not already finished (e.g. not interrupted, maybe?)
            action = &tap_dance_actions[QK_TAP_DANCE_GET_INDEX(keycode)];
            if (!record->event.pressed && action->state.count && !action->state.finished) {
                tap_dance_tap_hold_t *tap_hold = (tap_dance_tap_hold_t *)action->user_data;
                // send a tap on release
                tap_code16(tap_hold->tap);
                // don't return false, the tap dance cleanup functions won't do anything here
            }
            break;


        case LT(3, OPT_BSPC):
            if (!record->event.pressed && record->tap.count && !record->tap.interrupted) {
                tap_code16(LALT(KC_BSPC));
                layer_off(3);
                return false;
            }
            break;

        case LT(4, CMD_BSPC):
            if (!record->event.pressed && record->tap.count && !record->tap.interrupted) {
                tap_code16(LGUI(KC_BSPC));
                layer_off(4);
                return false;
            }
            break;

        case RCTL_SCLN:
            if (record->tap.count && record->event.pressed) {
                uint8_t mods = get_mods();
                if (mods == 0) {
                    // send colon on tap with no mods
                tap_code16(KC_COLON);
                return false;
                }
                else if (mods == MOD_BIT_LSHIFT || mods == MOD_BIT_RSHIFT) {
                    unregister_mods(mods);
                    tap_code(KC_SEMICOLON);
                    register_mods(mods);
                    return false;
                }
            }
            break;
    }
    return true;
};

void keyboard_post_init_user(void) {
    layer_on(1);
}

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

        case LALT_R:
        case LGUI_S:
        case LSFT_T_:
        case RSFT_N:
        case RGUI_E:
        case RALT_I:
        case RCTL_O:
            return 150;
            break;

        default:
            return TAPPING_TERM;
    }
}


const char chordal_hold_layout[MATRIX_ROWS][MATRIX_COLS] PROGMEM =
    LAYOUT(
        '*', 'L', 'L', 'L', 'L', 'L',           'R', 'R', 'R', 'R', 'R', '*',
        'L', 'L', 'L', 'L', 'L', 'L',           'R', 'R', 'R', 'R', 'R', 'R',
        'L', 'L', 'L', 'L', 'L', 'L',           'R', 'R', 'R', 'R', 'R', 'R',
        'L', 'L', 'L', 'L', 'L', 'L',           'R', 'R', 'R', 'R', 'R', 'R',
                            '*', '*',             '*', '*'
    );
