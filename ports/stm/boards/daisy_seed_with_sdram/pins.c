#include "shared-bindings/board/__init__.h"

static const mp_rom_map_elem_t board_module_globals_table[] = {
    {MP_ROM_QSTR(MP_QSTR_LED), MP_ROM_PTR(&pin_PC07)},
    {MP_ROM_QSTR(MP_QSTR_BOOT), MP_ROM_PTR(&pin_PG03)},
    {MP_ROM_QSTR(MP_QSTR_D14), MP_ROM_PTR(&pin_PB07)},
    {MP_ROM_QSTR(MP_QSTR_SDA4), MP_ROM_PTR(&pin_PB07)},
    {MP_ROM_QSTR(MP_QSTR_D13), MP_ROM_PTR(&pin_PB06)},
    {MP_ROM_QSTR(MP_QSTR_SCL4), MP_ROM_PTR(&pin_PB06)},
};
MP_DEFINE_CONST_DICT(board_module_globals, board_module_globals_table);
