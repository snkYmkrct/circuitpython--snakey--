// This file is part of the CircuitPython project: https://circuitpython.org
//
// SPDX-FileCopyrightText: Copyright (c) 2021 Scott Shawcroft for Adafruit Industries
//
// SPDX-License-Identifier: MIT

#include "supervisor/board.h"

#include "shared-bindings/microcontroller/Pin.h"
#include "hardware/gpio.h"

#include "shared-bindings/busio/SPI.h"
#include "shared-bindings/fourwire/FourWire.h"
#include "shared-module/displayio/__init__.h"
#include "shared-module/displayio/mipi_constants.h"


uint8_t display_init_sequence[] = {
    0x01, 0x80, 0x80,  // Software reset then delay 0x80 (128ms)
    0xEF, 0x03, 0x03, 0x80, 0x02,
    0xCF, 0x03, 0x00, 0xC1, 0x30,
    0xED, 0x04, 0x64, 0x03, 0x12, 0x81,
    0xE8, 0x03, 0x85, 0x00, 0x78,
    0xCB, 0x05, 0x39, 0x2C, 0x00, 0x34, 0x02,
    0xF7, 0x01, 0x20,
    0xEA, 0x02, 0x00, 0x00,
    0xc0, 0x01, 0x23,  // Power control VRH[5:0]
    0xc1, 0x01, 0x10,  // Power control SAP[2:0];BT[3:0]
    0xc5, 0x02, 0x3e, 0x28,  // VCM control
    0xc7, 0x01, 0x86,  // VCM control2
    0x36, 0x01, 0x38,  // Memory Access Control
    0x37, 0x01, 0x00,  // Vertical scroll zero
    0x3a, 0x01, 0x55,  // COLMOD: Pixel Format Set
    0xb1, 0x02, 0x00, 0x18,  // Frame Rate Control (In Normal Mode/Full Colors)
    0xb6, 0x03, 0x08, 0x82, 0x27,  // Display Function Control
    0xF2, 0x01, 0x00,  // 3Gamma Function Disable
    0x26, 0x01, 0x01,  // Gamma curve selected
    0xe0, 0x0f, 0x0F, 0x31, 0x2B, 0x0C, 0x0E, 0x08, 0x4E, 0xF1, 0x37, 0x07,
    0x10, 0x03, 0x0E, 0x09, 0x00,  // Set Gamma
    0xe1, 0x0f, 0x00, 0x0E, 0x14, 0x03, 0x11, 0x07, 0x31, 0xC1, 0x48, 0x08,
    0x0F, 0x0C, 0x31, 0x36, 0x0F,  // Set Gamma
    0x11, 0x80, 0x78,  // Exit Sleep then delay 0x78 (120ms)
    0x29, 0x80, 0x78,  // Display on then delay 0x78 (120ms)
};

void board_init(void) {
    fourwire_fourwire_obj_t *bus = &allocate_display_bus()->fourwire_bus;
    busio_spi_obj_t *spi = &bus->inline_bus;
    common_hal_busio_spi_construct(spi, &pin_GPIO2, &pin_GPIO3, NULL, false);
    common_hal_busio_spi_never_reset(spi);

    bus->base.type = &fourwire_fourwire_type;
    common_hal_fourwire_fourwire_construct(bus,
        spi,
        &pin_GPIO4, // TFT_DC Command or data
        &pin_GPIO5, // TFT_CS Chip select
        &pin_GPIO1, // TFT_RST Reset
        80000000L, // Baudrate
        0, // Polarity
        0); // Phase

    busdisplay_busdisplay_obj_t *display = &allocate_display()->display;
    display->base.type = &busdisplay_busdisplay_type;
    common_hal_busdisplay_busdisplay_construct(display,
        bus,
        320, // Width (after rotation)
        240, // Height (after rotation)
        0, // column start
        0, // row start
        0, // rotation
        16, // Color depth
        false, // grayscale
        false, // pixels in byte share row. only used for depth < 8
        1, // bytes per cell. Only valid for depths < 8
        false, // reverse_pixels_in_byte. Only valid for depths < 8
        true, // reverse_pixels_in_word
        MIPI_COMMAND_SET_COLUMN_ADDRESS, // Set column command
        MIPI_COMMAND_SET_PAGE_ADDRESS, // Set row command
        MIPI_COMMAND_WRITE_MEMORY_START, // Write memory command
        display_init_sequence,
        sizeof(display_init_sequence),
        NULL,  // backlight pin
        NO_BRIGHTNESS_COMMAND,
        1.0f, // brightness
        false, // single_byte_bounds
        false, // data_as_commands
        false, // auto_refresh
        20, // native_frames_per_second
        true, // backlight_on_high
        false, // SH1107_addressing
        50000); // backlight pwm frequency
}

bool board_requests_safe_mode(void) {
    return false;
}

void reset_board(void) {
}

void board_deinit(void) {
}
