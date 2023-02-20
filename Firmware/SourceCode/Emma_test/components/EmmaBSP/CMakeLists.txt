# CMakeLists.txt of Emma BSP component

# Source files directories
set(EMMA_SRC_DIRS
    "."
    "Buzzer"
    "Buzzer/Tone"
    "Encoder"
    "Encoder/Button"
    "LvglPort"
)

# Head files directories
set(EMMA_INC_DIRS
    "."
    "Lcd"
    "Buzzer"
    "Buzzer/Tone"
    "Encoder"
    "Encoder/Button"
    "LvglPort"
)

# Public component requirement
set(EMMA_REQUIRES
    "LovyanGFX"
    "lvgl"
)

# Private component requirement
set(EMMA_PRIV_REQUIRES
    "spi_flash"
    "esp_timer"
)

# Register component
idf_component_register(SRC_DIRS ${EMMA_SRC_DIRS}
                  INCLUDE_DIRS ${EMMA_INC_DIRS}
                  REQUIRES ${EMMA_REQUIRES}
                  PRIV_REQUIRES ${EMMA_PRIV_REQUIRES}
)
