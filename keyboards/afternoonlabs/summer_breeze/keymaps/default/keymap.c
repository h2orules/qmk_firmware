/* Copyright 2021 Afternoon Labs
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
#include <stdio.h>
//#include <os_detection.h>

#include QMK_KEYBOARD_H

enum layer_names {
    _MAIN,
    _LOWER,
    _RAISE,
    _ADJUST,
    _NUMPAD,
};

#define LOWER MO(_LOWER)
#define RAISE MO(_RAISE)

// Super CMD+Tab.
// TODO: OS Detection to switch between ALT & CMD
bool is_alt_tab_active = false;
uint16_t alt_tab_timer = 0;

enum custom_keycodes {
    KC_QWERTY = SAFE_RANGE,
    KC_LOWER,
    KC_RAISE,
    KC_ADJUST,
    KC_LAYER,
    KC_BSPC_DEL,
    KC_CMTAB,
};

// Tap Dance declarations
typedef enum {
    TD_NONE,
    TD_UNKNOWN,
    TD_SINGLE_TAP,
    TD_SINGLE_HOLD,
    TD_DOUBLE_TAP,
    TD_DOUBLE_HOLD,
    TD_DOUBLE_SINGLE_TAP, // Send two single taps
    TD_TRIPLE_TAP,
    TD_TRIPLE_HOLD,
} td_state_t;

typedef struct {
    bool is_press_action;
    td_state_t state;
} td_tap_t;

// Tap dance enums
enum {
    TD_MEGA_SHIFT,
    TD_SHFT_CAPS,
};

td_state_t cur_dance(tap_dance_state_t *state);

// For the megashift tap dance. Forward decl so it can be used in any keymap
void megaShift_finished(tap_dance_state_t *state, void *user_data);
void megaShift_reset(tap_dance_state_t *state, void *user_data);

// Tap Dance definitions
tap_dance_action_t tap_dance_actions[] = {
    // Tap once for Escape, twice for Caps Lock
    [TD_SHFT_CAPS] = ACTION_TAP_DANCE_DOUBLE(KC_LSFT, KC_CAPS),
    [TD_MEGA_SHIFT] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, megaShift_finished, megaShift_reset)
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [_MAIN] = LAYOUT(
        //┌────────┬────────┬────────┐┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐┌────────┬────────┬────────┐
           KC_BSLS, KC_EQL,  KC_GRAVE, KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                               KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINUS,  KC_INS, KC_HOME,  KC_PGUP,
        //├────────┼────────┼────────┤├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤├────────┼────────┼────────┤
           KC_BSLS, KC_LBRC, KC_RBRC,  LT(_NUMPAD,KC_TAB), KC_Q, KC_W, KC_E, KC_R,  KC_T,                               KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC_DEL, KC_DEL, KC_END, KC_PGDN,
        //├────────┼────────┼────────┤├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤├────────┼────────┼────────┤
                    KC_LPAD,           KC_CMTAB, KC_A,   KC_S,    KC_D,    KC_F,    KC_G,                               KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,           KC_UP,
        //├────────┼────────┼────────┤├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤├────────┼────────┼────────┤
           DM_PLY1, DM_PLY2, KC_MCTL,  TD(TD_MEGA_SHIFT), KC_Z, KC_X, KC_C, KC_V,   KC_B,                               KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, SC_RSPC,  KC_LEFT, KC_DOWN, KC_RIGHT,
        //└────────┴────────┴────────┘└────────┴────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┴────────┴────────┴────────┘└────────┴────────┴────────┘
                                                                  KC_LCTL, KC_LOWER, KC_LGUI, KC_ENT,         KC_SPC,   KC_RGUI, KC_RAISE, KC_RALT
        //                                                       └────────┴────────┴────────┴────────┘        └────────┴────────┴────────┴────────┘
    ),

    [_LOWER] = LAYOUT(
        //┌────────┬────────┬────────┐┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐┌────────┬────────┬────────┐
           _______, _______, _______,  KC_GRV,   KC_F1,  KC_F2,   KC_F3,   KC_F4,   KC_F5,                              KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10,  KC_EQUAL,  KC_MUTE, KC_VOLD, KC_VOLU,
        //├────────┼────────┼────────┤├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤├────────┼────────┼────────┤
           _______, _______, _______,  _______, XXXXXXX, LCA_T(KC_NO), LSA_T(KC_NO), LSG_T(KC_NO), XXXXXXX,             KC_PGUP, G(KC_LEFT), KC_UP, G(KC_RIGHT), KC_LBRC, KC_RBRC, KC_MPRV, KC_MPLY, KC_MNXT,
        //├────────┼────────┼────────┤├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤├────────┼────────┼────────┤
                    _______,           _______, KC_LCTL, KC_LALT, KC_LSFT, KC_LGUI, XXXXXXX,                            KC_PGDN,  KC_LEFT, KC_DOWN, KC_RGHT, KC_LCBR, KC_RCBR,          KC_BRIU,
        //├────────┼────────┼────────┤├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤├────────┼────────┼────────┤
           DM_REC1, DM_REC2, DM_RSTP,  _______, C(KC_Z), C(KC_X), C(KC_C), C(KC_V), XXXXXXX,                            XXXXXXX, A(KC_LEFT), XXXXXXX, A(KC_RGHT), KC_BSLS, XXXXXXX,  XXXXXXX, KC_BRID, XXXXXXX,
        //└────────┴────────┴────────┘└────────┴────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┴────────┴────────┴────────┘└────────┴────────┴────────┘
                                                                  _______, _______, _______, _______,          _______, _______, _______, _______
        //                                                       └────────┴────────┴────────┴────────┘        └────────┴────────┴────────┴────────┘
    ),

    [_RAISE] = LAYOUT(
        //┌────────┬────────┬────────┐┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐┌────────┬────────┬────────┐
           KC_BTN4, KC_WH_U, KC_BTN5,  _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                            C(A(KC_D)), C(A(KC_E)), C(A(KC_F)), C(A(KC_T)), C(A(KC_G)), XXXXXXX,          _______, _______, _______,
        //├────────┼────────┼────────┤├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤├────────┼────────┼────────┤
           KC_BTN1, KC_WH_D, KC_BTN2,  _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                            XXXXXXX, C(A(G(KC_LEFT))), C(A(KC_UP)), C(A(G(KC_RIGHT))), XXXXXXX, XXXXXXX,  _______, _______, _______,
        //├────────┼────────┼────────┤├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤├────────┼────────┼────────┤
                    KC_MS_U,           _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, G(KC_TAB),                          C(A(KC_ENT)), C(A(KC_LEFT)), C(A(KC_DOWN)), C(A(KC_RIGHT)), C(A(KC_DEL)), XXXXXXX,     _______,
        //├────────┼────────┼────────┤├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤├────────┼────────┼────────┤
           KC_MS_L, KC_MS_D, KC_MS_R,  _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, G(S(KC_TAB)),                       XXXXXXX, XXXXXXX, C(A(KC_C)), XXXXXXX, XXXXXXX, XXXXXXX,                      _______, _______, _______,
        //└────────┴────────┴────────┘└────────┴────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┴────────┴────────┴────────┘└────────┴────────┴────────┘
                                                                  _______, _______, _______, _______,          _______, _______, _______, _______
        //                                                       └────────┴────────┴────────┴────────┘        └────────┴────────┴────────┴────────┘
    ),

    [_ADJUST] = LAYOUT(
        //┌────────┬────────┬────────┐┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐┌────────┬────────┬────────┐
           _______, _______, _______,  QK_BOOT, QK_RBT,  QK_MAKE, _______, _______, _______,                            _______, _______, _______, _______, _______, _______,  _______, _______, _______,
        //├────────┼────────┼────────┤├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤├────────┼────────┼────────┤
           _______, KC_BTN3, _______,  EE_CLR,  _______, _______, _______, _______, _______,                            _______, _______, _______, _______, _______, _______,  _______, _______, _______,
        //├────────┼────────┼────────┤├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤├────────┼────────┼────────┤
                    _______,           _______, _______, _______, _______, _______, _______,                            _______, _______, _______, _______, _______, _______,           _______,
        //├────────┼────────┼────────┤├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤├────────┼────────┼────────┤
           _______, _______, _______,  _______, _______, _______, _______, _______, _______,                            _______, _______, _______, _______, _______, _______,  _______, _______, _______,
        //└────────┴────────┴────────┘└────────┴────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┴────────┴────────┴────────┘└────────┴────────┴────────┘
                                                                  _______, _______, _______, _______,          _______, _______, _______, _______
        //                                                       └────────┴────────┴────────┴────────┘        └────────┴────────┴────────┴────────┘
    ),

    [_NUMPAD] = LAYOUT(
        //┌────────┬────────┬────────┐┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐┌────────┬────────┬────────┐
           XXXXXXX, XXXXXXX, XXXXXXX,  _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                            KC_ESC,  KC_PEQL, KC_PSLS, KC_PAST, KC_PMNS, KC_LPRN,  _______, _______, _______,
        //├────────┼────────┼────────┤├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤├────────┼────────┼────────┤
           XXXXXXX, XXXXXXX, XXXXXXX,  _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                            KC_CIRC, KC_P7,   KC_P8,   KC_P9,   KC_PPLS, KC_RPRN,  _______, _______, _______,
        //├────────┼────────┼────────┤├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤├────────┼────────┼────────┤
                    XXXXXXX,           XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                            KC_PERC, KC_P4,   KC_P5,   KC_P6,   KC_EQL,  KC_BSPC,           _______,
        //├────────┼────────┼────────┤├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤├────────┼────────┼────────┤
           XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                            KC_PCMM, KC_P1,   KC_P2,   KC_P3,   KC_PENT, KC_ENT,   _______, _______, _______,
        //└────────┴────────┴────────┘└────────┴────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┴────────┴────────┴────────┘└────────┴────────┴────────┘
                                                                  XXXXXXX, XXXXXXX, _______, _______,          _______, _______, KC_P0,   KC_PDOT
        //                                                       └────────┴────────┴────────┴────────┘        └────────┴────────┴────────┴────────┘
    ),


};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    static uint8_t saved_mods = 0;

    switch (keycode) {
        case KC_LOWER:
            if (record->event.pressed) {
                layer_on(_LOWER);
                update_tri_layer(_LOWER, _RAISE, _ADJUST);
            } else {
                layer_off(_LOWER);
                update_tri_layer(_LOWER, _RAISE, _ADJUST);
            }
            return false;
        case KC_RAISE:
            if (record->event.pressed) {
                layer_on(_RAISE);
                update_tri_layer(_LOWER, _RAISE, _ADJUST);
            } else {
                layer_off(_RAISE);
                update_tri_layer(_LOWER, _RAISE, _ADJUST);
            }
            return false;
        case KC_ADJUST:
            if (record->event.pressed) {
                layer_on(_ADJUST);
            } else {
                layer_off(_ADJUST);
            }
            return false;

        /* Smart Backspace Delete */
        case KC_BSPC_DEL:
            if (record->event.pressed) {
                saved_mods = get_mods() & MOD_MASK_SHIFT;

                if (saved_mods == MOD_MASK_SHIFT) {  // Both shifts pressed
                    register_code(KC_DEL);
                } else if (saved_mods) {   // One shift pressed
                    del_mods(saved_mods);  // Remove any Shifts present
                    register_code(KC_DEL);
                    add_mods(saved_mods);  // Add shifts again
                } else {
                    register_code(KC_BSPC);
                }
            } else {
                unregister_code(KC_DEL);
                unregister_code(KC_BSPC);
            }
            return false;
        case KC_CMTAB:
            if (record->event.pressed) {
                if (!is_alt_tab_active) {
                is_alt_tab_active = true;
                register_code(KC_LGUI);
                }
                alt_tab_timer = timer_read();
                register_code(KC_TAB);
            } else {
                unregister_code(KC_TAB);
            }
            break;
    }
    return true;
}

