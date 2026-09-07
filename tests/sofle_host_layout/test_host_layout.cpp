// Copyright 2026 QMK
// SPDX-License-Identifier: GPL-2.0-or-later
#include "test_common.hpp"

extern "C" {
#include "keyboards/sofle/keymaps/rgb_default/host_layout.h"
#include "keycode_config.h"
#include "eeconfig.h"
}

class SofleHostLayout : public TestFixture {
   public:
    void SetUp() override {
        host_layout_init();
    }
};

TEST_F(SofleHostLayout, HostChangesSwapBothSidesAndDisplayMode) {
    for (auto os : {OS_MACOS, OS_WINDOWS, OS_LINUX, OS_IOS, OS_UNSURE, OS_WINDOWS, OS_MACOS}) {
        process_detected_host_os_user(os);
        housekeeping_task_user();
        const bool swap = os == OS_WINDOWS || os == OS_LINUX;
        EXPECT_EQ(host_layout_os(), os);
        EXPECT_EQ(keycode_config(KC_LGUI), swap ? KC_LCTL : KC_LGUI);
        EXPECT_EQ(keycode_config(KC_LCTL), swap ? KC_LGUI : KC_LCTL);
        EXPECT_EQ(keycode_config(KC_RGUI), swap ? KC_RCTL : KC_RGUI);
        EXPECT_EQ(keycode_config(KC_RCTL), swap ? KC_RGUI : KC_RCTL);
        EXPECT_EQ(keycode_config(KC_LALT), KC_LALT);
        EXPECT_EQ(mod_config(MOD_LGUI), swap ? MOD_LCTL : MOD_LGUI);
    }
}

TEST_F(SofleHostLayout, DefersChangeUntilModifiersAreReleased) {
    set_mods(MOD_LGUI);
    process_detected_host_os_user(OS_WINDOWS);
    housekeeping_task_user();
    EXPECT_EQ(host_layout_os(), OS_UNSURE);
    clear_mods();
    set_weak_mods(MOD_LGUI);
    housekeeping_task_user();
    EXPECT_EQ(host_layout_os(), OS_UNSURE);
    clear_weak_mods();
    housekeeping_task_user();
    EXPECT_EQ(host_layout_os(), OS_WINDOWS);
}

TEST_F(SofleHostLayout, NavigationMatchesAppliedHost) {
    for (auto os : {OS_UNSURE, OS_MACOS, OS_WINDOWS, OS_LINUX, OS_IOS}) {
        process_detected_host_os_user(os);
        housekeeping_task_user();
        const bool native = os == OS_WINDOWS || os == OS_LINUX;
        EXPECT_EQ(host_layout_navigation_keycode(KC_HOME), native ? KC_HOME : LGUI(KC_LEFT));
        EXPECT_EQ(host_layout_navigation_keycode(KC_END), native ? KC_END : LGUI(KC_RIGHT));
        EXPECT_EQ(host_layout_navigation_keycode(KC_PGUP), KC_PGUP);
        EXPECT_EQ(host_layout_navigation_keycode(KC_PGDN), KC_PGDN);
        EXPECT_EQ(host_layout_navigation_keycode(KC_LEFT), KC_LEFT);
    }
}

TEST_F(SofleHostLayout, MacNavigationPreservesShiftAndReleasesCommand) {
    TestDriver driver;
    auto shift = KeymapKey(0, 0, 0, KC_LSFT);
    auto home = KeymapKey(0, 1, 0, host_layout_navigation_keycode(KC_HOME));
    auto end = KeymapKey(0, 2, 0, host_layout_navigation_keycode(KC_END));
    set_keymap({shift, home, end});
    testing::InSequence sequence;

    EXPECT_REPORT(driver, (KC_LSFT));
    shift.press();
    run_one_scan_loop();
    EXPECT_REPORT(driver, (KC_LSFT, KC_LGUI));
    EXPECT_REPORT(driver, (KC_LSFT, KC_LGUI, KC_LEFT));
    home.press();
    run_one_scan_loop();
    EXPECT_REPORT(driver, (KC_LSFT, KC_LGUI));
    EXPECT_REPORT(driver, (KC_LSFT));
    home.release();
    run_one_scan_loop();
    EXPECT_REPORT(driver, (KC_LSFT, KC_LGUI));
    EXPECT_REPORT(driver, (KC_LSFT, KC_LGUI, KC_RIGHT));
    end.press();
    run_one_scan_loop();
    EXPECT_REPORT(driver, (KC_LSFT, KC_LGUI));
    EXPECT_REPORT(driver, (KC_LSFT));
    end.release();
    run_one_scan_loop();
    EXPECT_EMPTY_REPORT(driver);
    shift.release();
    run_one_scan_loop();
}

TEST_F(SofleHostLayout, DefersChangeUntilPhysicalKeysAreReleased) {
    auto key = KeymapKey(0, 0, 0, KC_A);
    set_keymap({key});
    key.press();
    process_detected_host_os_user(OS_WINDOWS);
    housekeeping_task_user();
    EXPECT_EQ(host_layout_os(), OS_UNSURE);
    key.release();
    housekeeping_task_user();
    EXPECT_EQ(host_layout_os(), OS_WINDOWS);
}

TEST_F(SofleHostLayout, HostChangesDoNotWriteEepromAndStartupRestoresFallback) {
    keymap_config_t before;
    eeconfig_read_keymap(&before);
    process_detected_host_os_user(OS_WINDOWS);
    housekeeping_task_user();
    keymap_config_t after;
    eeconfig_read_keymap(&after);
    EXPECT_EQ(before.raw, after.raw);
    host_layout_init();
    EXPECT_EQ(host_layout_os(), OS_UNSURE);
    EXPECT_FALSE(keymap_config.swap_lctl_lgui);
    EXPECT_FALSE(keymap_config.swap_rctl_rgui);
}
