// This file is part of the CircuitPython project: https://circuitpython.org
//
// SPDX-FileCopyrightText: Copyright (c) 2024 snkYmkrct
//
// SPDX-License-Identifier: MIT

#include "supervisor/board.h"
#include "sdram.h"

// Use the MP_WEAK supervisor/shared/board.c versions of routines not defined here.

void board_init(void) {
    sdram_init();
    #if CIRCUITPY_DEBUG == 1
    sdram_test(true);
    #endif
}
