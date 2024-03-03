/* Copyright (c) Etienne Le Cousin 2024-02-17. */

#pragma once

#include <Arduino.h>
#include <sdk_private.h>

#ifdef __cplusplus
extern "C" {
#endif

struct PinData_s {
	gpio_init_t_def *gpio;
//	gpio_irq_t *irq;
//	pwmout_t *pwm;
	PinMode gpioMode;
	uint32_t gpio_base;
	PinStatus irqMode;
	void *irqHandler;
	void *irqParam;
};

#ifdef __cplusplus
} // extern "C"
#endif
