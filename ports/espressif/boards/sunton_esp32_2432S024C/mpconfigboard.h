// This file is part of the CircuitPython project: https://circuitpython.org
//
// SPDX-FileCopyrightText: Copyright (c) 2024 Olav Schettler
//
// SPDX-License-Identifier: MIT

#pragma once

// Micropython setup

#define MICROPY_HW_BOARD_NAME       "sunton_esp32_2432S024C"
#define MICROPY_HW_MCU_NAME         "ESP32-D0WD-V3"
#define MICROPY_HW_LED_STATUS       (&pin_GPIO17) // LED_BLUE

#define CIRCUITPY_BOOT_BUTTON       (&pin_GPIO0)

#define DEFAULT_I2C_BUS_SDA         (&pin_GPIO33)
#define DEFAULT_I2C_BUS_SCL         (&pin_GPIO32)

#define CIRCUITPY_BOARD_SPI         (2)
#define CIRCUITPY_BOARD_SPI_PIN     { \
        {.clock = &pin_GPIO18, .mosi = &pin_GPIO23, .miso = &pin_GPIO19}, /*SD*/ \
        {.clock = &pin_GPIO14, .mosi = &pin_GPIO13, .miso = &pin_GPIO12}, /*LCD*/ \
}

#define CIRCUITPY_CONSOLE_UART_TX (&pin_GPIO1)
#define CIRCUITPY_CONSOLE_UART_RX (&pin_GPIO3)
