// Copyright 2026 QMK
// SPDX-License-Identifier: GPL-2.0-or-later
#include "quantum.h"
#include "host_layout.h"

static os_variant_t pending_host_os = OS_UNSURE;
static os_variant_t active_host_os = OS_UNSURE;

static void apply_host_layout(os_variant_t os) {
    const bool swap = os == OS_WINDOWS || os == OS_LINUX;
    keymap_config.swap_lctl_lgui = swap;
    keymap_config.swap_rctl_rgui = swap;
    active_host_os = os;
#ifdef OLED_ENABLE
    oled_clear();
#endif
}

void host_layout_init(void) {
    // Host-dependent swaps are session-local, not EEPROM preferences.
    pending_host_os = OS_UNSURE;
    apply_host_layout(OS_UNSURE);
}

os_variant_t host_layout_os(void) {
    return active_host_os;
}

bool process_detected_host_os_user(os_variant_t os) {
    pending_host_os = os;
    return true;
}

void housekeeping_task_user(void) {
    if (!is_keyboard_master() || pending_host_os == active_host_os) {
        return;
    }
    // Keep press/release mappings consistent if detection settles while typing.
    if (get_mods() || get_weak_mods()) {
        return;
    }
    for (uint8_t row = 0; row < MATRIX_ROWS; ++row) {
        if (matrix_get_row(row)) {
            return;
        }
    }
    apply_host_layout(pending_host_os);
}
