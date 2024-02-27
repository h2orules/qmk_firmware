# LTO: link time optimization makes the build take slightly longer
# but makes the resulting .hex file smaller, which allows you to
# fit more features into smaller MCUs:
LTO_ENABLE = yes
# Support for these features make the hex file larger, but we want 'em:
MOUSEKEY_ENABLE = yes     # Allow mapping of mouse control keys
EXTRAKEY_ENABLE = yes     # Allow audio & system control keys
COMMAND_ENABLE = no       # Commands for debug and configuration
CONSOLE_ENABLE = no       # Console for debug
MUSIC_ENABLE = no
NKRO_ENABLE = yes
SPACE_CADET_ENABLE = yes
TAP_DANCE_ENABLE = yes
CAPS_WORD_ENABLE = yes
DYNAMIC_MACRO_ENABLE = yes