void matrix_scan_user(void) { // The very important timer.
  if (is_alt_tab_active) {
    if (timer_elapsed(alt_tab_timer) > 1000) {
      unregister_code(KC_LGUI);
      is_alt_tab_active = false;
    }
  }
}

/* Return an integer that corresponds to what kind of tap dance should be executed.
 *
 * How to figure out tap dance state: interrupted and pressed.
 *
 * Interrupted: If the state of a dance is "interrupted", that means that another key has been hit
 *  under the tapping term. This is typically indicitive that you are trying to "tap" the key.
 *
 * Pressed: Whether or not the key is still being pressed. If this value is true, that means the tapping term
 *  has ended, but the key is still being pressed down. This generally means the key is being "held".
 *
 * One thing that is currenlty not possible with qmk software in regards to tap dance is to mimic the "permissive hold"
 *  feature. In general, advanced tap dances do not work well if they are used with commonly typed letters.
 *  For example "A". Tap dances are best used on non-letter keys that are not hit while typing letters.
 *
 * Good places to put an advanced tap dance:
 *  z,q,x,j,k,v,b, any function key, home/end, comma, semi-colon
 *
 * Criteria for "good placement" of a tap dance key:
 *  Not a key that is hit frequently in a sentence
 *  Not a key that is used frequently to double tap, for example 'tab' is often double tapped in a terminal, or
 *    in a web form. So 'tab' would be a poor choice for a tap dance.
 *  Letters used in common words as a double. For example 'p' in 'pepper'. If a tap dance function existed on the
 *    letter 'p', the word 'pepper' would be quite frustating to type.
 *
 * For the third point, there does exist the 'TD_DOUBLE_SINGLE_TAP', however this is not fully tested
 *
 */
