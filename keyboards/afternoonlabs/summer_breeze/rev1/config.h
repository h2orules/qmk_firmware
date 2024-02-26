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

#pragma once

#define SPLIT_HAND_PIN B3

 /// https://thomasbaart.nl/2018/12/01/reducing-firmware-size-in-qmk/
#undef LOCKING_SUPPORT_ENABLE
#undef LOCKING_RESYNC_ENABLE
#define NO_MUSIC_MODE

/* Select hand configuration */
#define MASTER_LEFT
#define SPLIT_USB_DETECT

// #define BOTH_SHIFTS_TURNS_ON_CAPS_WORD

// #define QUICK_TAP_TERM 0
 #ifdef TAPPING_TERM
     #undef TAPPING_TERM
     #define TAPPING_TERM 200
 #endif
