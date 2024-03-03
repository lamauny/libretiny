#ifndef _PINNAMES_H_
#define _PINNAMES_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <hal/hal_gpio.h>

typedef enum {
	PORT_A = 0,
	PORT_B = 1,
} ln_PinPort;

/* (((port)<<16)|(pin)) */
typedef enum {
	PA_0  = (PORT_A<<16|GPIO_PIN_0),
	PA_1  = (PORT_A<<16|GPIO_PIN_1),
	PA_2  = (PORT_A<<16|GPIO_PIN_2),
	PA_3  = (PORT_A<<16|GPIO_PIN_3),
	PA_4  = (PORT_A<<16|GPIO_PIN_4),
	PA_5  = (PORT_A<<16|GPIO_PIN_5),
	PA_6  = (PORT_A<<16|GPIO_PIN_6),
	PA_7  = (PORT_A<<16|GPIO_PIN_7),
	PA_8  = (PORT_A<<16|GPIO_PIN_8),
	PA_9  = (PORT_A<<16|GPIO_PIN_9),
	PA_10  = (PORT_A<<16|GPIO_PIN_10),
	PA_11  = (PORT_A<<16|GPIO_PIN_11),
	PA_12  = (PORT_A<<16|GPIO_PIN_12),
	PA_13  = (PORT_A<<16|GPIO_PIN_13),
	PA_14  = (PORT_A<<16|GPIO_PIN_14),
	PA_15  = (PORT_A<<16|GPIO_PIN_15),

	PB_0  = (PORT_B<<16|GPIO_PIN_0),
	PB_1  = (PORT_B<<16|GPIO_PIN_1),
	PB_2  = (PORT_B<<16|GPIO_PIN_2),
	PB_3  = (PORT_B<<16|GPIO_PIN_3),
	PB_4  = (PORT_B<<16|GPIO_PIN_4),
	PB_5  = (PORT_B<<16|GPIO_PIN_5),
	PB_6  = (PORT_B<<16|GPIO_PIN_6),
	PB_7  = (PORT_B<<16|GPIO_PIN_7),
	PB_8  = (PORT_B<<16|GPIO_PIN_8),
	PB_9  = (PORT_B<<16|GPIO_PIN_9),

	// Not connected
	NC = (uint32_t)0xFFFFFFFF
} ln_PinName;

#ifdef __cplusplus
}
#endif

#endif
