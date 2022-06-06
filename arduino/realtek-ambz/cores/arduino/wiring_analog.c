/*
 Copyright (c) 2011 Arduino.  All right reserved.

 This library is free software; you can redistribute it and/or
 modify it under the terms of the GNU Lesser General Public
 License as published by the Free Software Foundation; either
 version 2.1 of the License, or (at your option) any later version.

 This library is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 See the GNU Lesser General Public License for more details.

 You should have received a copy of the GNU Lesser General Public
 License along with this library; if not, write to the Free Software
 Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 */

#include <Arduino.h>
#include <analogin_api.h>
#include <analogout_api.h>
#include <gpio_ex_api.h>
#include <pwmout_api.h>

/* ADC */
analogin_t adc1;
analogin_t adc2;
analogin_t adc3;

bool g_adc_enabled[] = {false, false, false};
// from realtek_amebaz_va0_example/example_sources/adc_vbat/src/main.c
#define AD2MV(ad, offset, gain) (((ad >> 4) - offset) * 1000 / gain)

extern void *gpio_pin_struct[];

extern void pinRemoveMode(pin_size_t pinNumber);

static int _readResolution	= 10;
static int _writeResolution = 8;
static int _writePeriod		= 20000; // 50 Hz

// TODO implement custom ADC calibration

void analogReadResolution(int res) {
	_readResolution = res;
}

void analogWriteFrequency(int hz) {
	_writePeriod = 1E6 / hz;
}

void analogWritePeriod(int us) {
	_writePeriod = us;
}

void analogWriteResolution(int res) {
	_writeResolution = res;
}

uint8_t analog_reference = AR_DEFAULT;

void analogReference(uint8_t mode) {
	analog_reference = mode;
}

uint16_t analogReadVoltage(pin_size_t pinNumber) {
	uint16_t ret = 0;
	switch (pinNumber) {
		case PIN_A1:
			if (g_adc_enabled[1] == false) {
				analogin_init(&adc2, AD_2);
				g_adc_enabled[1] = true;
			}
			ret = analogin_read_u16(&adc2);
			// AD_1 - 0.0V-5.0V
			return AD2MV(ret, 0x496, 0xBA);
		case PIN_A0:
			if (g_adc_enabled[0] == false) {
				analogin_init(&adc1, AD_1);
				g_adc_enabled[0] = true;
			}
			ret = analogin_read_u16(&adc1);
			break;
		case PIN_A2:
			if (g_adc_enabled[2] == false) {
				analogin_init(&adc3, AD_3);
				g_adc_enabled[2] = true;
			}
			ret = analogin_read_u16(&adc3);
			break;
		default:
			return 0;
	}

	// AD_0, AD_2 - 0.0V-3.3V
	return AD2MV(ret, 0x418, 0x342);
}

int analogRead(pin_size_t pinNumber) {
	float voltage = analogReadVoltage(pinNumber);
	uint16_t ret  = 0;
	if (pinNumber != PIN_A1) {
		ret = round((1 << _readResolution) * voltage / 3300);
	} else {
		ret = round((1 << _readResolution) * voltage / 5000);
	}
	if (ret >= (1 << _readResolution))
		ret = (1 << _readResolution) - 1;
	return ret;
}

void analogOutputInit(void) {
	// nop
}

// Right now, PWM output only works on the pins with
// hardware support.  These are defined in the appropriate
// pins_*.c file.  For the rest of the pins, we default
// to digital output.
void analogWrite(pin_size_t pinNumber, int value) {
	pwmout_t *obj;

	if ((g_APinDescription[pinNumber].ulPinAttribute & PIO_PWM) == PIO_PWM) {
		float percent = value * 1.0 / (1 << _writeResolution);
		if (g_APinDescription[pinNumber].ulPinType != PIO_PWM) {
			if ((g_APinDescription[pinNumber].ulPinType == PIO_GPIO) ||
				(g_APinDescription[pinNumber].ulPinType == PIO_GPIO_IRQ)) {
				pinRemoveMode(pinNumber);
			}
			gpio_pin_struct[pinNumber] = malloc(sizeof(pwmout_t));
			pwmout_t *obj			   = (pwmout_t *)gpio_pin_struct[pinNumber];
			pwmout_init(obj, g_APinDescription[pinNumber].pinname);
			pwmout_period_us(obj, _writePeriod);
			pwmout_write(obj, percent);
			g_APinDescription[pinNumber].ulPinType = PIO_PWM;
			g_APinDescription[pinNumber].ulPinMode = PWM_MODE_ENABLED;
		} else {
			pwmout_t *obj = (pwmout_t *)gpio_pin_struct[pinNumber];
			// pwmout_period_us(obj, _writePeriod);
			pwmout_write(obj, percent);
		}
	}
}

typedef struct _tone_argument {
	uint32_t ulPin;
	uint32_t timer_id;
};

void _tone_timer_handler(const void *argument) {
	struct _tone_argument *arg = (struct _tone_argument *)argument;

	uint32_t ulPin = (uint32_t)argument;

	noTone(arg->ulPin);

	os_timer_delete(arg->timer_id);

	free((struct _tone_argument *)arg);
}

void _tone(uint32_t ulPin, unsigned int frequency, unsigned long duration) {
	pwmout_t *obj;

	if ((g_APinDescription[ulPin].ulPinAttribute & PIO_PWM) != PIO_PWM) {
		return;
	}

	if (g_APinDescription[ulPin].ulPinType != PIO_PWM) {
		if ((g_APinDescription[ulPin].ulPinType == PIO_GPIO) || (g_APinDescription[ulPin].ulPinType == PIO_GPIO_IRQ)) {
			pinRemoveMode(ulPin);
		}
		gpio_pin_struct[ulPin] = malloc(sizeof(pwmout_t));
		pwmout_t *obj		   = (pwmout_t *)gpio_pin_struct[ulPin];
		pwmout_init(obj, g_APinDescription[ulPin].pinname);
		pwmout_period(obj, 1.0 / frequency);
		pwmout_pulsewidth(obj, 1.0 / (frequency * 2));
		g_APinDescription[ulPin].ulPinType = PIO_PWM;
		g_APinDescription[ulPin].ulPinMode = PWM_MODE_ENABLED;

	} else {
		// There is already a PWM configured
		pwmout_t *obj = (pwmout_t *)gpio_pin_struct[ulPin];
		pwmout_period(obj, 1.0 / frequency);
		pwmout_pulsewidth(obj, 1.0 / (frequency * 2));
		/* if (g_APinDescription[ulPin].ulPinMode == PWM_MODE_DISABLED) {
			HAL_Pwm_Enable( &obj->pwm_hal_adp );
		} */
	}

	if (duration > 0) {
		struct _tone_argument *arg = (struct _tone_argument *)malloc(sizeof(struct _tone_argument));
		arg->ulPin				   = ulPin;
		arg->timer_id			   = os_timer_create(_tone_timer_handler, 0, arg);
		os_timer_start(arg->timer_id, duration);
	}
}
