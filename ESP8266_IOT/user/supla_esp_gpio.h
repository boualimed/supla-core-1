/*
 ============================================================================
 Name        : supla_esp_gpio.h
 Author      : Przemyslaw Zygmunt przemek@supla.org
 Version     : 1.2
 Copyright   : GPLv2
 ============================================================================
*/

#ifndef SUPLA_ESP_GPIO_H_
#define SUPLA_ESP_GPIO_H_

#include "supla_esp.h"


void ICACHE_FLASH_ATTR gpio16_output_conf(void);
void ICACHE_FLASH_ATTR gpio16_output_set(uint8 value);
void ICACHE_FLASH_ATTR gpio16_input_conf(void);
uint8 ICACHE_FLASH_ATTR gpio16_input_get(void);
uint8 ICACHE_FLASH_ATTR gpio16_output_get(void);

void ICACHE_FLASH_ATTR supla_esp_gpio_init(void);

void ICACHE_FLASH_ATTR supla_esp_gpio_state_disconnected(void);
void ICACHE_FLASH_ATTR supla_esp_gpio_state_ipreceived(void);
void ICACHE_FLASH_ATTR supla_esp_gpio_state_connected(void);
void ICACHE_FLASH_ATTR supla_esp_gpio_state_cfgmode(void);

void ICACHE_FLASH_ATTR supla_esp_gpio_hi(int port, char hi);
char ICACHE_FLASH_ATTR supla_esp_gpio_is_hi(int port);

#ifdef RELAY1_PORT
char ICACHE_FLASH_ATTR supla_esp_gpio_relay1_hi(char hi);
#endif

#ifdef RELAY2_PORT
char ICACHE_FLASH_ATTR supla_esp_gpio_relay2_hi(char hi);
#endif

#endif /* SUPLA_ESP_GPIO_H_ */