td_state_t cur_dance(tap_dance_state_t *state) {
    if (state->count == 1) {
        if (/*state->interrupted ||*/ !state->pressed) return TD_SINGLE_TAP;
        // Key has not been interrupted, but the key is still held. Means you want to send a 'HOLD'.
        else return TD_SINGLE_HOLD;
    } else if (state->count == 2) {
        // TD_DOUBLE_SINGLE_TAP is to distinguish between typing "pepper", and actually wanting a double tap
        // action when hitting 'pp'. Suggested use case for this return value is when you want to send two
        // keystrokes of the key, and not the 'double tap' action/macro.
        /*if (state->interrupted) return TD_DOUBLE_SINGLE_TAP;
        else */if (state->pressed) return TD_DOUBLE_HOLD;
        else return TD_DOUBLE_TAP;
    }

    // Assumes no one is trying to type the same letter three times (at least not quickly).
    // If your tap dance key is 'KC_W', and you want to type "www." quickly - then you will need to add
    // an exception here to return a 'TD_TRIPLE_SINGLE_TAP', and define that enum just like 'TD_DOUBLE_SINGLE_TAP'
    if (state->count == 3) {
        if (/*state->interrupted ||*/ !state->pressed) return TD_TRIPLE_TAP;
        else return TD_TRIPLE_HOLD;
    } else return TD_UNKNOWN;
}

