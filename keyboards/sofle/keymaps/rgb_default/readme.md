# Custom Sofle RGB layout

Build this 72-LED, ATmega32U4 Sofle layout with:

```sh
qmk compile -kb sofle/rev1 -km rgb_default
```

The firmware is `sofle_rev1_rgb_default.hex`. This is not the separate
`h2orules` keymap or the Keyhive hardware variant.

## Automatic host layout

The left thumb row, **right to left**, follows the detected host:

| Host | Thumb keys |
| --- | --- |
| macOS / iOS | Enter, Command, Lower, Control, Option |
| Windows / Linux | Enter, Control, Lower, GUI, Alt |
| Unknown / detection pending | Original Mac layout |

Control and GUI are swapped on both sides for Windows/Linux using QMK's
runtime modifier configuration. This also swaps those modifiers in chords
and mod-taps; it does not translate application-specific shortcuts into
equivalent commands on another OS. Alt, layer positions, and the selected
QWERTY/Colemak/Colemak-DH layout are unchanged.

The master OLED shows the applied host's logo/name and `CMD` or `CTRL` for
the thumb key next to Enter. `MAC?` indicates the unknown-host fallback.
Changes wait for all keys and modifiers to be released so a press and its
release use the same mapping. The other OLED retains its WPM display.
Automatic modifier swaps are not written to EEPROM.

QMK's USB fingerprinting is best-effort, not a guaranteed OS identification.

## Powered dock reconnection

The AVR uses VBUS sensing to choose the USB-connected master half. Unlike
`SPLIT_USB_DETECT`, this does not require the laptop to enumerate the keyboard
within two seconds of power-on. The USB cable should normally be connected
to the left half, as before.

`OS_DETECTION_KEYBOARD_RESET` additionally enables QMK's reset recovery after
USB reinitialization. A reset clears transient keyboard state and restarts
host detection. Actual dock behavior still needs confirmation on hardware.

The unused one-shot-key engine is disabled to fit the firmware in AVR flash;
this layout has no one-shot key bindings. RGB layers, the OLEDs, encoders,
Caps Word, tap dance, and NKRO remain enabled.
