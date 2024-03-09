/* #ifdef __cplusplus

#undef hexdump
#define hexdump ln_hexdump

#undef log_printf
#define __wrap_sprintf __wrap_ln_sprintf

#endif //__cplusplus

#include_next "utils/debug/log.h"

#ifdef __cplusplus

#undef log_printf
#undef __wrap_sprintf

#undef hexdump

#endif //__cplusplus */

#ifndef __cplusplus

#undef log_printf
#define __wrap_sprintf __wrap_ln_sprintf
#include_next "utils/debug/log.h"
#undef __wrap_sprintf

#endif //__cplusplus */

