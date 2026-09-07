// Copyright 2026 QMK
// SPDX-License-Identifier: GPL-2.0-or-later
#pragma once

#include "os_detection.h"

enum sofle_layers {
    _DEFAULTS = 0,
    _QWERTY = 0,
    _COLEMAK,
    _COLEMAKDH,
    _LOWER,
    _RAISE,
    _ADJUST,
    _NUMPAD,
    _SWITCH
};

void host_layout_init(void);
os_variant_t host_layout_os(void);
uint16_t host_layout_navigation_keycode(uint16_t keycode);
