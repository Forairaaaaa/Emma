# CMakeLists.txt of Emma BSP component

# Source files directories
set(EMMA_SRC_DIRS
    "."
    "Buzzer"
    "Buzzer/Tone"
    "RGBLED"
    "RGBLED/led_strip"
    "Encoder"
    "Button"
    "Button/iot_button"
)

# Head files directories
set(EMMA_INC_DIRS
    "."
    "LCD"
    "Buzzer"
    "Buzzer/Tone"
    "RGBLED"
    "RGBLED/led_strip"
    "Encoder"
    "Button"
    "Button/iot_button"
)

# Public component requirement
set(EMMA_REQUIRES
    "LovyanGFX"
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
