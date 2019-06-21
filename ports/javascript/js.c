#include "py/nlr.h"
#include "py/obj.h"
#include "py/runtime.h"
#include "py/binary.h"
#include <stdio.h>
#include <string.h>

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

STATIC mp_obj_t js_exec(mp_obj_t code) {
    char * result = emscripten_run_script_string(mp_obj_str_get_str(code));
    return mp_obj_new_str(result, strlen(result));
}
STATIC MP_DEFINE_CONST_FUN_OBJ_1(js_exec_obj, js_exec);

STATIC mp_obj_t js_sleep(mp_obj_t milliseconds) {
    emscripten_sleep_with_yield(mp_obj_get_int(milliseconds));
    return mp_const_none;
}
STATIC MP_DEFINE_CONST_FUN_OBJ_1(js_sleep_obj, js_sleep);


STATIC const mp_map_elem_t js_globals_table[] = {
    { MP_OBJ_NEW_QSTR(MP_QSTR___name__), MP_OBJ_NEW_QSTR(MP_QSTR_js) },
    { MP_OBJ_NEW_QSTR(MP_QSTR_exec), (mp_obj_t)&js_exec_obj },
    { MP_OBJ_NEW_QSTR(MP_QSTR_sleep), (mp_obj_t)&js_sleep_obj },

};

STATIC MP_DEFINE_CONST_DICT (
    mp_module_js_globals,
    js_globals_table
);

const mp_obj_module_t mp_module_js = {
    .base = { &mp_type_module },
    .globals = (mp_obj_dict_t*)&mp_module_js_globals,
};
