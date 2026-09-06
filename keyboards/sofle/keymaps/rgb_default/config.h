 /* Copyright 2021 Dane Evans
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
#pragma once

 /// https://thomasbaart.nl/2018/12/01/reducing-firmware-size-in-qmk/
#undef LOCKING_SUPPORT_ENABLE
#undef LOCKING_RESYNC_ENABLE
#define NO_MUSIC_MODE
// This keymap has no one-shot keys; omit their engine to fit the AVR flash.
#define NO_ACTION_ONESHOT

// Use the ATmega32U4 VBUS sense even when a powered dock has no host yet.
// Do not enable SPLIT_USB_DETECT's enumeration timeout on this AVR target.
#define OS_DETECTION_KEYBOARD_RESET

#define BOTH_SHIFTS_TURNS_ON_CAPS_WORD

#define CUSTOM_FONT
#define CUSTOM_LAYER_READ //if you remove this it causes issues - needs better guarding

// OLED support
#define OLED_TIMEOUT 120000
#define OLED_BRIGHTNESS 120
#define SPLIT_WPM_ENABLE

/* ws2812 RGB LED */
#define WS2812_DI_PIN D3

#define RGBLIGHT_SLEEP
#define RGBLIGHT_LAYERS

#ifdef RGBLIGHT_ENABLE
    #undef RGBLIGHT_LED_COUNT
    #undef RGBLED_SPLIT

    //#undef RGBLIGHT_ANIMATIONS
	// #define RGBLIGHT_EFFECT_BREATHING
	// #define RGBLIGHT_EFFECT_RAINBOW_MOOD
    #define RGBLIGHT_EFFECT_RAINBOW_SWIRL
	// #define RGBLIGHT_EFFECT_SNAKE
	// #define RGBLIGHT_EFFECT_KNIGHT
	// #define RGBLIGHT_EFFECT_CHRISTMAS
	// #define RGBLIGHT_EFFECT_STATIC_GRADIENT
	// #define RGBLIGHT_EFFECT_RGB_TEST
	// #define RGBLIGHT_EFFECT_ALTERNATING
	// #define RGBLIGHT_EFFECT_TWINKLE

    #define RGBLIGHT_LED_COUNT 72
    #define RGBLED_SPLIT { 36, 36 }

    #define RGBLIGHT_LIMIT_VAL 120
    #define RGBLIGHT_HUE_STEP 10
    #define RGBLIGHT_SAT_STEP 17
    #define RGBLIGHT_VAL_STEP 17
#endif

 // #define QUICK_TAP_TERM 0
 #ifdef TAPPING_TERM
     #undef TAPPING_TERM
     #define TAPPING_TERM 200
 #endif
 // #define ENCODER_DIRECTION_FLIP