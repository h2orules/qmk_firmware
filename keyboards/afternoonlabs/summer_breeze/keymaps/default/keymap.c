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


enum custom_keycodes {
    KC_QWERTY = SAFE_RANGE,
    KC_LOWER,
    KC_RAISE,
    KC_ADJUST,
    KC_LAYER,
    KC_BSPC_DEL,
};

// Tap Dance declarations
enum {
    TD_SHFT_CAPS,
};

// Tap Dance definitions
tap_dance_action_t tap_dance_actions[] = {
    // Tap once for Escape, twice for Caps Lock
    [TD_SHFT_CAPS] = ACTION_TAP_DANCE_DOUBLE(KC_LSFT, KC_CAPS),
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [_MAIN] = LAYOUT(
        //┌────────┬────────┬────────┐┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐┌────────┬────────┬────────┐
           KC_NO,   KC_EQL,  KC_GRAVE, KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                               KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINUS,  KC_INS, KC_HOME,  KC_PGUP,
        //├────────┼────────┼────────┤├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤├────────┼────────┼────────┤
           KC_BSLS, KC_LBRC, KC_RBRC,  LT(_NUMPAD,KC_TAB), KC_Q, KC_W, KC_E, KC_R,  KC_T,                               KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC_DEL, KC_DEL, KC_END, KC_PGDN,
        //├────────┼────────┼────────┤├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤├────────┼────────┼────────┤
                    KC_MS_U,           CW_TOGG, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                               KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,           KC_UP,
        //├────────┼────────┼────────┤├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤├────────┼────────┼────────┤
           KC_MS_L, KC_MS_D, KC_MS_R,  TD(TD_SHFT_CAPS), KC_Z, KC_X, KC_C, KC_V,    KC_B,                               KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,  KC_LEFT, KC_DOWN, KC_RIGHT,
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
           _______, _______, _______,  _______, C(KC_Z), C(KC_X), C(KC_C), C(KC_V), XXXXXXX,                            XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_BSLS, XXXXXXX,  XXXXXXX, KC_BRID, XXXXXXX,
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
    }
    return true;
}
