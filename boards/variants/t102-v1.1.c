/* This file was auto-generated from t102-v1.1.json using boardgen */

#include <Arduino.h>

#ifdef LT_VARIANT_INCLUDE
#include LT_VARIANT_INCLUDE
#endif

// clang-format off
PinInfo lt_arduino_pin_info_list[PINS_COUNT] = {
	// D0: PA12, PWM3
	{PA_12, PIN_PWM | PIN_IRQ | PIN_GPIO,                                PIN_NONE, 0},
	// D1: PA00, PWM2
	{PA_0,  PIN_PWM | PIN_IRQ | PIN_GPIO,                                PIN_NONE, 0},
	// D2: PA05, PWM4, WAKE1
	{PA_5,  PIN_PWM | PIN_IRQ | PIN_GPIO,                                PIN_NONE, 0},
	// D3: PA30, UART2_TX, I2C0_SDA, PWM4
	{PA_30, PIN_UART | PIN_I2C | PIN_PWM | PIN_IRQ | PIN_GPIO,           PIN_NONE, 0},
	// D4: PA29, UART2_RX, I2C0_SCL, PWM4
	{PA_29, PIN_UART | PIN_I2C | PIN_PWM | PIN_IRQ | PIN_GPIO,           PIN_NONE, 0},
	// D5: PA18, UART0_RX, SPI0_SCK, SPI1_SCK, I2C1_SCL, SD_D2, TMR4_TRIG, I2S0_MCK, WAKE0
	{PA_18, PIN_UART | PIN_SPI | PIN_I2S | PIN_I2C | PIN_IRQ | PIN_GPIO, PIN_NONE, 0},
	// D6: PA23, UART0_TX, SPI0_MOSI, SPI1_MOSI, I2C1_SDA, SD_D1, PWM0, WAKE3
	{PA_23, PIN_UART | PIN_SPI | PIN_I2C | PIN_PWM | PIN_IRQ | PIN_GPIO, PIN_NONE, 0},
	// D7: PA14, PWM0, SWCLK
	{PA_14, PIN_SWD | PIN_PWM | PIN_IRQ | PIN_GPIO,                      PIN_NONE, 0},
	// D8: PA15, PWM1, SWDIO
	{PA_15, PIN_SWD | PIN_PWM | PIN_IRQ | PIN_GPIO,                      PIN_NONE, 0},
};

PinInfo *lt_arduino_pin_gpio_map[] = {
	[0]  = &(lt_arduino_pin_info_list[1]), // PA_0 (D1)
	[5]  = &(lt_arduino_pin_info_list[2]), // PA_5 (D2)
	[12] = &(lt_arduino_pin_info_list[0]), // PA_12 (D0)
	[14] = &(lt_arduino_pin_info_list[7]), // PA_14 (D7)
	[15] = &(lt_arduino_pin_info_list[8]), // PA_15 (D8)
	[18] = &(lt_arduino_pin_info_list[5]), // PA_18 (D5)
	[23] = &(lt_arduino_pin_info_list[6]), // PA_23 (D6)
	[29] = &(lt_arduino_pin_info_list[4]), // PA_29 (D4)
	[30] = &(lt_arduino_pin_info_list[3]), // PA_30 (D3)
};
// clang-format on
