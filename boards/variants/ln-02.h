/* This file was auto-generated from ln-02.json using boardgen */

#pragma once

// clang-format off

// Pins
// ----
#define PINS_COUNT         8  // Total GPIO count
#define NUM_DIGITAL_PINS   8  // Digital inputs/outputs
#define NUM_ANALOG_INPUTS  2  // ADC inputs
#define NUM_ANALOG_OUTPUTS 0  // PWM & DAC outputs
#define PINS_GPIO_MAX      11 // Last usable GPIO number

// Wire Interfaces
// ---------------
#define PIN_WIRE0_SCL_0 11u // PA_11
#define PIN_WIRE0_SCL_1 3u  // PA_3
#define PIN_WIRE0_SCL_2 3u  // PA_3
#define PIN_WIRE0_SCL_3 8u  // PB_8
#define PIN_WIRE0_SCL_4 2u  // PA_2
#define PIN_WIRE0_SCL_5 9u  // PB_9
#define PIN_WIRE0_SCL_6 1u  // PA_1
#define PIN_WIRE0_SCL_7 0u  // PA_0
#define PIN_WIRE0_SDA_0 11u // PA_11
#define PIN_WIRE0_SDA_1 3u  // PA_3
#define PIN_WIRE0_SDA_2 3u  // PA_3
#define PIN_WIRE0_SDA_3 8u  // PB_8
#define PIN_WIRE0_SDA_4 2u  // PA_2
#define PIN_WIRE0_SDA_5 9u  // PB_9
#define PIN_WIRE0_SDA_6 1u  // PA_1
#define PIN_WIRE0_SDA_7 0u  // PA_0
#define PINS_WIRE0_SCL  (pin_size_t[]){11u, 3u, 3u, 8u, 2u, 9u, 1u, 0u}
#define PINS_WIRE0_SDA  (pin_size_t[]){11u, 3u, 3u, 8u, 2u, 9u, 1u, 0u}

// Serial ports
// ------------
#define PIN_SERIAL0_RX  8u // PB_8
#define PIN_SERIAL0_TX  9u // PB_9
#define PIN_SERIAL1_RX  3u // PA_3
#define PIN_SERIAL1_TX  2u // PA_2
#define PINS_SERIAL0_RX (pin_size_t[]){8u}
#define PINS_SERIAL0_TX (pin_size_t[]){9u}
#define PINS_SERIAL1_RX (pin_size_t[]){3u}
#define PINS_SERIAL1_TX (pin_size_t[]){2u}

// Pin function macros
// -------------------
#define PIN_ADC2 0u  // PA_0
#define PIN_ADC3 1u  // PA_1
#define PIN_ADC5 3u  // PB_3
#define PIN_PA00 0u  // PA_0
#define PIN_PA01 1u  // PA_1
#define PIN_PA02 2u  // PA_2
#define PIN_PA03 3u  // PA_3
#define PIN_PA11 11u // PA_11
#define PIN_PB03 3u  // PB_3
#define PIN_PB08 8u  // PB_8
#define PIN_PB09 9u  // PB_9
#define PIN_RX0  8u  // PB_8
#define PIN_RX1  3u  // PA_3
#define PIN_TX0  9u  // PB_9
#define PIN_TX1  2u  // PA_2

// Port availability
// -----------------
#define HAS_SERIAL0             1
#define HAS_SERIAL1             1
#define HAS_WIRE0               1
#define SERIAL_INTERFACES_COUNT 2
#define WIRE_INTERFACES_COUNT   1

// Arduino pin names
// -----------------
#define PIN_D0 11u // PA_11
#define PIN_D1 3u  // PB_3
#define PIN_D2 3u  // PA_3
#define PIN_D3 8u  // PB_8
#define PIN_D4 2u  // PA_2
#define PIN_D5 9u  // PB_9
#define PIN_D6 1u  // PA_1
#define PIN_D7 0u  // PA_0
#define PIN_A2 0u  // PA_0
#define PIN_A3 1u  // PA_1

// Static pin names
// ----------------
static const unsigned char A2 = PIN_A2;
static const unsigned char A3 = PIN_A3;
static const unsigned char D0 = PIN_D0;
static const unsigned char D1 = PIN_D1;
static const unsigned char D2 = PIN_D2;
static const unsigned char D3 = PIN_D3;
static const unsigned char D4 = PIN_D4;
static const unsigned char D5 = PIN_D5;
static const unsigned char D6 = PIN_D6;
static const unsigned char D7 = PIN_D7;