// Create an instance of 'td_tap_t' for the 'x' tap dance.
static td_tap_t xtap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

void megaShift_finished(tap_dance_state_t *state, void *user_data) {
    xtap_state.state = cur_dance(state);
    switch (xtap_state.state) {
        case TD_SINGLE_TAP: add_mods(MOD_BIT(KC_LSFT)); register_code(KC_9); del_mods(MOD_BIT(KC_LSFT)); break;
        case TD_SINGLE_HOLD: register_mods(MOD_BIT(KC_LSFT)); break;
        case TD_DOUBLE_TAP: /* caps_word_toggle ON RESET */ break;
        case TD_DOUBLE_HOLD: register_code(KC_LALT); break;
        // Last case is for fast typing. Assuming your key is `f`:
        // For example, when typing the word `buffer`, and you want to make sure that you send `ff` and not `Esc`.
        // In order to type `ff` when typing fast, the next character will have to be hit within the `TAPPING_TERM`, which by default is 200ms.
        //case TD_DOUBLE_SINGLE_TAP: tap_code(KC_X); register_code(KC_X); break;
        case TD_TRIPLE_TAP: register_code(KC_CAPS); break;
        case TD_TRIPLE_HOLD: register_code(KC_LCTL); break;
        default: break;
    }
}

void megaShift_reset(tap_dance_state_t *state, void *user_data) {
    switch (xtap_state.state) {
        case TD_SINGLE_TAP: add_mods(MOD_BIT(KC_LSFT)); unregister_code(KC_9); del_mods(MOD_BIT(KC_LSFT)); break;
        case TD_SINGLE_HOLD: unregister_mods(MOD_BIT(KC_LSFT)); break;
        case TD_DOUBLE_TAP: caps_word_toggle(); break;
        case TD_DOUBLE_HOLD: unregister_code(KC_LALT); break;
        //case TD_DOUBLE_SINGLE_TAP: unregister_code(KC_X); break;
        case TD_TRIPLE_TAP: unregister_code(KC_CAPS); break;
        case TD_TRIPLE_HOLD: unregister_code(KC_LCTL); break;
        default: break;
    }
    xtap_state.state = TD_NONE;
}
