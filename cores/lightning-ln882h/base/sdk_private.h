/* Copyright (c) Etienne Le Cousin 2024-02-10. */

#pragma once

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

//PinNames
#include "PinNames.h"

// fix conflicts with Arduino's PinMode enum
//#define PinMode ln_PinMode
// fix conflict with Arduino's hexdump declaration
// #define hexdump ln_hexdump

//#undef log_printf
//#define __wrap_sprintf __wrap_ln_sprintf
//#include "utils/debug/log.h"
// conflict with lt_logger.h
//#undef log_printf
//#undef __wrap_sprintf

// undefine ROM stdio in favor of printf() library (wrappers)
#undef printf
#undef sprintf
#undef vsprintf
#undef snprintf
#undef vsnprintf
#undef vprintf
#include <stdio.h>

//SDK
#include <osal/osal.h>
#include <serial/serial.h>
#include <hal/hal_gpio.h>
#include <hal/hal_interrupt.h>
//#include <hal/hal_flash.h>
//#include "utils/system_parameter.h"
#include "utils/debug/CmBacktrace/cm_backtrace.h"
#include "utils/reboot_trace/reboot_trace.h"
#include "utils/runtime/runtime.h"
#include "ln_nvds.h"
#include "ln_kv_api.h"
#include "flash_partition_table.h"

#ifdef __cplusplus
} // extern "C"
#endif
