/*
 * LedTaskInit.h
 *
 *  Created on: 18 Ara 2024
 *      Author: hakimmc
 */

#ifndef INCLUDE_LEDTASKINIT_H_
#define INCLUDE_LEDTASKINIT_H_

#include "stdint.h"

void gpio_init(uint8_t gpio_pin);
void led_init(void* pvParameter);

#endif /* INCLUDE_LEDTASKINIT_H_ */
