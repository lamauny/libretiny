/* Copyright (c) Etienne Le Cousin 2024-02-24. */

#include <libretiny.h>
#include <sdk_private.h>

extern uint8_t uart_print_port;

void lt_init_family() {
    //0. check reboot cause
    ln_chip_get_reboot_cause();

    //1.sys clock,interrupt
    SetSysClock();
    set_interrupt_priority();
    switch_global_interrupt(HAL_ENABLE);
    ln_runtime_measure_init();

    //2. register os heap mem
    OS_DefineHeapRegions();

    // set default UART print port
    uart_print_port = LT_UART_DEFAULT_LOGGER;
    log_init();

    cm_backtrace_init("LibreTiny - LN882H", "HW_V1.0", "SW_V1.0");
    LT_I("------  LibreTiny - LN882H  ------");

    if (NVDS_ERR_OK != ln_nvds_init(NVDS_SPACE_OFFSET)) {
        LT_E("NVDS init failed!");
    }

    if (KV_ERR_NONE != ln_kv_port_init(KV_SPACE_OFFSET, (KV_SPACE_OFFSET + KV_SPACE_SIZE))) {
        LT_E("KV init failed!");
    }

    //3.rf preprocess,img cal
    //wifi_rf_calibration();
}

void lt_init_arduino() {
#if LT_AUTO_DOWNLOAD_REBOOT && LT_ARD_HAS_SERIAL && LT_HW_UART1
	// initialize auto-download-reboot parser
	Serial1.begin(115200);
#endif
}

void lt_init_variant() {}

