/*
 ============================================================================
 Name        : supla_esp_pwm.h
 Author      : Przemyslaw Zygmunt przemek@supla.org
 Version     : 1.0
 Copyright   : GPLv2
 ============================================================================
*/

#include "supla_esp.h"

#ifdef SUPLA_PWM_COUNT

#ifndef SUPLA_ESP_PWM_H_
#define SUPLA_ESP_PWM_H_

#include <eagle_soc.h>
#include <os_type.h>


void ICACHE_FLASH_ATTR supla_esp_pwm_init(void);
void ICACHE_FLASH_ATTR supla_esp_pwm_set_percent_duty(uint8 percent, uint8 percent_percent, uint8 channel);
char ICACHE_FLASH_ATTR supla_esp_pwm_is_on(void);
void ICACHE_FLASH_ATTR supla_esp_pwm_on(char on);

#endif /* SUPLA_PWM_COUNT */

#endif /* SUPLA_PWM_H_ */
