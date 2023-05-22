# Build Options
#   change yes to no to disable
#
BOOTMAGIC_ENABLE = no       # Enable Bootmagic Lite
MOUSEKEY_ENABLE = no        # Mouse keys
EXTRAKEY_ENABLE = yes       # Audio control and System control
CONSOLE_ENABLE = no         # Console for debug
COMMAND_ENABLE = no         # Commands for debug and configuration
NKRO_ENABLE = no            # Enable N-Key Rollover
BACKLIGHT_ENABLE = no       # Enable keyboard backlight functionality
RGBLIGHT_ENABLE = yes       # Enable keyboard RGB underglow
AUDIO_ENABLE = no           # Audio output
ENCODER_ENABLE = yes
OLED_DRIVER_ENABLE = yes
OLED_ENABLE = yes
POINTING_DEVICE_ENABLE = yes
POINTING_DEVICE_DRIVER = pmw3360

# Save space
MAGIC_ENABLE = no
AVR_USE_MINIMAL_PRINTF = yes
LTO_ENABLE = yes

DEFAULT_FOLDER = macroball/rev1

SRC += modes/intro/intro_mode.c
SRC += modes/volume/volume_mode.c
SRC += modes/motion/motion_mode.c
SRC += modes/scroll/scroll_mode.c
SRC += modes/game/game_mode.c
