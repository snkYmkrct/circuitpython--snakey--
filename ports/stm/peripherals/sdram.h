// This file is part of the CircuitPython project: https://circuitpython.org
//
// SPDX-FileCopyrightText: Copyright (c) 2025 snkYmkrct
//
// SPDX-License-Identifier: MIT

#pragma once

bool sdram_init(void);
void *sdram_start(void);
void *sdram_end(void);
bool sdram_test(bool exhaustive);
