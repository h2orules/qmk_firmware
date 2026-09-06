#pragma once

/* The way how "handedness" is decided (which half is which),
see https://docs.qmk.fm/#/feature_split_keyboard?id=setting-handedness
for more options.
*/

// Recover USB enumeration when a dock switches to a newly connected host.
#define OS_DETECTION_KEYBOARD_RESET
